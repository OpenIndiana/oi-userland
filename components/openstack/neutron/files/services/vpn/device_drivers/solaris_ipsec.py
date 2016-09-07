# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.

#
# Based on neutron/services/vpn/device_drivers/ipsec.py written in 2013
# by Nachi Ueno, NTT I3, Inc.
#
# Configuration of VPNaaS:
#
# This is an optional service thats managed by the Neutron l3-agent.
# It is not enabled by default. See [1].
# VPNaaS requires a correctly configured l3 router. See [2].
# VPNaaS uses the generic IPsec service driver. See [1].
# VPNaaS requires a Solaris specific device driver. See [3].
#
# Note[1]:
# To enable VPNaaS, add the following to:
# /etc/neutron/neutron.conf:
#
# [service_providers]
# service_provider = vpnaas
#
# This will use the generic ipsec service driver which is predefined in:
# /etc/neutron/neutron_vpnaas.conf
#
# Enabling VPNaaS will require the following services to be restarted:
#
# svc:/application/openstack/neutron/neutron-server:default
# svc:/application/openstack/neutron/neutron-l3-agent:default
#
# Note[2]:
# /etc/neutron/l3_agent.ini
#
# The [default] section of this file contains a router_id which
# is required for Solaris L3 agent and VPNaaS. Currently only a single
# router_id is supported.
# e.g.
#
# router_id = 9b17a6af-69ee-4185-a9fd-fa47502d97d6
#
# The device driver (Solaris specific) is configured in:
#
# Note[3]:
# The Solaris specific device driver is preconfigured in:
# /etc/neutron/vpn_agent.ini
#
# [vpnagent]
# vpn_device_driver =
# neutron.services.vpn.device_drivers.solaris_ipsec.SolarisIPsecDriver
#
# Note[4] - Optional values.
#
# Some defualt values can be changed by setting values under the [solaris]
# section of /etc/neutron/vpn_agent.ini.
#
# [solaris]
# ipsec_status_check_interval = 5
# packet_logging = False
# logger_level = "message+packet"
#
# Note[5] - Logging.
#
# The default logging level is WARN. Any LOG.warn() messages will
# appear in the log file.
#
# Adding "Verbose = True" to the [default] section will cause LOG.info()
# messages to be logged in addition to LOG.warn().
#
# Adding "Debug = True" to the [default] section will cause LOG.debug()
# messages to be logged in addition to LOG.info() and LOG.warn().
#

import abc
import copy
import errno
import logging
import os
import re
import shutil
import socket
import struct
from subprocess import CalledProcessError, Popen, PIPE, check_call
import sys
import threading
import time
import traceback
import unicodedata

import iniparse
import jinja2
import netaddr
from netaddr import IPNetwork
from oslo_concurrency import lockutils, processutils
from oslo_config import cfg
import oslo_messaging
from oslo_service import loopingcall
import six

import rad.bindings.com.oracle.solaris.rad.smf_1 as smfb
import rad.client
import rad.connect

from neutron.agent.linux import ip_lib, utils
from neutron.agent.solaris import packetfilter
from neutron.common import rpc as n_rpc
from neutron import context
from neutron.plugins.common import constants
from neutron.plugins.common import utils as plugin_utils
from neutron_vpnaas.db.vpn import vpn_db
from neutron_vpnaas.services.vpn.common import topics
from neutron_vpnaas.services.vpn import device_drivers

LOG = logging.getLogger(__name__)
TEMPLATE_PATH = os.path.dirname(__file__)

# solaris_defaults[] and solaris_opts[] contain configurable variables
# that are used by this driver. Any of these can be changed by adding a
# variable=value entry into /etc/neutron/vpn_agent.ini under the section
# called:
#
# [solaris]
#
# If there is no value in /etc/neutron/vpn_agent.ini, the default value
# is used. Its highly recommended that the values defined in solaris_defaults[]
# are never changed. The values under solaris_opts[] may be changed if the
# defaults are not suitable.

solaris_defaults = [
    cfg.StrOpt(
        'config_base_dir', default='$state_path/ipsec',
        help=_('Location to store ipsec server config files')),
    cfg.StrOpt(
        'ipsec_config_template',
        default=os.path.join(
            TEMPLATE_PATH,
            'template/solaris/ipsecinit.conf.template'),
        help=_('Template file for IPsec Policy configuration')),
    cfg.StrOpt(
        'ike_config_template',
        default=os.path.join(
            TEMPLATE_PATH,
            'template/solaris/ike.template'),
        help=_('Template file for IKEv1 configuration')),
    cfg.StrOpt(
        'ikev2_config_template',
        default=os.path.join(
            TEMPLATE_PATH,
            'template/solaris/ikev2.template'),
        help=_('Template file for IKEv2 configuration')),
    cfg.StrOpt(
        'ike_secret_template',
        default=os.path.join(
            TEMPLATE_PATH,
            'template/solaris/ike.secret.template'),
        help=_('Template file for IKEv1 PSK configuration')),
    cfg.StrOpt(
        'ikev2_secret_template',
        default=os.path.join(
            TEMPLATE_PATH,
            'template/solaris/ikev2.secret.template'),
        help=_('Template file for IKEv2 PSK configuration')),
    cfg.IntOpt(
        'status_maxfails', default=6,
        help=_('Number of times status check can fail before error occurs'))
]

solaris_opts = [
    cfg.IntOpt(
        'ipsec_status_check_interval', default=60,
        help=_('Interval for checking ipsec status')),
    cfg.BoolOpt(
        'packet_logging', default=False,
        help=_('IPsec policy failure logging')),
    cfg.StrOpt(
        'logger_level', default='message+packet',
        help=_('IPsec policy log level'))
]
cfg.CONF.register_opts(solaris_defaults, 'solaris')
cfg.CONF.register_opts(solaris_opts, 'solaris')

JINJA_ENV = None

IPSEC_CONNS = 'ipsec_site_connections'

# These globals are flags used to stop the looping event
# report_status() from looking at unstable state during
# shutdown or when IKE is being restarted.
global being_shutdown
being_shutdown = False
global restarting
restarting = False
existing_tunnels = []


def get_vpn_interfaces():
    # OpenStack-created tunnel names use the convention of starting with
    # "vpn" followed by a number.

    vpn_tunnels = []

    cmd = ["/usr/sbin/ipadm", "show-if", "-p", "-o", "ifname"]
    p = Popen(cmd, stdout=PIPE, stderr=PIPE)
    output, error = p.communicate()
    if p.returncode != 0:
        return vpn_tunnels

    ifnames = output.splitlines()
    prog = re.compile('^vpn_\d+_site_\d+')
    for ifname in ifnames:
        if prog.search(ifname):
            if ifname not in vpn_tunnels:
                vpn_tunnels.append(ifname)

    return vpn_tunnels


def disable_smf_services():
    """Disable IPsec Policy/IKE smf(5) services using rad(1).
    """
    ike_svc = "network/ipsec/ike"
    ipsec_svc = "network/ipsec/policy"
    global restarting
    restarting = True
    cmd = ['/usr/bin/pfexec', '/usr/sbin/ipseckey', 'flush']
    try:
        stdout, stderr = processutils.execute(*cmd)
    except processutils.ProcessExecutionError as stderr:
        pass

    rad_connection = rad.connect.connect_unix()

    instance = rad_connection.get_object(
        smfb.Instance(),
        rad.client.ADRGlobPattern({'service': ipsec_svc,
                                   'instance': 'default'}))
    instance.disable(False)

    instance = rad_connection.get_object(
        smfb.Instance(),
        rad.client.ADRGlobPattern({'service': ipsec_svc,
                                   'instance': 'logger'}))
    instance.disable(False)

    instance = rad_connection.get_object(
        smfb.Instance(),
        rad.client.ADRGlobPattern({'service': ike_svc,
                                   'instance': 'default'}))
    instance.disable(False)

    instance = rad_connection.get_object(
        smfb.Instance(),
        rad.client.ADRGlobPattern({'service': ike_svc,
                                   'instance': 'ikev2'}))
    instance.disable(False)

    rad_connection.close()


def shutdown_vpn():
    # Check to see if the VPN device_driver has been configured
    # by looking in the config file. If it has we may have to give the
    # driver a little more time to gracefully shutdown.
    # This method is called from the smf(5) stop method. Suppress LOG
    # output while shutting down.
    config = iniparse.RawConfigParser()
    config.read('/etc/neutron/vpn_agent.ini')

    if config.has_section('vpnagent'):
        # If we have a VPNaaS device driver, we still can't tell if its been
        # configured or not. The easiest way to determine if VPNaaS is
        # configured is to check if there are any IP tunnels configured.
        ifs = get_vpn_interfaces()
        if ifs:
            whack_ike_rules()
            disable_smf_services()
            delete_tunnels(ifs, False)


def whack_ike_rules():
        cmd = ['/usr/bin/pfexec', '/usr/sbin/ikeadm', '-n', 'dump', 'rule']
        try:
            status, stderr = processutils.execute(*cmd)
        except processutils.ProcessExecutionError as stderr:
            return

        connection_ids = []
        for line in status.split('\n'):
            m = re.search('Label', line)
            if not m:
                continue
            m = line.split('\'')
            connection_id = m[1]
            connection_ids.append(connection_id)

        if not connection_ids:
            return

        for rule in connection_ids:
            cmd = ['/usr/bin/pfexec', '/usr/sbin/ikeadm', '-n', 'del', 'rule',
                   rule]
            try:
                status, stderr = processutils.execute(*cmd)
            except processutils.ProcessExecutionError as stderr:
                pass

        # Deleting the IKE rules from the running IKE service will
        # cause the looping status process to mark any connections
        # down and update the server side. We just need to wait a
        # few seconds for it to notice.
        time.sleep(5)


def _get_template(template_file):
    global JINJA_ENV
    if not JINJA_ENV:
        templateLoader = jinja2.FileSystemLoader(searchpath="/")
        JINJA_ENV = jinja2.Environment(loader=templateLoader)
    return JINJA_ENV.get_template(template_file)


def delete_tunnels(tunnels, chatty=True):
    """Delete tunnel interfaces using dladm(1m)/ipadm(1m).

       Tunneling in Solaris is done with actual tunnel interfaces, not
       tunneling as policy which is customary in other operating systems.
       Solaris tunnels are configured using ipadm(1m) and is separate from
       the IKE configuration. Starting the IKE and IPsec services does not
       configure the tunnels. The glue between the tunnel and IPsec policy
       is the tunnel name. See comment in sync() for a description
       of tunnel names.

       Also remove any PF bypass rules. We don't need
       to delete the routes added by our evil twin add_tunnels()
       because these get whacked when the tunnel is removed.
       We are not really interested in any errors at this point, the
       tunnels are being deleted because we are shutting down, or
       we have new config.
    """
    if not tunnels:
        if chatty:
            LOG.info("VPNaaS has just started, no tunnels to whack.")
        return

    for idstr in tunnels:
        if chatty:
            LOG.debug("Removing tunnel: \"%s\"" % idstr)
        cmd = ['/usr/bin/pfexec', 'ipadm', 'delete-ip', idstr]
        try:
            stdout, stderr = processutils.execute(*cmd)
        except processutils.ProcessExecutionError as stderr:
            if chatty:
                LOG.debug("\"%s\"" % stderr)
        cmd = ['/usr/bin/pfexec', 'dladm', 'delete-iptun', idstr]
        try:
            stdout, stderr = processutils.execute(*cmd)
        except processutils.ProcessExecutionError as stderr:
            if chatty:
                LOG.debug("\"%s\"" % stderr)

    # Remove all the VPN bypass rules that were added for local subnet
    # going out to remote subnet. These rules are all captured inside of
    # a anchor whose name is of the form vpn_{peer_cidr}
    pf = packetfilter.PacketFilter('_auto/neutron:l3:agent')
    anchors = pf.list_anchors()
    if chatty:
        LOG.debug("All anchors under _auto/neutron:l3:agent: %s" % anchors)
    for anchor in anchors:
        if 'l3i' not in anchor:
            continue
        subanchors = anchor.split('/')[2:]
        l3i_anchors = pf.list_anchors(subanchors)
        if chatty:
            LOG.debug("All anchors under %s: %s" % (anchor, l3i_anchors))
        for l3i_anchor in l3i_anchors:
            if 'vpn_' not in l3i_anchor:
                continue
            l3i_subanchors = l3i_anchor.split('/')[2:]
            pf.remove_anchor(l3i_subanchors)


@six.add_metaclass(abc.ABCMeta)
class BaseSolaris():
    """Solaris IPsec/IKE Service Manager
       This class handles the generation of Solaris IKE (v1/v2)
       configuration files and IPsec policy configuration using
       templates. It also handles the starting/stopping of the
       IPsec and IKE smf(5) services and plumbing of IP tunnels.

       The configuration files are stored under:

       /var/lib/neutron/ipsec/<router_UUID>

       The smf(5) config_file properties for the policy and ike
       services are modified to point to this location.
    """

    CONFIG_DIRS = [
        'var/run',
        'log',
        'etc',
        'etc/inet',
        'etc/inet/ike',
        'etc/inet/secret'
    ]

    DIALECT_MAP = {
        "3des": "3des",
        "aes-128": "aes(128..128)",
        "aes-256": "aes(256..256)",
        "aes-192": "aes(192..192)",
        "group2": "2",
        "group5": "5",
        "group14": "14",
        "group15": "15",
        "bi-directional": "start",
        "response-only": "add",
        "v2": "ikev2",
        "v1": "default"
    }

    def __init__(self, conf, process_id,
                 vpnservice, namespace):
        self.conf = conf
        self.id = process_id
        self.updated_pending_status = False
        self.ike_running = False
        self.namespace = namespace
        self.connection_status = {}
        self.connection_ids = []
        self.ikeadm_fails = 0
        self.check_interval = cfg.CONF.solaris.ipsec_status_check_interval
        self.ikeadm_maxfails = cfg.CONF.solaris.status_maxfails
        self.config_dir = os.path.join(
            cfg.CONF.solaris.config_base_dir, self.id)
        self.etc_dir = os.path.join(self.config_dir, 'etc/inet')
        self.ike_svc = "network/ipsec/ike"
        self.ipsec_svc = "network/ipsec/policy"
        self.packet_logging = cfg.CONF.solaris.packet_logging
        self.logging_level = cfg.CONF.solaris.logger_level
        self.generate_config(vpnservice)
        self.dump_config()
        LOG.debug("Configuring router: %s" % process_id)
        LOG.debug("Configuring vpn-service: %s." % vpnservice)

    def dump_config(self):
        if not self.vpnservice:
            LOG.info("No VPNs configured.")
            return

        connections = self.vpnservice['ipsec_site_connections']
        LOG.info("New VPN configuration:")
        for site in connections:
            LOG.info("Site ID: \"%s\"" % site['id'])
            LOG.info("\tTenant ID: \"%s\"" % site['tenant_id'])
            LOG.info("\tIKE policy ID: \"%s\"" % site['ikepolicy_id'])
            LOG.info("\tIPsec policy ID: \"%s\"" % site['ipsecpolicy_id'])
            LOG.info("\tVPN service ID: \"%s\"" % site['vpnservice_id'])
            LOG.info("\tPeer address: \"%s\"" % site['peer_address'])
            LOG.info("\tRemote net ID: \"%s\"" % site['peer_cidrs'])
            LOG.info("\tStatus: \"%s\"" % site['status'])

    def translate_dialect(self):
        if not self.vpnservice:
            return
        LOG.info("Generating Solaris IKE/IPsec config files.")
        for ipsec_site_conn in self.vpnservice['ipsec_site_connections']:
            self._dialect(ipsec_site_conn, 'initiator')
            self._dialect(ipsec_site_conn['ikepolicy'], 'ike_version')
            for key in ['encryption_algorithm', 'auth_algorithm', 'pfs']:
                self._dialect(ipsec_site_conn['ikepolicy'], key)
                self._dialect(ipsec_site_conn['ipsecpolicy'], key)

    def generate_config(self, vpnservice):
        """Map neutron VPNaaS configuration to Solaris configuration
           files using the templates.
        """
        self.vpnservice = vpnservice
        self.translate_dialect()

    def _dialect(self, obj, key):
        obj[key] = self.DIALECT_MAP.get(obj[key], obj[key])

    @abc.abstractmethod
    def ensure_configs(self):
        pass

    def generate_config_file(self, kind, template, vpnservice):
        """Generate IPsec policy/IKEv1/IKEv2/PSK configuration files.
           This method may get called more than once if there is more
           than one vpn-service object. The configuration data is
           appended to the file in this case.
        """
        LOG.info("Generating \"%s\" config." % kind)
        LOG.debug("Using template file: \"%s\"" % template)
        config_str = self.gen_config_content(template, vpnservice)
        config_file_name = self.get_config_filename(kind)
        LOG.debug("New contents of: \"%s\"" % config_file_name)
        LOG.debug("\n\n%s\n" % config_str)
        with open(config_file_name, 'aw') as confile:
            confile.write(config_str)

    def get_config_filename(self, kind):
        config_dir = self.etc_dir
        return os.path.join(config_dir, kind)

    def create_path(self, dir_path):
        if not os.path.isdir(dir_path):
            os.makedirs(dir_path, 0o755)

    def create_config_dir(self, vpnservice):
        """Create config directory if it does not exist."""
        self.create_path(self.config_dir)
        for subdir in self.CONFIG_DIRS:
            dir_path = os.path.join(self.config_dir, subdir)
            self.create_path(dir_path)

    def gen_config_content(self, template_file, vpnservice):
        """Generate IPsec configuration files using templates.
        """
        template = _get_template(template_file)
        return template.render(
            {'vpnservice': vpnservice,
             'state_path': cfg.CONF.state_path})

    @abc.abstractmethod
    def get_status(self):
        pass

    @property
    def status(self):
        # This sets the status of vpn-service-list
        if self.active:
            return constants.ACTIVE
        return constants.DOWN

    @property
    def active(self):
        """Check to see if IKE is running. The output
            is parsed to update status of ipsec-site-connection.
            If this fails, one of the following happened:
                The IKE daemon crashed.
                The IKE service was disabled from the command line.
                The l3_agent is being shutdown.
        """
        LOG.debug("Getting status of IKE daemon")
        global being_shutdown
        if being_shutdown:
            LOG.info("VPNaaS being shutdown")
            return False

        # IKE is running. Update status of all connections
        # IKE knows about.
        self.get_connection_status()
        return True

    def update(self):
        """Update Status based on vpnservice configuration.
        """
        LOG.debug("update")
        if self.vpnservice and not self.vpnservice['admin_state_up']:
            self.disable()
        else:
            self.enable()

        self.updated_pending_status = True
        self.vpnservice['status'] = self.status

    def enable(self):
        LOG.debug("enable")
        try:
            if self.active:
                self.restart()
            else:
                self.start()
        except RuntimeError:
            LOG.exception(
                ("Failed to enable VPNaaS on router ID: \"%s\""),
                self.id)

    def disable(self):
        LOG.debug("disable")
        try:
            if self.active:
                self.stop()
        except RuntimeError:
            LOG.exception(
                ("Failed to disable VPNaaS on router ID: \"%s\""),
                self.id)

    @abc.abstractmethod
    def restart(self):
        """Restart VPNaaS.
        """

    @abc.abstractmethod
    def start(self):
        """Start VPNaaS.
        """

    @abc.abstractmethod
    def stop(self):
        """Stop VPNaaS.
        """

    def copy_process_status(self, process):
        return {
            'id': process.vpnservice['id'],
            'status': process.status,
            'updated_pending_status': process.updated_pending_status,
            'ipsec_site_connections': copy.deepcopy(process.connection_status)
        }

    def mark_connections(self, new_state):
        """Update the status of all of the ipsec-site-connections.
           Mark all the connections this router knows about as ACTIVE or DOWN.
           The update_pending_status flag is not set. This is
           because we will report status back to the l3 agent directly.
           We don't want the process_status_cache_check() method to change
           it back again.

           This should be revisited if we support more than one router.
        """
        if not self.vpnservice:
            LOG.info("No VPNs configured.")
            return

        status_changed_vpn_services = []
        new_status = self.copy_process_status(self)
        LOG.info("Marking all site connections %s" % new_state)
        for conn in new_status[IPSEC_CONNS]:
            new_status[IPSEC_CONNS][conn] = {
                'status': new_state,
                'updated_pending_status': True
            }
            status_changed_vpn_services.append(new_status)

        self.agent_rpc.update_status(
            self.context,
            status_changed_vpn_services)

    def get_connection_status(self):
        """Update the status of the ipsec-site-connection
           based on the output of ikeadm(1m). See get_status()
           for further comments. Any connections that ended up
           on the badboys list will be marked as state DOWN.
        """
        LOG.debug("Getting Connection Status")
        global being_shutdown
        global restarting

        if not self.vpnservice:
            LOG.info("No VPNs configured.")
            return True

        if restarting:
            LOG.info("IKE restarting")
            return True
        self.ike_was_running = self.ike_running
        if not self.get_status():
            if being_shutdown:
                self.ikeadm_fails = 0
            else:
                LOG.info("IKE daemon is not running.")
                self.ikeadm_fails += 1
            if self.ikeadm_fails > self.ikeadm_maxfails:
                LOG.info("IKE daemon still not running, something's wrong.")
                restarting = True
                being_shutdown = True
                self.mark_connections(constants.DOWN)
                restarting = False
                being_shutdown = False
                self.ikeadm_fails = 0
                self.ike_running = False

            return False

        if self.ike_running and not self.ike_was_running:
            LOG.info("IKE daemon has been restarted")
            self.mark_connections(constants.ACTIVE)
            return True
        for connection_id in self.connection_ids:
            if not self.connection_status.get(connection_id):
                self.connection_status[connection_id] = {
                    'status': None,
                    'tun_id': "",
                    'updated_pending_status': False
                }
            new_status = constants.ACTIVE
            for badboy in self.badboys:
                if badboy['id'] == connection_id:
                    new_status = constants.DOWN

            self.connection_status[connection_id] = {
                'status': new_status,
                'updated_pending_status': True,
            }

        return True


class SolarisIPsecProcess(BaseSolaris):
    """Solaris IPsec Process manager class.
       This class handles the configuration of IKE and IPsec
       on Solaris. The configuration files are generated under the
       standard neutron path:

       /var/lib/neutron/ipsec/<router UUID>/etc/inet

       This is a non default path for the Solaris utilities that read
       these files. Unlike Linux, Solaris services are started by smf(5)
       which passes parameters to the command(s) that make up that service.
       For IPsec there are four services of interest:

       svc:/network/ipsec/ike:default
       svc:/network/ipsec/ike:ikev2
       svc:/network/ipsec/policy:default
       svc:/network/ipsec/policy:logger

       The method service_setprops() sets the smf(5) properties to paths
       based on the path above, so the services know where to find their
       configuration.

       Tunnel configuration is handled externally from IKE. The Solaris
       commands dladm(1m) and ipadm(1m) use used to create the IP tunnels.
       The tunnel name is the glue that binds the IPsec policy to a
       particular tunnel. The tunnel name is based on the outer source and
       destination IP addresses. This is because only one tunnel can exist
       between any pair of addresses. The tunnel may have multiple inner
       IP address pairs.

       The status of the VPN connection is sampled regularly by the
       get_status() method. If any state changes, this is reported back to
       the l3 agent by report_status(), part of the IPsecDriver class.

       get_status() calls the Solaris utility ikeadm(1m) which queries the
       running IKE daemon. It determins that a VPN is ACTIVE if there is an IKE
       rule in place. There may not actually be active IPsec SAs at this point
       because Solaris IPsec connections are established on-demand, not part
       of the start process.

       Solaris commands mentioned above are called directly using pfexec(1).
    """
    def __init__(self, conf, process_id,
                 vpnservice, namespace):
        LOG.info("Configuring IPsec/IKE")
        super(SolarisIPsecProcess, self).__init__(
            conf, process_id,
            vpnservice, namespace)
        self.secrets_file = os.path.join(
            self.etc_dir, 'secret/ike.preshared')
        self.ikev2_secrets_file = os.path.join(
            self.etc_dir, 'ike/ikev2.preshared')
        self.config_file = os.path.join(
            self.etc_dir, 'ipsecinit.conf')
        self.ike_config_file = os.path.join(
            self.etc_dir, 'ike/config')
        self.ikev2_config_file = os.path.join(
            self.etc_dir, 'ike/ikev2.config')
        self.process = process_id
        self.badboys = []
        global being_shutdown
        being_shutdown = False
        self.ike_version = ""
        self.agent_rpc = IPsecVpnDriverApi(topics.IPSEC_DRIVER_TOPIC)
        self.context = context.get_admin_context_without_session()
        self.pf = packetfilter.PacketFilter('_auto/neutron:l3:agent')
        LOG.info("Solaris IPsec/IKE Configuration manager loaded.")

    def ensure_configs(self):
        """Generate config files which are needed for Solaris IPsec/IKE.
        This function will generate the parent directory if needed.
        Set the SMF(5) properties for the policy/IKE services to use
        the configuration files here as opposed to those in /etc/inet.
        """

        connections = self.vpnservice['ipsec_site_connections']
        # This is going to need a lot more work if we ever support IKEv1
        # and IKEv2 at the same time.
        for site in connections:
            self.ike_version = site['ikepolicy']['ike_version']
            LOG.debug("Using IKE service: \"ike:%s\"" % self.ike_version)

        self.create_config_dir(self.vpnservice)
        self.generate_config_file(
            'ipsecinit.conf',
            self.conf.solaris.ipsec_config_template,
            self.vpnservice)
        self.generate_config_file(
            'ike/config',
            self.conf.solaris.ike_config_template,
            self.vpnservice)
        self.generate_config_file(
            'secret/ike.preshared',
            self.conf.solaris.ike_secret_template,
            self.vpnservice)
        self.generate_config_file(
            'ike/ikev2.config',
            self.conf.solaris.ikev2_config_template,
            self.vpnservice)
        self.generate_config_file(
            'ike/ikev2.preshared',
            self.conf.solaris.ikev2_secret_template,
            self.vpnservice)

    def start_ipsec(self):
        self.service_setprops()
        self.enable_smf_services()

    def add_tunnels(self):
        """Add tunnel interfaces using dladm(1m) and
           ipadm(1m).

        """
        connections = self.vpnservice['ipsec_site_connections']
        for site in connections:
            tun_name = site['tunnel_id']
            subnet = self.vpnservice['subnet']
            peer = site['peer_address']
            peer_cidr = str(site['peer_cidrs'][0])
            o_local = self.vpnservice['external_ip']
            o_remote = peer
            i_local = subnet['gateway_ip']
            # Need an address for the tunnel end point.
            # Use the first address of the remote network.
            count = 0
            for i_remote in IPNetwork(peer_cidr):
                count += 1
                if (count == 2):
                    break

            LOG.info("Adding tunnel - tunnel_id: \"%s\"" % tun_name)

            # Add the IP tunnel using dladm(1m). Its possible for more than
            # one IPsec rule to use the same pair of IP addresses for the
            # outer addresses of a tunnel. We can only have a single tunnel
            # between any pair of addresses. So if dladm(1m) fails because
            # the tunnel already exists, we can ignore this error.
            cmd = ['/usr/bin/pfexec', 'dladm', 'create-iptun', '-t', '-T',
                   'ipv4', '-a', "local=%s,remote=%s" % (o_local, o_remote),
                   tun_name]
            try:
                stdout, stderr = processutils.execute(*cmd)
            except processutils.ProcessExecutionError as stderr:
                m = re.search('object already exists', str(stderr))
                if m:
                    LOG.info("Tunnel with Outer IP: %s -> %s, Inner: "
                             "%s -> %s already exists."
                             % (o_local, o_remote, i_local, i_remote))
                else:
                    LOG.info("Error adding tunnel - Outer IP: %s -> %s,"
                             "Inner: %s -> %s"
                             % (o_local, o_remote, i_local, i_remote))
                    LOG.info("\"%s\"" % stderr)
                    self.badboys.append(site)
                    continue

            LOG.info(
                "Added tunnel - Outer IP: %s -> %s, Inner: %s -> %s"
                % (o_local, o_remote, i_local, i_remote))

            cmd = ['/usr/bin/pfexec', 'ipadm', 'create-ip', '-t', tun_name]
            try:
                stdout, stderr = processutils.execute(*cmd)
            except processutils.ProcessExecutionError as stderr:
                if re.search('Interface already exists', str(stderr)):
                    LOG.info("Tunnel interface: '%s' already exists." %
                             tun_name)
                else:
                    LOG.info("Error creating tunnel")
                    LOG.info("\"%s\"" % stderr)
                    self.badboys.append(site)
                    continue
            cmd = ['/usr/bin/pfexec', 'ipadm', 'create-addr', '-t',  '-T',
                   'static', '-a', "local=%s,remote=%s" % (i_local, i_remote),
                   tun_name]
            try:
                stdout, stderr = processutils.execute(*cmd)
            except processutils.ProcessExecutionError as stderr:
                LOG.info("Error creating tunnel")
                LOG.info("\"%s\"" % stderr)
                self.badboys.append(site)
                continue

            cmd = ['/usr/bin/pfexec', 'route', '-n', 'add', 'net', peer_cidr,
                   i_remote]
            LOG.info("Adding route: %s -> %s" % (peer_cidr, i_remote))
            try:
                stdout, stderr = processutils.execute(*cmd)
            except processutils.ProcessExecutionError as stderr:
                m = re.search('entry exists', str(stderr))
                if m:
                    LOG.info("Route already exists.")
                else:
                    LOG.info("Error adding route.")
                    self.badboys.append(site)
                    continue

            # Now for some Policy Based Routing (PBR) voodoo. When a Neutron
            # subnet is added to a Neutron router, it adds a PBR rule that
            # looks like this:
            #
            #    anchor "l3ia18d6189_8_0/*" on l3ia18d6189_8_0 all {
            #      anchor "pbr" all {
            #        pass in inet from any to ! 192.168.80.0/24
            #          route-to 10.132.148.1.1@l3e88c2027b_9_0
            #        }
            #    }
            #
            # What this does is to pass all packets leaving interface
            # "l3ia18d6189_8_0" directly to interface/address
            # "l3e2d9b3c1c_8_0:10.132.148.1" *UNLESS* the packet is destined to
            # "192.168.80.0/24" which is a local address. This allows
            # instances on the virtual network to reach real addresses on the
            # Internet.
            #
            # When we create a VPN to another virtual network, we need to
            # ensure packets destined for that head over the IP tunnel instead.
            # To make this happen, we find the interface associated with our
            # network and add a bypass rule. The rule looks like this:
            #
            # pass in quick on l3ia18d6189_8_0 from any to 192.168.80.0/24
            #
            # There will be one of these pass rules for each remote network.
            # The "quick" keyword ensures it matches *BEFORE* the PBR rule.

            # Find the interfaces names that start with 'l3i and have the IP
            # address that matches the Inner Source IP address of an IP tunnel
            # added by VPNaaS. Add a bypass rule to the sub-anchor for this
            # interface
            cmd = ['/usr/sbin/ipadm', 'show-addr', '-po', 'addrobj,addr']
            p = Popen(cmd, stdout=PIPE, stderr=PIPE)
            output, error = p.communicate()
            ifname = None
            if p.returncode == 0:
                for addrobj_addr in output.strip().splitlines():
                    if ((i_local + '/') in addrobj_addr and
                            addrobj_addr.startswith('l3i')):
                        addrobj = addrobj_addr.split(':')[0]
                        ifname = addrobj.split('/')[0]
                        break
            if not ifname:
                LOG.info("Failed to find IP interface corresponding to "
                         "VPN subnet: %s. Skipping bypass rule for '%s'" %
                         (subnet['cidr'], tun_name))
                continue

            label = 'vpn_%s_%s' % (ifname, peer_cidr.replace('/', '_'))
            bypass_rule = 'pass in quick from any to %s label %s' % \
                (peer_cidr, label)
            anchor_name = 'vpn_%s' % (peer_cidr.replace('/', '_'))
            self.pf.add_rules([bypass_rule], [ifname, anchor_name])
            LOG.debug("Added PBR bypass rule: '%s'" % bypass_rule)

    def get_status(self):
        """Check to see if IKE is configured and running.
           If ikeadm(1m) fails, because in.iked(1m) is not
           running, the vpn-service will be switched from
           ACTIVE to DOWN.

           Each time a new configuration has been loaded the
           IKE daemon service will be restarted. If the restart
           has not yet happened, or is happening now, don't
           report status as it could be stale.

           If the VPN service is being stopped then always
           get the status using ikeadm(1m), even if it's stale.
           This information is used as a best effort to unplumb
           tunnels. The VPN service is stopped when the l3 agent
           smf(5) service is disabled or restarted. It's also
           stopped before new configuration is loaded, then
           restarted.

           Assumption: Only one IKE service is running. If
           we support IKEv1 and IKEv2 at the same time, this
           code will need to be modified to look at rules
           configured for IKEv1 and IKEv2.

           By default the status of the service is checked every 60
           seconds. The interval can be chanmged by setting:

           ipsec_status_check_interval=<new_value>

           under the [solaris] section of vpn_agent.ini .

           Cache a list of ipsec-site-connections based on output of
           ikeadm(1m). We are looking for the line in an IKE rule that
           contains the tag "Label". The value following this will be the
           connection_id.

           If ikeadm fails, list of connection_ids is unchanged.
        """
        LOG.debug("Looking for IPsec site connections.")
        cmd = ['/usr/bin/pfexec', '/usr/sbin/ikeadm', '-n', 'dump', 'rule']
        try:
            status, stderr = processutils.execute(*cmd)
        except processutils.ProcessExecutionError as stderr:
            LOG.info("IKE daemon does not appear to be running.")
            LOG.debug("\"%s\"" % stderr)
            return False

        self.ikeadm_fails = 0
        self.connection_ids = []
        for line in status.split('\n'):
            m = re.search('Label', line)
            if not m:
                continue
            m = line.split('\'')
            connection_id = m[1]
            LOG.debug("IKE rule found for: \"%s\"" % connection_id)
            self.connection_ids.append(connection_id)

        self.ike_running = True
        return True

    def restart(self):
        """Restart VPNaaS.
           Some optimization possible here, a restart does not
           require property setting. If we are not running, we
           don't need to disable stuff. See self.start(), self.stop()
        """
        LOG.info("Restarting VPNaaS")
        self.stop()
        self.start()
        return

    def start(self):
        """Start VPNaaS.
        """
        LOG.info("Start")
        if not self.vpnservice:
            LOG.info("No VPNs configured.")
            return

        LOG.info("Starting VPNaaS")
        self.ensure_configs()
        self.add_tunnels()

    def stop(self):
        self.connection_status = {}

        self.get_status()
        self.flush_sas()
        self.mark_connections(constants.DOWN)
        LOG.debug("Disable IPsec policy and IKE SMF(5) services")
        disable_smf_services()

    def flush_sas(self):
        """Flush IPsec SAs, this should be done with rad(1) eventually.
           For disable ignore any errors.
        """
        LOG.info("Flushing IPsec SAs.")
        cmd = ['/usr/bin/pfexec', '/usr/sbin/ipseckey', 'flush']
        try:
            stdout, stderr = processutils.execute(*cmd)
        except processutils.ProcessExecutionError as stderr:
            LOG.debug("\"%s\"" % stderr)

    def service_setprops(self):
        """Enable IPsec Policy/IKE smf(5) services using rad(1)
        """

        rad_connection = rad.connect.connect_unix()

        LOG.info(
            "Setting IPsec policy config file to: \"%s\"" % self.config_file)
        instance = rad_connection.get_object(
            smfb.Instance(),
            rad.client.ADRGlobPattern({'service': self.ipsec_svc,
                                       'instance': 'default'}))
        instance.writeProperty('config/config_file', smfb.PropertyType.ASTRING,
                               [self.config_file])
        instance.refresh()

        LOG.info("Setting IKEv1 config file to: \"%s\"" % self.ike_config_file)
        instance = rad_connection.get_object(
            smfb.Instance(),
            rad.client.ADRGlobPattern({'service': self.ike_svc,
                                       'instance': 'default'}))
        instance.writeProperty('config/config_file', smfb.PropertyType.ASTRING,
                               [self.ike_config_file])

        LOG.info("Setting IKEv1 PSK file to: \"%s\"" % self.secrets_file)
        instance.writeProperty('config/preshared_file',
                               smfb.PropertyType.ASTRING, [self.secrets_file])
        instance.refresh()

        LOG.info(
            "Setting IKEv2 config file to: \"%s\"" % self.ikev2_config_file)
        instance = rad_connection.get_object(
            smfb.Instance(),
            rad.client.ADRGlobPattern({'service': self.ike_svc,
                                       'instance': 'ikev2'}))
        instance.writeProperty('config/config_file', smfb.PropertyType.ASTRING,
                               [self.ikev2_config_file])

        LOG.info("Setting IKEv2 PSK file to: \"%s\"" % self.ikev2_secrets_file)
        instance.writeProperty('config/preshared_file',
                               smfb.PropertyType.ASTRING,
                               [self.ikev2_secrets_file])
        instance.refresh()

        if self.packet_logging:
            LOG.info(
                "Setting IPsec policy logger to: \"%s\"" % self.logging_level)
            instance = rad_connection.get_object(
                smfb.Instance(),
                rad.client.ADRGlobPattern({'service': self.ipsec_svc,
                                           'instance': 'logger'}))
            instance.writeProperty('config/log_level',
                                   smfb.PropertyType.ASTRING,
                                   [self.logging_level])
            instance.refresh()

        rad_connection.close()

    def enable_smf_services(self):
        """Enable IPsec Policy/IKE smf(5) services using rad(1).
        """
        LOG.info("Enabling IPsec policy.")
        rad_connection = rad.connect.connect_unix()
        instance = rad_connection.get_object(
            smfb.Instance(),
            rad.client.ADRGlobPattern({'service': self.ipsec_svc,
                                       'instance': 'default'}))
        instance.enable(True)

        LOG.info("Enabling IKE version \"%s\"" % self.ike_version)
        instance = rad_connection.get_object(
            smfb.Instance(),
            rad.client.ADRGlobPattern({'service': self.ike_svc,
                                       'instance': self.ike_version}))
        instance.enable(True)

        if self.packet_logging:
            LOG.info("Enabling IPsec packet logger.")
            instance = rad_connection.get_object(
                smfb.Instance(),
                rad.client.ADRGlobPattern({'service': self.ipsec_svc,
                                           'instance': 'logger'}))
            instance.enable(True)

        rad_connection.close()
        global restarting
        restarting = False
        self.ike_running = True


class IPsecVpnDriverApi(object):
    """IPSecVpnDriver RPC api."""
    def __init__(self, topic):
        target = oslo_messaging.Target(topic=topic, version='1.0')
        self.client = n_rpc.get_client(target)

    def get_vpn_services_on_host(self, context, host):
        """Get list of vpnservices.

           The vpnservices including related ipsec_site_connection,
           ikepolicy and ipsecpolicy on this host
        """
        LOG.debug("Server requested status from router.")
        cctxt = self.client.prepare()
        return cctxt.call(context, 'get_vpn_services_on_host', host=host)

    def update_status(self, context, status):
        """Update local status.
            This method call updates status attribute of
            VPNServices.
        """
        LOG.debug("Current site status: \"%s\"" % status)
        cctxt = self.client.prepare()
        return cctxt.call(context, 'update_status', status=status)


@six.add_metaclass(abc.ABCMeta)
class IPsecDriver(device_drivers.DeviceDriver):
    """Methods in this class are called by the l3 agent.

       Check to see if VPNaaS is enabled in neutron.conf. If it's
       not, just return and don't start the looping event.

       The code here generates IPsec/IKE configuration
       for Solaris. There is a looping event which periodically
       runs and, if state has changed this is reported back to the
       l3 agent.

       The looping method calls get_status() at a regular interval.
       The interval (in seconds) is defined by:

       ipsec_status_check_interval

       See solaris_opts for more details

       References to "process" are a little misleading. This code
       is not managing processes, its managing the IPsec/IKE
       configuration on a router.

       For the purposes of this code:

       router_id == process_id

       This code is called once when the service is started. Variables
       are valid until the service is disabled.
    """
    RPC_API_VERSION = '1.0'

    target = oslo_messaging.Target(version=RPC_API_VERSION)

    def __init__(self, vpn_service, host):
        self.conf = vpn_service.conf
        self.host = host
        self.conn = n_rpc.create_connection(new=True)
        self.context = context.get_admin_context_without_session()
        self.topic = topics.IPSEC_AGENT_TOPIC
        node_topic = '%s.%s' % (self.topic, self.host)
        not_configured = True

        config = iniparse.RawConfigParser()
        try:
            config.read('/etc/neutron/neutron.conf')
        except:
            LOG.info("Unable to read /etc/neutron/neutron.conf")
            sys.exit(1)

        try:
            vpnaas = config.get('DEFAULT', 'service_plugins')
            for arg in vpnaas.split(","):
                if re.match(r'\bvpnaas\b', arg):
                    not_configured = False
                    break
        except:
            pass

        if not_configured:
            LOG.info("VPNaaS has not been configured.")
            return

        self.processes = {}
        self.process_status_cache = {}

        self.endpoints = [self]
        self.conn.create_consumer(node_topic, self.endpoints, fanout=False)
        self.conn.consume_in_threads()

        self.agent_rpc = IPsecVpnDriverApi(topics.IPSEC_DRIVER_TOPIC)
        self.process_status_cache_check = loopingcall.FixedIntervalLoopingCall(
            self.report_status, self.context)
        LOG.info("Value of \"ipsec_status_check_interval\": \"%s\" Seconds." %
                 cfg.CONF.solaris.ipsec_status_check_interval)
        self.process_status_cache_check.start(
            interval=cfg.CONF.solaris.ipsec_status_check_interval)
        LOG.info("Solaris status reporting driver started.")

    def vpnservice_updated(self, context, **kwargs):
        """VPN Service Driver will call this method
           when VPN configuration objects have been modified. This
           will call sync(), which will restart the device driver.
        """
        self.sync(context, [])

    def report_status(self, context):
        """This code is called when a new configuration is loaded, via sync().
           It is also called periodically every ipsec_status_check_interval
           seconds. If state has changed, report this back to the l3 agent.

           Solaris currently only supports a single router.

           The connection cache contains a list of the ipsec-site-connection's
           that are in the neutron server configuration. This may differ from
           what is actually configured.

           The connection cache contains a list of the ipsec-site-connection's
           that are in the neutron server configuration. This may differ from
           what is actually configured.

           "process" is misleading, its really refers to a router.
        """
        global being_shutdown
        if being_shutdown:
            LOG.debug("Being shutdown - skipping VPNaaS status report.")
            return

        LOG.info("Getting VPNaaS status")
        status_changed_vpn_services = []

        for process in self.processes.values():
            previous_status = self.get_process_status_cache(process)
            if self.has_status_changed(process, previous_status):
                LOG.info(
                    "Status of router ID: \"%s\" has changed." % process.id)
                new_status = self.copy_process_status(process)

                if not self.check_connection_cache(process, new_status):
                    LOG.debug("Connection Cache has been updated.")

                status_changed_vpn_services.append(new_status)

                self.unset_updated_pending_status(process)
                self.unset_cache_status(process)
                self.process_status_cache[process.id] = (
                    self.copy_process_status(process))

        if status_changed_vpn_services:
            LOG.info("Status of VPN services have changed %s" %
                     status_changed_vpn_services)
            self.agent_rpc.update_status(context, status_changed_vpn_services)

    @lockutils.synchronized('vpn-agent', 'neutron-')
    @abc.abstractmethod
    def create_process(self, process_id, vpnservice, namespace):
        pass

    def enable_vpn(self, process_id, vpnservice=None):
        """Configure IPsec, IKE, tunnels on this router.
        """
        LOG.info("Configuring VPNaaS on router: \"%s\"" % process_id)
        if not vpnservice:
            LOG.info("No VPNs configured")
            return

        process = self.processes.get(process_id)
        if not process or not process.namespace:
            namespace = ""
            process = self.create_process(
                process_id,
                vpnservice,
                namespace)
            self.processes[process_id] = process
        elif vpnservice:
            process.generate_config(vpnservice)

        return process

    def create_router(self, process_id):
        """"Handling create router event.
        """
        try:
            if process_id in self.processes:
                process = self.processes[process_id]
                LOG.info("Creating router ID: \"%s\"" % process)
                process.enable()
        except:
            pass

    def destroy_router(self, process_id):
        """Handling destroy_router event.
        """
        LOG.info("Destroying router ID: \"%s\"" % process_id)
        try:
            processes = self.processes
        except:
            return

        if process_id in processes:
            process = processes[process_id]
            process.disable()
            vpnservice = process.vpnservice
            del processes[process_id]

    def get_process_status_cache(self, process):
        if not self.process_status_cache.get(process.id):
            self.process_status_cache[process.id] = {
                'status': None,
                'id': process.vpnservice['id'],
                'updated_pending_status': False,
                'ipsec_site_connections': {}}
        return self.process_status_cache[process.id]

    def has_status_changed(self, process, previous_status):
        """Get the current status from ikeadm(1m). Note that
           process.status *calls* active.
           There is a lot of debug here, because if this function fails
           nothing gets updated.
        """
        if process.updated_pending_status:
            LOG.debug("Status of VPN services have changed")
            return True

        if process.status != previous_status['status']:
            LOG.debug("Current Router status != Previous status")
            LOG.debug("%s/%s" % (process.status, previous_status['status']))
            return True
        ps = previous_status['ipsec_site_connections']
        if process.connection_status != ps:
            LOG.debug("Current VPN status != Previous status")
            LOG.debug("%s/%s" % (process.connection_status, ps))
            return True

        found_previous_connection = False

        ps = previous_status['ipsec_site_connections']
        for ipsec_site_conn in ps.keys():
            LOG.debug("Site connection ID: \"%s\" State: \"%s[%s]\"" %
                      (ipsec_site_conn, ps[ipsec_site_conn]['status'],
                       ps[ipsec_site_conn]['updated_pending_status']))
            found_previous_connection = False

            for new_ipsec_site_conn in process.connection_ids:
                if ipsec_site_conn == new_ipsec_site_conn:
                    LOG.debug("Found existing entry for ID: '%s'" %
                              new_ipsec_site_conn)
                    found_previous_connection = True
            if not found_previous_connection:
                LOG.debug("Unable to find existing entry for ID: '%s'" %
                          ipsec_site_conn)
                ps[ipsec_site_conn]['status'] = constants.DOWN
                ps[ipsec_site_conn]['updated_pending_status'] = True
                return True
            continue

        return False

    def unset_cache_status(self, process):
        self.process_status_cache[process.id]['updated_pending_status'] = False
        cache = self.process_status_cache[process.id]
        for pending in cache['ipsec_site_connections'].values():
            pending['updated_pending_status'] = False

    def unset_updated_pending_status(self, process):
        process.updated_pending_status = False
        for connection_status in process.connection_status.values():
            LOG.debug("Unset Pending Status %s" % connection_status)
            connection_status['updated_pending_status'] = False

    def copy_process_status(self, process):
        return {
            'id': process.vpnservice['id'],
            'status': process.status,
            'updated_pending_status': process.updated_pending_status,
            'ipsec_site_connections': copy.deepcopy(process.connection_status)
        }

    def check_connection_cache(self, process, new_status):
        """Verify the site connection cache.

           This is called as a result of a sync() from the l3 agent.
           The new configuration may differ from the current content
           of the cache. If an ipsec-site-connection exists in the cache
           but is no longer part of the new configuration (ie: it was
           deleted) report this ipsec-site-connection as DOWN.

           Note process_id is really the router UUID.
        """
        process_id = process.id
        return_value = True
        if process_id in self.process_status_cache:
            LOG.debug(
                "Checking connection cache of router ID: \"%s\"" % process_id)
            stale_entries = []
            cache = self.process_status_cache[process_id]
            if not cache[IPSEC_CONNS]:
                LOG.debug("No cache")
                return False

            for site_conn in cache[IPSEC_CONNS]:
                status = cache[IPSEC_CONNS][site_conn]['status']
                LOG.debug(
                    "Cache has [%s] entry for site ID: \"%s\""
                    % (status, site_conn))
                if site_conn not in process.connection_ids:
                    LOG.info(
                        "Site connection \"%s\" appears to have been deleted."
                        % site_conn)
                    return_value = False
                    new_status[IPSEC_CONNS][site_conn] = {
                        'status': constants.DOWN,
                        'updated_pending_status': True
                    }
                    stale_entries.append(site_conn)

            if stale_entries:
                for badboy in stale_entries:
                    LOG.debug("Remove stale entry from connection cache: %s" %
                              badboy)
                    cache[IPSEC_CONNS].pop(badboy)

        return return_value

    @lockutils.synchronized('vpn-agent', 'neutron-')
    def sync(self, context, routers):
        """Sync is called by the server side of neutron.
           This will be called whenever new configuration is
           delivered from the server. This forces the underlying
           IPsec/IKE services to be disabled and restarted with
           freshly generated configuration files.

           Follow process.update() to see what happens.

           The terminology "process" is very misleading. It in fact
           is a reference to a router object.

           The code below loops through the list of routers configured
           and enables the VPNs on them. Currently Solaris only supports
           a single router in Neutron. It will be a short list ...

           We no longer have access to the previous configuration. The new
           configuration may well be different, so we have to delete
           existing configuration and tear down any tunnels. The tunnel
           configuration is not part of IPsec/IKE. Tunnel interfaces do
           not go away when IPsec/IKE services are restarted. A global
           list existing_tunnels[] is used to cache the tunnels created.

           The first time the driver is loaded, when the service is first
           started, this list will be empty. The smf(5) start method checks
           to see if there are any stray tunnels.

           Remove all configuration files under <router_UUID>.
           This directory structure is only used by the VPNaaS driver. It's
           recreated every time the driver is loaded, or new configuration is
           sent to the driver. Any errors generated deleting this directory
           structure can be safely ignored.

           The vpn-service object does not have the tunnel id, which
           we need for Solaris tunnels. We will add it here.
           Solaris tunnel names (see dladm(1m)) must start with an
           alphabetic character and end with a decimal number and
           be unique.

           Solaris tunnels are not part of the IPsec/IKE configuration.
           The glue between the IPsec policy and tunnels is the name
           of the tunnel. The tunnel interface is created with dladm(1m).
           If there are multiple VPNs using the same outer tunnel IP addresses
           then they will share the same tunnel. To ensure that only one
           tunnel is created between any pair of addresses, the tunnel name
           is constructed as follows:

           vpn_x_site_y

           Where x is a decimal index number which is unique for each local
           external IP address used as the outer source for a tunnel. Typically
           this will only be a single IP address as each neutron router only
           has a single external IP address. But this could change in the
           future.

           The decimal index y is unique per IKE peer. There may be more than
           one set of inner addresses on each tunnel.

           The output below shows the tunnels for a setup that has a local site
           with two virtual subnets and two remote sites. One of the remote
           sites has two remote subnets. The combination of two local subnets
           and three remote subnets results in six ipsec-site-connections
           and six tunnels on two data-link tunnels.

           vpn_0_site_1      ip         ok   --  --
              vpn_0_site_1/v4 static    ok   -- 192.168.90.1->192.168.40.1
              vpn_0_site_1/v4a static   ok   -- 192.168.80.1->192.168.40.1
           vpn_0_site_2      ip         ok   -- --
              vpn_0_site_2/v4 static    ok   -- 192.168.90.1->192.168.100.1
              vpn_0_site_2/v4a static   ok   -- 192.168.90.1->192.168.101.1
              vpn_0_site_2/v4b static   ok   -- 192.168.80.1->192.168.100.1
              vpn_0_site_2/v4c static   ok   -- 192.168.80.1->192.168.101.1
        """
        try:
            LOG.info("Getting VPN configuration from neutron")
            vpnservices = self.agent_rpc.get_vpn_services_on_host(
                context, self.host)
        except:
            LOG.info("VPNaaS not enabled.")
            return

        router_ids = [vpnservice['router_id'] for vpnservice in vpnservices]
        global existing_tunnels
        delete_tunnels(existing_tunnels)
        whack_ike_rules()
        existing_tunnels = []

        # Remove old configuration files.
        try:
            shutil.rmtree(os.path.join(cfg.CONF.solaris.config_base_dir,
                          vpnservice['router_id']))
        except:
            pass

        # Add tunnel_id's
        local_ips = {}
        remote_ips = {}
        vpn_cnt = 0
        site_cnt = 0

        # If there are no vpn-services defined, we can bail out here.
        # But we still need to check and delete any sub-processes that
        # may have been created last time sync() was called.
        if not vpnservices:
            LOG.info("No VPNs configured")
            for process in self.processes:
                del process
            self.process_status_cache['process_id'] = {}
            self.processes = {}
            disable_smf_services()
            return

        for vpnservice in vpnservices:
            ex_ip = vpnservice['external_ip']
            l_id = local_ips.get(ex_ip)

            if not l_id:
                l_id = "vpn_%d" % vpn_cnt
                vpn_cnt += 1
                local_ips[ex_ip] = l_id

            for ipsec_site_conn in vpnservice['ipsec_site_connections']:
                peer_ip = ipsec_site_conn['peer_address']
                r_id = remote_ips.get(peer_ip)

                if not r_id:
                    site_cnt += 1
                    r_id = "site_%d" % site_cnt
                    remote_ips[peer_ip] = r_id

                tun_name = "%s_%s" % (l_id, r_id)
                ipsec_site_conn['tunnel_id'] = tun_name
                LOG.debug("Added tunnel \"%s\" to vpn-service: %s" %
                          (tun_name, vpnservice['id']))
                # Next time we restart, these tunnels will be removed.
                if tun_name not in existing_tunnels:
                    existing_tunnels.append(tun_name)

        new_vpnservice_status = []

        for vpnservice in vpnservices:
            process = self.enable_vpn(
                vpnservice['router_id'], vpnservice=vpnservice)
            self.vpnservice = vpnservice
            process.update()
            new_status = {
                'id': vpnservice['id'],
                'status': constants.ACTIVE,
                'updated_pending_status': True,
                'ipsec_site_connections': {}
            }
            new_vpnservice_status.append(new_status)

        LOG.debug("Updating status of all vpnservices: %s" %
                  new_vpnservice_status)
        self.agent_rpc.update_status(
            self.context, new_vpnservice_status)

        # Call start routine that sets up tunnels and
        # enables smf(5) services.
        process.start_ipsec()


class SolarisIPsecDriver(IPsecDriver):
    def create_process(self, process_id, vpnservice, namespace):
        LOG.debug("SolarisIPsec Driver loaded.")
        return SolarisIPsecProcess(
            self.conf,
            process_id,
            vpnservice,
            namespace)
