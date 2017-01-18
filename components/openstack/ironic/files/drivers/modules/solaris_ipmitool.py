# vim: tabstop=4 shiftwidth=4 softtabstop=4
#
# Copyright 2012 Hewlett-Packard Development Company, L.P.
# Copyright (c) 2012 NTT DOCOMO, INC.
# Copyright 2014 International Business Machines Corporation
# All Rights Reserved.
#
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
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
"""
Solaris Driver and supporting meta-classes.
"""

import errno
import os
import platform
import re
import select
import shutil
import socket
from subprocess import Popen, PIPE
import tempfile
from threading import Thread
import time
import urllib2
from urlparse import urlparse

from lockfile import LockFile, LockTimeout
from oslo_concurrency import processutils
from oslo_config import cfg
from oslo_log import log as logging
from oslo_service import loopingcall
from oslo_utils import excutils, strutils
from scp import SCPClient
import six

from ironic.common import boot_devices, exception, images, keystone, states, \
    utils
from ironic.common.i18n import _, _LE, _LI, _LW
from ironic.conductor import task_manager
from ironic.conductor import utils as manager_utils
from ironic.db import api as dbapi
from ironic.drivers import base
from ironic.drivers.modules import ipmitool
from ironic.drivers import utils as driver_utils
from ironic import objects

PLATFORM = platform.system()
if PLATFORM != "SunOS":
    import tarfile
    IPMITOOL = '/usr/bin/ipmitool'
else:
    from pkg.fmri import IllegalFmri, PkgFmri
    from pkg.misc import valid_pub_prefix, valid_pub_url
    IPMITOOL = '/usr/sbin/ipmitool'

AI_OPTS = [
    cfg.StrOpt('server',
               help='Host name for AI Server.'),
    cfg.StrOpt('username',
               help='Username to ssh to AI Server.'),
    cfg.StrOpt('password',
               help='Password for user to ssh to AI Server. If ssh_key_file '
                    'or ssh_key_contents are set, this config setting is used '
                    'to provide the passphrase if required. If an encrypted '
                    'key is used, set this to the passphrase.'),
    cfg.StrOpt('port',
               default='22',
               help='SSH port to use.'),
    cfg.StrOpt('timeout',
               default='10',
               help='SSH socket timeout value in seconds.'),
    cfg.StrOpt('deploy_interval',
               default='10',
               help='Interval in seconds to check AI deployment status.'),
    cfg.StrOpt('derived_manifest',
               default='file:///usr/lib/ironic/ironic-manifest.ksh',
               help='Derived Manifest used for deployment.'),
    cfg.StrOpt('ssh_key_file',
               help='SSH Filename to use.'),
    cfg.StrOpt('ssh_key_contents',
               help='Actual SSH Key contents to use.')
    ]

SOLARIS_IPMI_OPTS = [
    cfg.StrOpt('imagecache_dirname',
               default='/var/lib/ironic/images',
               help='Default path to image cache.'),
    cfg.StrOpt('imagecache_lock_timeout',
               default='60',
               help='Timeout to wait when attempting to lock refcount file.')
]

LOG = logging.getLogger(__name__)

CONF = cfg.CONF
OPT_GROUP = cfg.OptGroup(name='ai',
                         title='Options for the Solaris driver')
CONF.register_group(OPT_GROUP)
CONF.register_opts(AI_OPTS, OPT_GROUP)
SOLARIS_IPMI_GROUP = cfg.OptGroup(
    name="solaris_ipmi",
    title="Options defined in ironic.drivers.modules.solaris_ipmi")
CONF.register_group(SOLARIS_IPMI_GROUP)
CONF.register_opts(SOLARIS_IPMI_OPTS, SOLARIS_IPMI_GROUP)

VALID_ARCH = ['x86', 'SPARC']
VALID_ARCHIVE_SCHEMES = ["file", "http", "https", "glance"]
VALID_URI_SCHEMES = VALID_ARCHIVE_SCHEMES
DEFAULT_ARCHIVE_IMAGE_PATH = 'auto_install/manifest/default_archive.xml'
AI_STRING = "Automated Installation"
AI_SUCCESS_STRING = AI_STRING + " succeeded"
AI_FAILURE_STRING = AI_STRING + " failed"
AI_DEPLOY_STRING = AI_STRING + " started"

REQUIRED_PROPERTIES = {
    'ipmi_address': _("IP address or hostname of the node. Required."),
    'ipmi_username': _("username to use for IPMI connection. Required."),
    'ipmi_password': _("password to use for IPMI connection. Required.")
}

OPTIONAL_PROPERTIES = {
    'ai_manifest': _("Automated install manifest to be used for provisioning. "
                     "Optional."),
    'ai_service': _("Automated Install service name to use. Optional."),
    'archive_uri': _("URI of archive to deploy. Optional."),
    'fmri': _("List of IPS package FMRIs to be installed. "
              "Required if publishers property is set."),
    'install_profiles': _("List of configuration profiles to be applied "
                          "to the installation environment during an install. "
                          "Optional."),
    'publishers': _("List of IPS publishers to install from, in the format "
                    "name@origin. Required if fmri property is set."),
    'sc_profiles': _("List of system configuration profiles to be applied "
                     "to an installed system. Optional."),

    'ipmi_port': _("remote IPMI RMCP port. Optional."),
    'ipmi_priv_level':
        _("privilege level; default is ADMINISTRATOR. "
          "One of %s. Optional.") % '. '.join(ipmitool.VALID_PRIV_LEVELS),
    'ipmi_bridging': _("bridging_type; default is \"no\". One of \"single\", "
                       "\"dual\", \"no\". Optional."),
    'ipmi_transit_channel': _("transit channel for bridged request. Required "
                              "only if ipmi_bridging is set to \"dual\"."),
    'ipmi_transit_address': _("transit address for bridged request. Required "
                              "only if ipmi_bridging is set to \"dual\"."),
    'ipmi_target_channel': _("destination channel for bridged request. "
                             "Required only if ipmi_bridging is set to "
                             "\"single\" or \"dual\"."),
    'ipmi_target_address': _("destination address for bridged request. "
                             "Required only if ipmi_bridging is set "
                             "to \"single\" or \"dual\"."),
    'ipmi_local_address': _("local IPMB address for bridged requests. "
                            "Used only if ipmi_bridging is set "
                            "to \"single\" or \"dual\". Optional."),
    'ipmi_protocol_version': _('the version of the IPMI protocol; default '
                               'is "2.0". One of "1.5", "2.0". Optional.'),
    'ipmi_force_boot_device': _("Whether Ironic should specify the boot "
                                "device to the BMC each time the server "
                                "is turned on, eg. because the BMC is not "
                                "capable of remembering the selected boot "
                                "device across power cycles; default value "
                                "is False. Optional.")
}

COMMON_PROPERTIES = REQUIRED_PROPERTIES.copy()
COMMON_PROPERTIES.update(OPTIONAL_PROPERTIES)

IPMI_PROPERTIES = [
    ('mac', '/System/host_primary_mac_address'),
    ('serial', '/System/serial_number'),
    ('model', '/System/model'),
    ('cpu_arch', '/System/Processors/architecture'),
    ('memory_mb', '/System/Memory/installed_memory'),
    ('cpus', '/System/Processors/installed_cpus'),
    ('datalinks', '/System/Networking/installed_eth_nics'),
    ('disks', '/System/Storage/installed_disks'),
    ('local_gb', '/System/Storage/installed_disk_size')
]

CPU_LOCATION = '/System/Processors/CPUs/CPU_%d/total_cores'

LAST_CMD_TIME = {}


def _ssh_execute(ssh_obj, ssh_cmd, raise_exception=True, err_msg=None):
    """Execute a command via SSH.

    :param ssh_obj: paramiko.SSHClient, an active ssh connection
    :param ssh_cmd: Command to execute over SSH.
    :param raise_exception: Wheter to raise exception or not
    :param err_msg: Custom error message to use
    :returns: tuple [stdout from command, returncode]
    :raises: SSHCommandFailed on an error from ssh, if specified to raise.
    """
    LOG.debug("_ssh_execute():ssh_cmd: %s" % (ssh_cmd))

    returncode = 0
    stdout = None
    try:
        stdout = processutils.ssh_execute(ssh_obj, ssh_cmd)[0]
    except Exception as err:
        LOG.error(_LE("Cannot execute SSH cmd %(cmd)s. Reason: %(err)s.") %
                  {'cmd': ssh_cmd, 'err': err})
        returncode = 1
        if raise_exception:
            if err_msg:
                raise SolarisIPMIError(msg=err_msg)
            else:
                raise exception.SSHCommandFailed(cmd=ssh_cmd)

    return stdout, returncode


def _parse_driver_info(node):
    """Gets the parameters required for ipmitool to access the node.

    Copied from ironic/drivers/modules/ipmitool.py. No differences.
    Copied locally as REQUIRED_PROPERTIES differs from standard ipmitool.

    :param node: the Node of interest.
    :returns: dictionary of parameters.
    :raises: InvalidParameterValue when an invalid value is specified
    :raises: MissingParameterValue when a required ipmi parameter is missing.

    """
    LOG.debug("_parse_driver_info()")
    info = node.driver_info or {}
    bridging_types = ['single', 'dual']
    missing_info = [key for key in REQUIRED_PROPERTIES if not info.get(key)]
    if missing_info:
        raise exception.MissingParameterValue(_(
            "Missing the following IPMI credentials in node's"
            " driver_info: %s.") % missing_info)

    address = info.get('ipmi_address')
    username = info.get('ipmi_username')
    password = six.text_type(info.get('ipmi_password', ''))
    dest_port = info.get('ipmi_port')
    port = info.get('ipmi_terminal_port')
    priv_level = info.get('ipmi_priv_level', 'ADMINISTRATOR')
    bridging_type = info.get('ipmi_bridging', 'no')
    local_address = info.get('ipmi_local_address')
    transit_channel = info.get('ipmi_transit_channel')
    transit_address = info.get('ipmi_transit_address')
    target_channel = info.get('ipmi_target_channel')
    target_address = info.get('ipmi_target_address')
    protocol_version = str(info.get('ipmi_protocol_version', '2.0'))
    force_boot_device = info.get('ipmi_force_boot_device', False)

    if not username:
        LOG.warning(_LW('ipmi_username is not defined or empty for node %s: '
                        'NULL user will be utilized.') % node.uuid)
    if not password:
        LOG.warning(_LW('ipmi_password is not defined or empty for node %s: '
                        'NULL password will be utilized.') % node.uuid)

    if protocol_version not in ipmitool.VALID_PROTO_VERSIONS:
        valid_versions = ', '.join(ipmitool.VALID_PROTO_VERSIONS)
        raise exception.InvalidParameterValue(_(
            "Invalid IPMI protocol version value %(version)s, the valid "
            "value can be one of %(valid_versions)s") %
            {'version': protocol_version, 'valid_versions': valid_versions})

    if port is not None:
        port = utils.validate_network_port(port, 'ipmi_terminal_port')

    if dest_port is not None:
        dest_port = utils.validate_network_port(dest_port, 'ipmi_port')

    # check if ipmi_bridging has proper value
    if bridging_type == 'no':
        # if bridging is not selected, then set all bridging params to None
        (local_address, transit_channel, transit_address, target_channel,
         target_address) = (None,) * 5
    elif bridging_type in bridging_types:
        # check if the particular bridging option is supported on host
        if not ipmitool._is_option_supported('%s_bridge' % bridging_type):
            raise exception.InvalidParameterValue(_(
                "Value for ipmi_bridging is provided as %s, but IPMI "
                "bridging is not supported by the IPMI utility installed "
                "on host. Ensure ipmitool version is > 1.8.11"
            ) % bridging_type)

        # ensure that all the required parameters are provided
        params_undefined = [param for param, value in [
            ("ipmi_target_channel", target_channel),
            ('ipmi_target_address', target_address)] if value is None]
        if bridging_type == 'dual':
            params_undefined2 = [param for param, value in [
                ("ipmi_transit_channel", transit_channel),
                ('ipmi_transit_address', transit_address)
            ] if value is None]
            params_undefined.extend(params_undefined2)
        else:
            # if single bridging was selected, set dual bridge params to None
            transit_channel = transit_address = None

        # If the required parameters were not provided,
        # raise an exception
        if params_undefined:
            raise exception.MissingParameterValue(_(
                "%(param)s not provided") % {'param': params_undefined})
    else:
        raise exception.InvalidParameterValue(_(
            "Invalid value for ipmi_bridging: %(bridging_type)s,"
            " the valid value can be one of: %(bridging_types)s"
        ) % {'bridging_type': bridging_type,
             'bridging_types': bridging_types + ['no']})

    if priv_level not in ipmitool.VALID_PRIV_LEVELS:
        valid_priv_lvls = ', '.join(ipmitool.VALID_PRIV_LEVELS)
        raise exception.InvalidParameterValue(_(
            "Invalid privilege level value:%(priv_level)s, the valid value"
            " can be one of %(valid_levels)s") %
            {'priv_level': priv_level, 'valid_levels': valid_priv_lvls})

    return {
        'address': address,
        'dest_port': dest_port,
        'username': username,
        'password': password,
        'port': port,
        'uuid': node.uuid,
        'priv_level': priv_level,
        'local_address': local_address,
        'transit_channel': transit_channel,
        'transit_address': transit_address,
        'target_channel': target_channel,
        'target_address': target_address,
        'protocol_version': protocol_version,
        'force_boot_device': force_boot_device
    }


def _exec_ipmitool(driver_info, command):
    """Execute the ipmitool command.

    This uses the lanplus interface to communicate with the BMC device driver.

    Copied from ironic/drivers/modules/ipmitool.py. Only one difference.
    ipmitool.py version expects a string of space separated commands, and
    it splits this into an list using 'space' as delimiter.
    This causes setting of bootmode script for SPARC network boot to fail.
    Solaris versions takes a list() as command paramater, and therefore
    we don't need to split.

    :param driver_info: the ipmitool parameters for accessing a node.
    :param command: list() : the ipmitool command to be executed.
    :returns: (stdout, stderr) from executing the command.
    :raises: PasswordFileFailedToCreate from creating or writing to the
             temporary file.
    :raises: processutils.ProcessExecutionError from executing the command.

    """
    LOG.debug("SolarisDeploy._exec_ipmitool:driver_info: '%s', "
              "command: '%s'" % (driver_info, command))
    ipmi_version = ('lanplus'
                    if driver_info['protocol_version'] == '2.0'
                    else 'lan')
    args = [IPMITOOL,
            '-I',
            ipmi_version,
            '-H',
            driver_info['address'],
            '-L', driver_info['priv_level']
            ]

    if driver_info['dest_port']:
        args.append('-p')
        args.append(driver_info['dest_port'])

    if driver_info['username']:
        args.append('-U')
        args.append(driver_info['username'])

    for name, option in ipmitool.BRIDGING_OPTIONS:
        if driver_info[name] is not None:
            args.append(option)
            args.append(driver_info[name])

    # specify retry timing more precisely, if supported
    num_tries = max(
        (CONF.ipmi.retry_timeout // CONF.ipmi.min_command_interval), 1)

    if ipmitool._is_option_supported('timing'):
        args.append('-R')
        args.append(str(num_tries))

        args.append('-N')
        args.append(str(CONF.ipmi.min_command_interval))

    end_time = (time.time() + CONF.ipmi.retry_timeout)

    while True:
        num_tries = num_tries - 1
        # NOTE(deva): ensure that no communications are sent to a BMC more
        #             often than once every min_command_interval seconds.
        time_till_next_poll = CONF.ipmi.min_command_interval - (
            time.time() - LAST_CMD_TIME.get(driver_info['address'], 0))
        if time_till_next_poll > 0:
            time.sleep(time_till_next_poll)
        # Resetting the list that will be utilized so the password arguments
        # from any previous execution are preserved.
        cmd_args = args[:]
        # 'ipmitool' command will prompt password if there is no '-f'
        # option, we set it to '\0' to write a password file to support
        # empty password
        with ipmitool._make_password_file(
                    driver_info['password'] or '\0'
                ) as pw_file:
            cmd_args.append('-f')
            cmd_args.append(pw_file)
            cmd_args = cmd_args + list(command)  # Append list, don't split
            try:
                out, err = utils.execute(*cmd_args)
                return out, err
            except processutils.ProcessExecutionError as e:
                with excutils.save_and_reraise_exception() as ctxt:
                    err_list = [x for x in ipmitool.IPMITOOL_RETRYABLE_FAILURES
                                if x in six.text_type(e)]
                    if ((time.time() > end_time) or
                        (num_tries == 0) or
                            not err_list):
                        LOG.error(_LE('IPMI Error while attempting '
                                      '"%(cmd)s" for node %(node)s. '
                                      'Error: %(error)s'),
                                  {
                                      'node': driver_info['uuid'],
                                      'cmd': e.cmd,
                                      'error': e
                                  })
                    else:
                        ctxt.reraise = False
                        LOG.warning(_LW('IPMI Error encountered, retrying '
                                        '"%(cmd)s" for node %(node)s. '
                                        'Error: %(error)s'),
                                    {
                                        'node': driver_info['uuid'],
                                        'cmd': e.cmd,
                                        'error': e
                                    })
            finally:
                LAST_CMD_TIME[driver_info['address']] = time.time()


def _get_node_architecture(node):
    """Queries the node for architecture type

    :param node: the Node of interest.
    :returns: SPARC or X86 depending on architecture discovered
    :raises: IPMIFailure if ipmitool command fails
    """
    LOG.debug("SolarisDeploy._get_node_architecture")
    cpu_arch = node.properties.get('cpu_arch', None)
    if cpu_arch is None:
        LOG.info(_LI("Inspection not performed, retrieving architecture via "
                     "IPMI for node: %s"), node.uuid)
        ipmi_cmd_args = ['sunoem', 'getval', '/System/Processors/architecture']
        driver_info = _parse_driver_info(node)
        try:
            cpu_arch, _err = _exec_ipmitool(driver_info, ipmi_cmd_args)
            propdict = {'cpu_arch': cpu_arch.split(":")[1].strip()}
            node_properties = node.properties
            node_properties.update(propdict)
            node.properties = node_properties
            node.save()

        except Exception as err:
            LOG.error(_LE("Failed to get node architecture from IPMI : %s" %
                      (err)))
            raise exception.IPMIFailure(cmd=err)

        LOG.debug("SolarisDeploy._get_node_architecture: cpu_arch: '%s'"
                  % (cpu_arch))

    if 'SPARC' in cpu_arch:
        return 'SPARC'
    elif 'x86' in cpu_arch:
        return 'x86'
    else:
        raise SolarisIPMIError(msg="Unknown node architecture: %s"
                               % (cpu_arch))


def _check_deploy_state(task, node_uuid, deploy_thread):
    """ Check deployment state of a running install

    Check the deployment status for this node ideally this will be
    achieved via communicating with the AI Server and querying the
    telemetry data returned by the AI Client install to the AI Server.

    However until that is integrated we need to maintain a connection
    with the Serial Console of the node being installed and parse the
    output to the console made during an install.

    :param task: a TaskManager instance.
    :param deploy_thread: Threaded class monitor deployment status
    :returns: Nothing, raises loopingcall.LoopingCallDone() once
        node deployment status is determined as done or failed.
    """
    LOG.debug("_check_deploy_state()")
    LOG.debug("_check_deploy_state() deploy_thread_state: %s" %
              (deploy_thread.state))

    try:
        # Get current DB copy of node
        cur_node = objects.Node.get_by_uuid(task.context, node_uuid)
    except exception.NodeNotFound:
        LOG.info(_LI("During check_deploy_state, node %(node)s was not "
                     "found and presumed deleted by another process.") %
                 {'node': node_uuid})
        # Thread should have stopped already, but let's make sure.
        deploy_thread.stop()
        if deploy_thread.state in [states.DEPLOYING, states.DEPLOYWAIT]:
            # Update node with done/fail state
            if task.node:
                task.node.provision_state = states.DEPLOYFAIL
                task.node.last_error = "Failed to find node whilst " + \
                                       "transitioning to '%s' state." % \
                                       (task.node.target_provision_state)
                task.node.target_provision_state = states.NOSTATE
                task.node.save()
        raise loopingcall.LoopingCallDone()
    except Exception as err:
        LOG.info(_LI("During check_deploy_state, node %(node)s could "
                     "not be retrieved: %(err)s") %
                 {'node': node_uuid, 'err': err})
        # Thread should have stopped already, but lets make sure.
        deploy_thread.stop()
        if deploy_thread.state in [states.DEPLOYING, states.DEPLOYWAIT]:
            # Update node with done/fail state
            if task.node:
                task.node.last_error = "Failed to find node whilst " + \
                                       "transitioning to '%s' state." % \
                                       (task.node.target_provision_state)
                task.node.provision_state = states.DEPLOYFAIL
                task.node.target_provision_state = states.NOSTATE
                task.node.save()
        raise loopingcall.LoopingCallDone()

    LOG.debug("_check_deploy_state().cur_node.target_provision_state: %s" %
              (cur_node.target_provision_state))
    LOG.debug("_check_deploy_state().cur_node.provision_state: %s" %
              (cur_node.provision_state))

    if deploy_thread.state not in [states.DEPLOYING, states.DEPLOYWAIT]:
        LOG.debug("_check_deploy_state().done: %s" % (deploy_thread.state))
        # Node has completed deployment, success or failure

        # Thread should have stopped already, but lets make sure.
        deploy_thread.stop()

        # Update node with done/fail state
        if deploy_thread.state == states.DEPLOYDONE:
            cur_node.provision_state = states.ACTIVE
        elif deploy_thread.state == states.DEPLOYFAIL:
            if deploy_thread.error is not None:
                cur_node.last_error = deploy_thread.error
            else:
                cur_node.last_error = "Install failed; check install.log " + \
                                      "for more details."
            cur_node.provision_state = deploy_thread.state
        else:
            cur_node.provision_state = deploy_thread.state
        cur_node.target_provision_state = states.NOSTATE
        cur_node.save()

        # Raise LoopincCallDone to terminate deployment checking.
        raise loopingcall.LoopingCallDone()

    elif deploy_thread.state == states.DEPLOYING and \
            cur_node.provision_state != states.DEPLOYING:
        # Actual node deployment has initiated
        LOG.debug("_check_deploy_state().deploying: %s" %
                  (deploy_thread.state))
        cur_node.provision_state = states.DEPLOYING
        cur_node.save()

    elif cur_node.target_provision_state == states.AVAILABLE or \
            cur_node.target_provision_state == states.NOSTATE:
        # Node was most likely deleted so end deployment completion checking
        LOG.debug("_check_deploy_state().deleted: %s" %
                  (cur_node.target_provision_state))
        deploy_thread.stop()
        raise loopingcall.LoopingCallDone()

    elif cur_node.provision_state == states.DEPLOYFAIL:
        # Node deployment has for some reason failed already, exit thread
        LOG.debug("_check_deploy_state().deploy_failed: %s" %
                  (cur_node.provision_state))
        deploy_thread.stop()
        raise loopingcall.LoopingCallDone()


def _url_exists(url):
    """Validate specific exists

    :param url: HTTP url
    :returns: boolean, True of exists, otherwise False
    """
    LOG.debug("_url_exists: url: %s" % (url.strip()))
    try:
        _open_url = urllib2.urlopen(urllib2.Request(url))
        return True
    except Exception as err:
        LOG.debug(_("URL %s not reachable: %s") % (url, err))
        return False


def _image_refcount_acquire_lock(image_path):
    """Acquire a lock on reference count image file

    :param image_path: Path to image file
    :returns: Acquired LockFile lock
    """
    LOG.debug("_image_refcount_acquire_lock: image_path: %s" % (image_path))
    ref_filename = image_path + ".ref"
    lock = LockFile(ref_filename)
    while not lock.i_am_locking():
        try:
            if os.path.exists(image_path):
                image_size_1 = os.path.getsize(image_path)
            else:
                image_size_1 = 0
            lock.acquire(
                timeout=int(CONF.solaris_ipmi.imagecache_lock_timeout))
        except LockTimeout:
            # Check if image_path size has changed, due to still downloading
            if os.path.exists(image_path):
                image_size_2 = os.path.getsize(image_path)
            else:
                image_size_2 = 0

            if image_size_1 != image_size_2:
                LOG.debug("_image_refcount_acquire_lock: Image downloading...")
                continue
            else:
                # Assume lock is an old one, force it's removal
                LOG.debug("_image_refcount_acquire_lock: Breaking stale lock.")
                lock.break_lock()
                lock.acquire()

    return lock


def _image_refcount_adjust(image_path, count, release=True):
    """Adjust cached image file reference counter

    :param image_path: Path to image file
    :param count: Integer count value to adjust reference by
    :param release: Release the acquired lock or return it.
    :returns: Acquired lock
    """
    LOG.debug("_image_refcount_adjust: image_path: %s, "
              "count: %s" % (image_path, str(count)))

    if count == 0:
        # Adjusting by zero makes no sense just return
        err_msg = _LE("Zero reference count adjustment attempted "
                      "on file: %s") % (image_path)
        LOG.error(err_msg)
        raise SolarisIPMIError(msg=err_msg)

    ref_filename = image_path + ".ref"

    if not os.path.exists(ref_filename):
        if count < 0:
            # Cannot decrement reference on non-existent file
            err_msg = _LE("Negative reference count adjustment attempted on "
                          "non-existent file: %s") % (image_path)
            LOG.error(err_msg)
            raise SolarisIPMIError(msg=err_msg)

        # Create reference count file
        with open(ref_filename, "w") as fp:
            fp.write("0")

    # Acquire lock on refcount file
    lock = _image_refcount_acquire_lock(image_path)
    if lock is None:
        err_msg = _LE("Failed to acquire lock on image: %s") % (image_path)
        LOG.error(err_msg)
        raise SolarisIPMIError(msg=err_msg)

    with open(ref_filename, "r+") as fp:
        ref_count = fp.readline()
        if len(ref_count) == 0:
            ref_count = 1
        ref_count = str(int(ref_count) + count)

        # Check if reference count is zero if so remove
        # refcount file and image file
        if int(ref_count) <= 0:
            lock.release()
            try:
                os.remove(ref_filename)
            except OSError as err:
                if err.errno != errno.ENOENT:
                    raise
            try:
                os.remove(image_path)
            except OSError as err:
                if err.errno != errno.ENOENT:
                    raise

        else:
            fp.seek(0)
            fp.write(ref_count)
            if release:
                lock.release()
    return lock


def _fetch_uri(task, uri):
    """Retrieve the specified URI to local temporary file

    Removal of locally fetched file is the responsibility of the
    caller.

    :param task: a TaskManager instance
    :param uri: URI of file to fetch.
    """
    LOG.debug("SolarisDeploy._fetch_uri:uri: '%s'" % (uri))
    url = urlparse(uri)

    try:
        if url.scheme == "glance":
            temp_uri = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                    url.netloc)

            # Check of image already in cache, retrieve if not
            if not os.path.isfile(temp_uri):
                try:
                    # Increment reference, creates refcount file and returns
                    # the acquired lock.
                    lock = _image_refcount_adjust(temp_uri, 1, release=False)

                    # Fetch URI from Glance into local file.
                    images.fetch(task.context, url.netloc, temp_uri)

                    # Release acquired lock now that file is retrieved
                    lock.release()

                except Exception as err:
                    LOG.error(_LE("Unable to fetch Glance image: id %s: %s")
                              % (url.netloc, err))
                    raise
            else:
                # Increase reference count for this image
                _image_refcount_adjust(temp_uri, 1)

        else:   # http/file scheme handled directly by curl
            if PLATFORM == "SunOS":
                _fd, temp_uri = tempfile.mkstemp(
                    dir=CONF.solaris_ipmi.imagecache_dirname)
                cmd = ["/usr/bin/curl", "-sS", "-o", temp_uri, uri]
                pc = Popen(cmd, stdout=PIPE, stderr=PIPE)
                _stdout, err = pc.communicate()
                if pc.returncode != 0:
                    err_msg = _("Failed to retrieve image: %s") % err
                    raise SolarisIPMIError(msg=err_msg)
            else:  # Linux compat
                temp_uri = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                        url.path.replace("/", ""))
                if not os.path.isfile(temp_uri):
                    try:
                        # Increment reference, creates refcount file and
                        # returns the acquired lock.
                        lock = _image_refcount_adjust(temp_uri, 1,
                                                      release=False)

                        # Actually fetch the image
                        cmd = ["/usr/bin/curl", "-sS", "-o", temp_uri, uri]
                        pc = Popen(cmd, stdout=PIPE, stderr=PIPE)
                        _stdout, err = pc.communicate()
                        if pc.returncode != 0:
                            err_msg = _("Failed to retrieve image: %s") % err
                            _image_refcount_adjust(temp_uri, -1)
                            raise SolarisIPMIError(msg=err_msg)

                        # Release acquired lock now that file is retrieved
                        lock.release()

                    except Exception as err:
                        LOG.error(_LE("Unable to fetch image: id %s: %s")
                                  % (url.netloc, err))
                        raise
                else:
                    # Increase reference count for this image
                    _image_refcount_adjust(temp_uri, 1)
    except Exception as err:
        # Only remove the temporary file if exception occurs
        # as noted above Caller is responsible for its removal
        LOG.error(_LE("Unable to fetch image: uri %s: %s") % (uri, err))
        if url.scheme == "glance":
            _image_refcount_adjust(temp_uri, -1)
        else:
            try:
                os.remove(temp_uri)
            except OSError as err:
                if err.errno != errno.ENOENT:
                    raise
        raise

    return temp_uri


def _get_archive_iso_and_uuid(mount_dir, extract_iso=False):
    """Get ISO name and UUID

    Retrieved from mounted archive if on Solaris

    On non-Solaris systems we cannot mount a UAR so we need to parse the
    contents of the unified archive and extract ISO and UUID from
    cached UAR. In this scenario the caller is responsible for removing
    the extracted file.

    :param mount_dir: Location of locally mounted UAR or locally cached UAR
    :param extract_iso: Whether to extract ISO file to temp file
    :returns: Extracted ISO location and UUID
    """
    LOG.debug("SolarisDeploy._get_archive_iso_and_uuid:mount_dir: '%s'" %
              (mount_dir))
    uuid = None
    iso = None

    if PLATFORM == "SunOS":
        ovf_dir = os.path.join(mount_dir, "OVF")

        for uar_file in os.listdir(ovf_dir):
            if uar_file.endswith('.ovf'):
                uuid = uar_file.split('.ovf')[0]
            elif uar_file.endswith('.iso'):
                iso = os.path.join(ovf_dir, uar_file)
    else:
        tf = tarfile.open(name=mount_dir)

        for ti in tf.getmembers():
            if ti.path.endswith('.ovf'):
                uuid = ti.path.split('.ovf')[0]
            elif ti.path.endswith('.iso') and extract_iso:
                try:
                    temp_tar_dir = tempfile.mkdtemp(
                        dir=CONF.solaris_ipmi.imagecache_dirname)
                    tf.extractall(path=temp_tar_dir, members=[ti])
                    iso = os.path.join(temp_tar_dir, ti.path)
                except:
                    # Remove temp_tar_dir and contents
                    shutil.rmtree(temp_tar_dir)
                    raise

    return iso, uuid


def _mount_archive(task, archive_uri):
    """Mount a unified archive

    :param archive_uri: URI of unified archive to mount
    :returns: Path to mounted unified archive
    """
    LOG.debug("SolarisDeploy._mount_archive:archive_uri: '%s'" %
              (archive_uri))

    if urlparse(archive_uri).scheme == "glance":
        # TODO(mattk):
        # Ideally mounting the http ISO directly is preferred.
        # However mount(1M), does not support auth_token
        # thus we must fetch the image locally and then mount the
        # local image.
        # Tried putting a proxy in place to intercept the mount(1M)
        # http request and adding an auth_token as it proceeds.
        # However mount(1M) launches a new SMF instance for each HTTP
        # mount request, and each SMF instance has a minimal environment
        # set, which does not include http_proxy, thus the custom local
        # proxy never gets invoked.
        # Would love to have a new mount(1M) option to accept either
        # a proxy e.g. -o proxy=<proxy> or to accept setting of http headers
        # e.g. -o http_header="X-Auth-Token: askdalksjdlakjsd"

        # Retrieve UAR to local temp file for mounting
        temp_uar = _fetch_uri(task, archive_uri)
        archive_mount = temp_uar
    else:
        # Can mount archive directly
        temp_uar = None
        archive_mount = archive_uri

    mount_dir = tempfile.mkdtemp(dir=CONF.solaris_ipmi.imagecache_dirname)

    cmd = ["/usr/sbin/mount", "-F", "uvfs", "-o",
           "archive=%s" % (archive_mount), "/usr/lib/fs/uafs/uafs", mount_dir]
    LOG.debug("SolarisDeploy._mount_archive:cmd: '%s'" % (cmd))
    pc = Popen(cmd, stdout=PIPE, stderr=PIPE)
    _stdout, err = pc.communicate()
    if pc.returncode != 0:
        err_msg = _("Failed to mount UAR %s: %s") % (archive_uri, err)
        shutil.rmtree(mount_dir)
        raise SolarisIPMIError(msg=err_msg)

    return mount_dir, temp_uar


def _umount_archive(mount_dir):
    """ Unmount archive and remove mount point directory

    :param mount_dir: Path to mounted archive
    :param temp_uar: Path to glance local uar to remove
    """
    LOG.debug("SolarisDeploy._umount_archive:mount_dir: '%s'" % (mount_dir))

    cmd = ["/usr/sbin/umount", mount_dir]
    pc = Popen(cmd, stdout=PIPE, stderr=PIPE)
    _stdout, err = pc.communicate()
    if pc.returncode != 0:
        err_msg = _("Failed to unmount UAR %s: %s") % (mount_dir, err)
        raise SolarisIPMIError(msg=err_msg)

    shutil.rmtree(mount_dir)


def _get_archive_uuid(task):
    """Get the UUID of an archive

    :param task: a TaskManager instance
    :returns: UUID string for an archive otherwise raise exception
    """
    LOG.debug("SolarisDeploy._get_archive_uuid")
    uuid = None
    archive_uri = task.node.driver_info['archive_uri']

    if PLATFORM == "SunOS":
        mount_dir, temp_uar = _mount_archive(task, archive_uri)
        try:
            _iso, uuid = _get_archive_iso_and_uuid(mount_dir)
        except:
            _umount_archive(mount_dir)
            raise
        _umount_archive(mount_dir)
    else:
        temp_uar = _fetch_uri(task, archive_uri)
        try:
            _iso, uuid = _get_archive_iso_and_uuid(temp_uar)
        except:
            _image_refcount_adjust(temp_uar, -1)
            raise

    if uuid is None:
        err_msg = _("Failed to extract UUID from UAR: %s") % archive_uri
        if PLATFORM != "SunOS":
            _image_refcount_adjust(temp_uar, -1)
        raise SolarisIPMIError(msg=err_msg)

    LOG.debug("SolarisDeploy._get_archive_uuid: uuid: %s" % (uuid))
    return uuid


def _validate_archive_uri(task):
    """Validate archive_uri for reachable, format, etc

    :param task: a TaskManager instance.
    :raises: InvalidParameterValie if invalid archive_uri
    """
    LOG.debug("SolarisDeploy._validate_archive_uri")
    archive_uri = task.node.driver_info['archive_uri']

    url = urlparse(archive_uri)

    if url.scheme not in VALID_ARCHIVE_SCHEMES:
        raise exception.InvalidParameterValue(_(
            "Unsupported archive scheme (%s) referenced in archive_uri (%s).")
            % (url.scheme, archive_uri))

    if not url.netloc and not url.path:
        raise exception.InvalidParameterValue(_(
            "Missing archive name in archive_uri (%s).") % (archive_uri))

    if url.scheme == "glance":
        # Glance schema only supported if using keystone authorization
        # otherwise ironic being used standalone
        if CONF.auth_strategy != "keystone":
            raise exception.InvalidParameterValue(_(
                "Glance scheme only supported when using Keystone (%s).")
                % (archive_uri))

        # Format : glance://<glance UUID>
        # When parsed by urlparse, Glance image uuid appears as netloc param
        if not url.netloc:
            raise exception.InvalidParameterValue(_(
                "Missing Glance image UUID archive_uri (%s).")
                % (archive_uri))

        # Validate glance image exists by attempting to get download size
        try:
            size = images.download_size(task.context, url.netloc)
            LOG.debug("Image %s size: %s" % (url.netloc, str(size)))
            if not size:
                raise exception.InvalidParameterValue(_(
                    "Glance image not found: %s") % (url.netloc))

        except Exception as err:
            raise exception.InvalidParameterValue(_(
                "Failed to validate Glance image '%s': %s") %
                (url.netloc, err))

    elif url.scheme in ["http", "https"]:
        # Presuming client authentication using HTTPS is not being used.
        # Just a secure connection.
        # TODO(mattk): Do I need to support client side HTTPS authentication
        if not _url_exists(archive_uri):
            raise exception.InvalidParameterValue(_(
                "archive_uri does not exist (%s).") % (archive_uri))
    elif url.scheme == "file":
        file_path = os.path.join(os.sep,
                                 url.netloc.strip(os.sep),
                                 url.path.strip(os.sep))
        if not os.path.isfile(file_path):
            raise exception.InvalidParameterValue(_(
                "archive_uri does not exist (%s).") % (archive_uri))


def _format_archive_uri(task, archive_uri):
    """Format archive URL to be passed as boot argument to AI client

    Transformation of archive_uri is only required if URI scheme is glance.

    :param task: a TaskManager instance.
    :param archive_uri: URI path to unified archive
    :returns: Formatted archive URI, and auth_token if needed
    """
    LOG.debug("SolarisDeploy._format_archive_uri: archive_uri: %s" %
              (archive_uri))
    if archive_uri:
        url = urlparse(archive_uri)

        if url.scheme == "glance":
            # Transform uri from glance://<UUID> to
            # direct glance URL glance://<GLANCE_REST_API>/<UUID>
            new_uri = "http://%s:%s/v2/images/%s/file" % \
                (CONF.glance.glance_host, CONF.glance.glance_port,
                 url.netloc)
            auth_token = task.context.auth_token
        else:
            new_uri = archive_uri
            auth_token = None
    else:
        new_uri = None
        auth_token = None

    return new_uri, auth_token


def _validate_ai_manifest(task):
    """Validate ai_manifest for format, etc

    driver_info/ai_manifest is used to specify a path to a single
    AI manifest to be used instead of the default derived script.
    e.g. http://path-to-manifest

    :param task: a TaskManager instance.
    :raises: InvalidParameterValue if invalid ai_manifest
    """
    LOG.debug("SolarisDeploy._validate_ai_manifest")
    ai_manifest = task.node.driver_info['ai_manifest']
    _validate_uri(task, ai_manifest)


def _validate_profiles(task, profiles):
    """Validate profiles for format, etc

    Configuration profiles are specified as a plus(+) delimited list of paths
    e.g. http://path-to-profile+http://path-to-another-profile

    :param task: a TaskManager instance.
    :param profiles: Plus(+) delimited list of configuration profile
    :raises: InvalidParameterValue if invalid configuration profile
    """
    LOG.debug("SolarisDeploy._validate_profiles: %s" % (profiles))

    # Split profiles into list of paths@environment elements
    prof_list = [prof.strip() for prof in profiles.split('+') if prof.strip()]

    for profile in prof_list:
        _validate_uri(task, profile)


def _validate_uri(task, uri):
    """Validate URI for AI Manifest or SC Profile

    :param task: a TaskManager instance.
    :param uri: URI to AI Manifest or SC profile
    :raises: InvalidParameterValue if invalid manifest/profile URI
    """
    LOG.debug("SolarisDeploy._validate_uri: URI: %s" % (uri))
    url = urlparse(uri)

    if url.scheme not in VALID_URI_SCHEMES:
        raise exception.InvalidParameterValue(_(
            "Unsupported uri scheme (%s) referenced"
            " in URI (%s).") % (url.scheme, uri))

    if not url.netloc and not url.path:
        raise exception.InvalidParameterValue(_(
            "Missing URI name (%s).") % (uri))

    if url.scheme in ["http", "https"]:
        # Presuming client authentication using HTTPS is not being used.
        # Just a secure connection.
        # TODO(mattk): Do I need to support client side HTTPS authentication
        if not _url_exists(uri):
            raise exception.InvalidParameterValue(_(
                "URI does not exist (%s).") % (uri))
        else:
            LOG.debug("SolarisDeploy._validate_uri: %s exists." %
                      (uri))
    elif url.scheme == "file":
        file_path = os.path.join(os.sep,
                                 url.netloc.strip(os.sep),
                                 url.path.strip(os.sep))
        if not os.path.isfile(file_path):
            raise exception.InvalidParameterValue(_(
                "URI does not exist (%s).") % (uri))
        else:
            LOG.debug("SolarisDeploy._validate_uri: %s exists." %
                      (url.scheme))
    elif url.scheme == "glance":
        # Glance schema only supported if using keystone authorization
        # otherwise ironic being used standalone
        if CONF.auth_strategy != "keystone":
            raise exception.InvalidParameterValue(_(
                "Glance scheme only supported when using Keystone (%s).")
                % (uri))

        # Format : glance://<glance UUID>
        # When parsed by urlparse, Glance image uuid appears as netloc param
        if not url.netloc:
            raise exception.InvalidParameterValue(_(
                "Missing Glance image UUID for URI (%s).")
                % (uri))

        # Validate glance uri exists by attempting to get download size
        try:
            size = images.download_size(task.context, url.netloc)
            LOG.debug("Image %s size: %s" % (url.netloc, str(size)))
            if not size:
                raise exception.InvalidParameterValue(_(
                    "Glance image not found: %s") % (url.netloc))
            else:
                LOG.debug("SolarisDeploy._validate_uri: %s exists." %
                          (uri))

        except Exception as err:
            raise exception.InvalidParameterValue(_(
                "Failed to validate Glance URI '%s': %s") %
                (url.netloc, err))


def _validate_fmri(task):
    """Validate fmri for format, etc

    driver_info/fmri is a plus(+) delimited list of IPS package
    FMRIs to be installed. e.g. pkg:/pkg1+pkg:/pkg2

    :param task: a TaskManager instance.
    :raises: InvalidParameterValue if invalid fmri
    """
    LOG.debug("SolarisDeploy._validate_fmri")
    fmri = task.node.driver_info['fmri']

    # Split fmri into list of possible packages
    pkg_list = [pkg.strip() for pkg in fmri.split('+') if pkg.strip()]
    for fmri in pkg_list:
        _validate_fmri_format(fmri)


def _validate_fmri_format(fmri):
    """Validate FMRI for format
    FMRI must not contain the publisher and must be of the format:

            pkg:/<package path>

    Note the fmri only contains a single backslash.

    :param fmri: IPS FMRI
    :raises: InvalidParameterValue if invalid FMRI
    """
    LOG.debug("SolarisDeploy._validate_fmri_format: fmri: %s" % (fmri))
    url = urlparse(fmri)

    if url.scheme != "pkg":
        raise exception.InvalidParameterValue(_(
            "Unsupported IPS scheme (%s) referenced in fmri (%s).")
            % (url.scheme, fmri))

    if url.netloc:
        raise exception.InvalidParameterValue(_(
            "Cannot specify publisher name in fmri (%s).") % (fmri))

    if not url.path:
        raise exception.InvalidParameterValue(_(
            "Missing IPS package name in fmri (%s).") % (fmri))
    elif PLATFORM == "SunOS":
        # Validate package name
        try:
            # PkgFmri object does not like the @latest special case so
            # strip it off if it's there.
            _pkgfmri = PkgFmri(fmri.strip('@latest'))
        except IllegalFmri as err:
            raise exception.InvalidParameterValue(err)


def _validate_publishers(task):
    """Validate custom publisher name/origins for format

    publishers property is a plus(+) delimited list of IPS publishers
    to be installed from, in the format name@origin. e.g.
        solaris@http://pkg.oracle.com/solaris+extra@http://int.co.com/extras

    :param task: a TaskManager instance.
    :raises: InvalidParameterValue if invalid publisher
    """
    LOG.debug("SolarisDeploy._validate_publishers")
    pubs = task.node.driver_info['publishers']

    # Split publishers into list of name@origin publishers
    pub_list = [pub.strip() for pub in pubs.split('+') if pub.strip()]
    for pub in pub_list:
        try:
            # Split into name origin
            name, origin = pub.split('@', 1)
        except ValueError:
            raise exception.InvalidParameterValue(_(
                "Malformed IPS publisher, must be of format "
                "name@origin (%s).") % (pub))

        if not name or not origin:
            raise exception.InvalidParameterValue(_(
                "Malformed IPS publisher, must be of format "
                "name@origin (%s).") % (pub))

        if PLATFORM == "SunOS":
            if not valid_pub_prefix(name):
                raise exception.InvalidParameterValue(_(
                    "Malformed IPS publisher name (%s).") % (name))

            if not valid_pub_url(origin):
                raise exception.InvalidParameterValue(_(
                    "Malformed IPS publisher origin (%s).") % (origin))


def _fetch_and_create(task, obj_type, obj_name, obj_uri, aiservice, mac,
                      env=None):
    """Fetch manifest/profile and create on AI Server

    :param task: a TaskManager instance.
    :param obj_type: Type of AI object to create "manifest" or "profile"
    :param obj_name: manifest/profile name
    :param obj_uri: URI to manifest/profile to use
    :param aiservice: AI Service to create manifest/profile for
    :param mac: MAC address criteria to use
    :param env: Environment to apply profile to
    :raises: AICreateProfileFail or AICreateManifestFail
    """
    # Fetch URI to local file
    url = urlparse(obj_uri)
    temp_file = _fetch_uri(task, obj_uri)

    try:
        # scp temp file to AI Server
        remote_file = os.path.join("/tmp", obj_name) + ".xml"
        aiservice.copy_remote_file(temp_file, remote_file)
    except Exception as err:
        LOG.error(_LE("Fetch and create failed for %s: name: %s: %s") %
                  (obj_type, obj_uri, err))
        if url.scheme == "glance":
            _image_refcount_adjust(temp_file, -1)
        else:
            os.remove(temp_file)
        raise

    try:
        if obj_type == "manifest":
            # Create AI Profile
            aiservice.create_manifest(obj_name, remote_file, mac)
        elif obj_type == "profile":
            # Create AI Profile
            aiservice.create_profile(obj_name, remote_file, mac, env)

    except (AICreateManifestFail, AICreateProfileFail) as _err:
        aiservice.delete_remote_file(remote_file)
        if url.scheme == "glance":
            _image_refcount_adjust(temp_file, -1)
        else:
            os.remove(temp_file)
        raise

    # Remove local and remote temporary profiles
    aiservice.delete_remote_file(remote_file)
    if url.scheme == "glance":
        _image_refcount_adjust(temp_file, -1)
    else:
        os.remove(temp_file)


class DeployStateChecker(Thread):
    """Thread class to check for deployment completion"""

    def __init__(self, task):
        """Init method for thread class"""
        LOG.debug("DeployStateChecker.__init__()")
        Thread.__init__(self)

        self.task = task
        self.node = task.node
        self._state = states.DEPLOYWAIT
        self._error = None
        self.ssh_connection = None
        self.running = True

    @property
    def state(self):
        """Deployment state property"""
        return self._state

    @property
    def error(self):
        """Deployment error property"""
        return self._error

    def run(self):
        """Start the thread """
        LOG.debug("DeployStateChecker.run(): Connecting...")
        # Occasionally SSH connection fails, make three attempts
        # before returning failure.
        connection_attempt = 0
        while (connection_attempt < 3):
            try:
                connection_attempt += 1
                client = utils.ssh_connect(self._get_ssh_dict())
                break
            except SSHException as err:
                if connection_attempt < 3:
                    continue
                else:
                    self._state = states.DEPLOYFAIL
                    self._error = str(err)
                    self.stop()
                    return
        else:
            self._state = states.DEPLOYFAIL
            self._error = "Failed to establish SSH Connection with node."
            self.stop()
            return

        channel = client.invoke_shell()
        channel.settimeout(0.0)
        channel.set_combine_stderr(True)

        # Continuously read stdout from console and parse
        # specifically for success/failure output
        while self.running:
            with tempfile.TemporaryFile(dir='/var/lib/ironic') as tf:
                while True:
                    rchans, _wchans, _echans = select.select([channel], [], [])
                    if channel in rchans:
                        try:
                            console_data = ""
                            while channel.recv_ready():
                                console_data += channel.recv(1024)

                            if len(console_data) == 0:
                                tf.write("\n*** EOF\n")
                                # Confirm string to search for on success
                                if self._string_in_file(tf, AI_SUCCESS_STRING):
                                    self._state = states.DEPLOYDONE
                                else:
                                    # Didn't succeed so default to failure
                                    self._state = states.DEPLOYFAIL
                                self.stop()
                                break
                            tf.write(console_data)
                            tf.flush()

                            # Read input buffer for prompt
                            if re.search("->", console_data):
                                # Send console start command
                                channel.send("start -script SP/Console\n")

                            # Cater for Yes/No prompts always sending Yes
                            elif re.search("y/n", console_data):
                                channel.send("y\n")

                            # Confirm string to search for on success
                            elif self._string_in_file(tf, AI_SUCCESS_STRING):
                                LOG.debug("DeployStateChecker.run(): Done")
                                self._state = states.DEPLOYDONE
                                self.stop()
                                break

                            # Confirm string to search for on failure
                            elif self._string_in_file(tf, AI_FAILURE_STRING):
                                LOG.debug("DeployStateChecker.run(): FAIL")
                                self._state = states.DEPLOYFAIL
                                self.stop()
                                break

                            elif self._string_in_file(tf, AI_DEPLOY_STRING):
                                LOG.debug(
                                    "DeployStateChecker.run(): DEPLOYING")
                                self._state = states.DEPLOYING
                        except socket.timeout:
                            pass

    def stop(self):
        """Stop the thread"""
        LOG.debug("DeployStateChecker.stop()")
        self.running = False

    def _string_in_file(self, fp, string):
        """Read all data from file checking for string presence

        :param fp: Open file pointer to read
        :param string: Specific string to check for
        :returns: boolean True of string present in file, False if not
        """
        found_string = False

        # Position read at start of file
        fp.seek(0)
        for line in fp:
            if re.search(string, line):
                found_string = True
                break

        # Return current read point to end of file for subsequent writes
        fp.seek(0, 2)
        return found_string

    def _get_ssh_dict(self):
        """Generate SSH Dictionary for SSH Connection via paramiko

        :returns: dictionary for paramiko connection
        """
        LOG.debug("DeployStateChecker._get_ssh_dict()")

        driver_info = _parse_driver_info(self.node)

        ssh_dict = {
            'host': driver_info.get('address'),
            'username': driver_info.get('username'),
            'port': driver_info.get('port', 22)
            }

        if ssh_dict.get('port') is not None:
            ssh_dict['port'] = int(ssh_dict.get('port'))
        else:
            del ssh_dict['port']

        if driver_info['password']:
            ssh_dict['password'] = driver_info['password']

        LOG.debug("DeployStateChecker._get_ssh_dict():ssh_dict: %s" %
                  (ssh_dict))
        return ssh_dict


class SolarisDeploy(base.DeployInterface):
    """AI Deploy Interface """

    def get_properties(self):
        """Return Solaris driver properties"""
        return COMMON_PROPERTIES

    def validate(self, task):
        """Validate the driver-specific Node deployment info.

        :param task: a task from TaskManager.
        :raises: InvalidParameterValue.
        :raises: MissingParameterValue.
        """
        LOG.debug("SolarisDeploy.validate()")
        LOG.debug(task.context.auth_token)

        # Validate IPMI credentials by getting node architecture
        try:
            _cpu_arch = _get_node_architecture(task.node)
        except Exception as err:
            raise exception.InvalidParameterValue(_(err))

        if not driver_utils.get_node_mac_addresses(task):
            raise exception.InvalidParameterValue(
                _("Node %s does not have any port associated with it.") %
                (task.node.uuid))

        # Ensure server configured
        if not CONF.ai.server or CONF.ai.server == "None":
            raise exception.MissingParameterValue(
                _("AI Server not specified in configuration file."))

        # Ensure username configured
        if not CONF.ai.username or CONF.ai.username == "None":
            raise exception.MissingParameterValue(
                _("AI Server user not specified in configuration file."))

        # One of ssh_key_file / ssh_key_contents / password must be configured
        if ((not CONF.ai.password or CONF.ai.password == "None") and
            (not CONF.ai.ssh_key_file or CONF.ai.ssh_key_file == "None") and
            (not CONF.ai.ssh_key_contents or
                CONF.ai.ssh_key_contents == "None")):
            raise exception.MissingParameterValue(
                _("AI Server authentication not specified. One of password, "
                  "ssh_key_file and ssh_key_contents must be present in "
                  "configuration file."))

        # archive_uri, publishers or fmri are ignored if a ai_manifest is
        # defined. They should be contained within the custom manifest itself
        if (task.node.driver_info.get('ai_manifest') and
            (task.node.driver_info.get('archive_uri') or
            task.node.driver_info.get('publishers') or
                task.node.driver_info.get('fmri'))):
            raise exception.InvalidParameterValue(
                _("Custom Archive, Publishers or FMRI cannot be specified "
                  "when specifying a custom AI Manifest. They should be "
                  "contained within this custom AI Manifest."))

        # Ensure ai_service is valid if specified in driver
        if task.node.driver_info.get('ai_service'):
            aiservice = AIService(task,
                                  task.node.driver_info.get('ai_service'))
            if not aiservice.exists:
                raise exception.InvalidParameterValue(
                    _("AI Service %s does not exist.") % (aiservice.name))

        # Ensure node archive_uri is valid if specified
        if task.node.driver_info.get('archive_uri'):
            # Validate archive_uri for reachable, format, etc
            _validate_archive_uri(task)

        # Ensure custom publisher provided if FMRI provided
        if task.node.driver_info.get('fmri') and \
                not task.node.driver_info.get('publishers'):
            raise exception.MissingParameterValue(_(
                "Must specify custom publisher with custom fmri."))

        # Ensure node publishers are valid if specified
        if task.node.driver_info.get('publishers'):
            # Validate publishers for format, etc
            _validate_publishers(task)

        # Ensure node fmri is valid if specified
        if task.node.driver_info.get('fmri'):
            # Validate fmri for format, etc
            _validate_fmri(task)

        # Ensure node sc_profiles is valid if specified
        if task.node.driver_info.get('sc_profiles'):
            # Validate sc_profiles for format, etc
            _validate_profiles(task, task.node.driver_info.get('sc_profiles'))

        # Ensure node install_profiles is valid if specified
        if task.node.driver_info.get('install_profiles'):
            # Validate install_profiles for format, etc
            _validate_profiles(task,
                               task.node.driver_info.get('install_profiles'))

        # Ensure node manifest is valid of specified
        if task.node.driver_info.get('ai_manifest'):
            # Validate ai_manifest for format, etc
            _validate_ai_manifest(task)

        # Try to get the URL of the Ironic API
        try:
            CONF.conductor.api_url or keystone.get_service_url()
        except (exception.KeystoneFailure,
                exception.KeystoneUnauthorized,
                exception.CatalogNotFound):
            raise exception.InvalidParameterValue(_(
                "Couldn't get the URL of the Ironic API service from the "
                "configuration file or Keystone catalog."))

        # Validate driver_info by parsing contents
        _parse_driver_info(task.node)

    @task_manager.require_exclusive_lock
    def deploy(self, task):
        """Perform start deployment a node.

        For AI Deployment of x86 machines, we simply need to set the chassis
        boot device to pxe and reboot the physical node.

        For AI Deployment of SPARC Machines we need to supply a boot script
        indicating to perform a network DHCP boot.

        AI Server settings for this node, e.g. client, manifest, boot args
        etc, will have been configured via prepare() method which is called
        before deploy().

        :param task: a TaskManager instance.
        :returns: deploy state DEPLOYWAIT.
        """
        LOG.debug("SolarisDeploy.deploy()")

        cpu_arch = _get_node_architecture(task.node)

        # Ensure persistence is false so net boot only occurs once
        if cpu_arch == 'x86':
            # Set boot device to PXE network boot
            dev_cmd = 'pxe'
        elif cpu_arch == 'SPARC':
            # Set bootmode script to network DHCP
            dev_cmd = 'wanboot'
        else:
            raise exception.InvalidParameterValue(
                _("Invalid node architecture of '%s'.") % (cpu_arch))

        manager_utils.node_set_boot_device(task, dev_cmd,
                                           persistent=False)
        manager_utils.node_power_action(task, states.REBOOT)

        deploy_thread = DeployStateChecker(task)
        deploy_thread.start()
        timer = loopingcall.FixedIntervalLoopingCall(_check_deploy_state,
                                                     task, task.node.uuid,
                                                     deploy_thread)
        timer.start(interval=int(CONF.ai.deploy_interval))

        return states.DEPLOYWAIT

    @task_manager.require_exclusive_lock
    def tear_down(self, task):
        """Tear down a previous deployment.

        Reset boot device or bootmode script and power off the node.
        All actual clean-up is done in the clean_up()
        method which should be called separately.

        :param task: a TaskManager instance.
        :returns: deploy state DELETED.
        """
        LOG.debug("SolarisDeploy.tear_down()")
        manager_utils.node_set_boot_device(task, 'disk',
                                           persistent=False)
        manager_utils.node_power_action(task, states.POWER_OFF)

        return states.DELETED

    def prepare(self, task):
        """Prepare the deployment environment for this node.

        1. Ensure Node's AI Service is specified and it exists
        2. (Re)Create AI Clients for each port/Mac specified for this Node
        3. (Re)Create AI Manifest for each port/Mac specified for this Node
           with specific criteria of MAC address

        AI Service to use for installation is determined from
        driver_info properties archive_uri or ai_service. archive_uri
        takes precedence over ai_service.

        1. archive_uri specified.
            Extract AI ISO from UAR and create a new AI service if service
            for this ID does not exist.
        2. ai_service specified
            AI Service must exist.
        3. archive_uri & ai_service not specified
            Use default architecture specific service to perform IPS
            install.

        :param task: a TaskManager instance.
        """
        LOG.debug("SolarisDeploy.prepare()")

        ai_manifest = task.node.driver_info.get('ai_manifest', None)
        ai_service = task.node.driver_info.get('ai_service', None)
        cpu_arch = _get_node_architecture(task.node)
        archive_uri = task.node.driver_info.get('archive_uri', None)
        fmri = task.node.driver_info.get('fmri', None)
        install_profiles = task.node.driver_info.get('install_profiles', None)
        publishers = task.node.driver_info.get('publishers', None)
        sc_profiles = task.node.driver_info.get('sc_profiles', None)

        # Ensure cache dir exists
        if not os.path.exists(CONF.solaris_ipmi.imagecache_dirname):
            os.makedirs(CONF.solaris_ipmi.imagecache_dirname)

        # archive_uri, publishers or fmri are ignored if a ai_manifest is
        # defined. They should be contained within the custom manifest itself
        if ((ai_manifest) and (archive_uri or publishers or fmri)):
            raise exception.InvalidParameterValue(
                _("Custom Archive, Publishers or FMRI cannot be specified "
                  "when specifying a custom AI Manifest. They should be "
                  "contained within this custom AI Manifest."))

        # 1. Ensure Node's AI Service exists, if archive_uri then
        #    create a new service of UUID of archive does not already exist
        if archive_uri:
            # Validate archive_uri, format, reachable, etc
            _validate_archive_uri(task)

            # Extract UUID from archive UAR and instantiate AIService
            ai_service = _get_archive_uuid(task)
            aiservice = AIService(task, ai_service)

        elif ai_service:
            # Instantiate AIService object for this node/service
            aiservice = AIService(task, ai_service)
        else:
            # IPS Install, ensure default architecture service exists
            if cpu_arch == "x86":
                ai_service = "default-i386"
            elif cpu_arch == 'SPARC':
                ai_service = "default-sparc"
            else:
                raise exception.InvalidParameterValue(
                    _("Invalid node architecture of '%s'.") % (cpu_arch))

            # Instantiate AIService object for this node/service
            aiservice = AIService(task, ai_service)

        # Check if AI Service exists, raise exception of not
        if not aiservice.exists:
            if archive_uri:
                # Create this service
                aiservice.create_service(archive_uri)
            else:
                raise exception.InvalidParameterValue(
                    _("AI Service %s does not exist.") % (aiservice.name))

        # Ensure custom publisher provided if FMRI provided
        if fmri and not publishers:
            raise exception.InvalidParameterValue(_(
                "Must specify custom publisher with custom fmri."))

        # Ensure node publishers are valid if specified
        if publishers:
            # Validate publishers for format, etc
            _validate_publishers(task)

        # Ensure node fmri is valid if specified
        if fmri:
            # Validate fmri, format, etc
            _validate_fmri(task)

        # Ensure node sc_profiles is of valid format if specified
        if sc_profiles:
            # Validate sc_profiles for format, etc
            _validate_profiles(task, sc_profiles)

        # Ensure node install_profiles is of valid format if specified
        if install_profiles:
            # Validate install_profiles for format, etc
            _validate_profiles(task, install_profiles)

        # Ensure node ai_manifest is valid if specified
        if ai_manifest:
            # Validate ai_manifest for format, etc
            _validate_ai_manifest(task)

        for mac in driver_utils.get_node_mac_addresses(task):
            # 2. Recreate AI Clients for each port/Mac specified for this Node
            # Check if AI Client exists for this service and if so remove it
            if mac.lower() in aiservice.clients:
                # Client exists remove it
                aiservice.delete_client(mac)

            # Recreate new ai client for this mac address
            new_uri, auth_token = _format_archive_uri(task, archive_uri)
            aiservice.create_client(mac, cpu_arch, new_uri, auth_token,
                                    publishers, fmri)

            # 3. (Re)Create AI Manifest for each port/Mac specified for this
            #    Node. Manifest name will be MAC address stripped of colons
            manifest_name = mac.replace(':', '')

            # Check if AI Manifest exists for this service and if so remove it
            if manifest_name in aiservice.manifests:
                # Manifest exists remove it
                aiservice.delete_manifest(manifest_name)

            # (Re)Create new ai Manifest for this mac address
            # If ai_manifest is specified use it as the manifest otherwise
            # use derived manifest script specified by aiservice.
            if ai_manifest is not None:
                # Fetch manifest locally, copy to AI Server so that
                # installadm create-manifest CLI works.
                _fetch_and_create(task, "manifest", manifest_name, ai_manifest,
                                  aiservice, mac)
            else:
                _fetch_and_create(task, "manifest", manifest_name,
                                  aiservice.derived_manifest, aiservice, mac)

            # 4. (Re)Create AI Profiles for each port/MAC specified for this
            #   Node, adding a new profile for each SC Profile specified.
            #   Profile Name will be MAC address prefix and counter suffix.
            #   e.g. AAEEBBCCFF66-1
            profile_prefix = mac.replace(':', '') + "-"

            # Remove all profiles associated with this MAC address and service
            for profile_name in aiservice.profiles:
                # Profile name starts with MAC address, assuming ironic
                # created this profile so remove it.
                if profile_prefix in profile_name:
                    aiservice.delete_profile(profile_name)

            # Process both sc_profiles and install_profiles filtering into
            # unique list of profiles and environments to be applied to.
            if install_profiles is not None:
                ins_list = [prof.strip() for prof in
                            install_profiles.split('+') if prof.strip()]
            else:
                ins_list = []

            prof_dict = dict(((uri, "install") for uri in ins_list))

            if sc_profiles is not None:
                sc_list = [prof.strip() for prof in sc_profiles.split('+')
                           if prof.strip()]
            else:
                sc_list = []

            for profile in sc_list:
                if profile in prof_dict:
                    prof_dict[profile] = "all"
                else:
                    prof_dict[profile] = "system"

            profile_index = 0
            for profile_uri, profile_env in prof_dict.iteritems():
                profile_index += 1
                profile_name = profile_prefix + str(profile_index)

                # Fetch profile locally, copy to AI Server so that
                # installadm create-profile CLI works.
                _fetch_and_create(task, "profile", profile_name, profile_uri,
                                  aiservice, mac, env=profile_env)

        # Ensure local copy of archive_uri is removed if not needed
        if archive_uri:
            url = urlparse(archive_uri)
            if url.scheme == "glance":
                temp_uar = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                        url.netloc)
                _image_refcount_adjust(temp_uar, -1)
            elif PLATFORM != "SunOS":
                temp_uar = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                        url.path.replace("/", ""))
                _image_refcount_adjust(temp_uar, -1)

    def clean_up(self, task):
        """Clean up the deployment environment for this node.

        As node is being torn down we need to clean up specific
        AI Clients and Manifests associated with MAC addresses
        associated with this node.

        1. Delete AI Clients for each port/Mac specified for this Node
        2. Delete AI Manifest for each port/Mac specified for this Node

        :param task: a TaskManager instance.
        """
        LOG.debug("SolarisDeploy.clean_up()")

        ai_service = task.node.driver_info.get('ai_service', None)
        cpu_arch = _get_node_architecture(task.node)
        archive_uri = task.node.driver_info.get('archive_uri', None)

        # Instantiate AIService object for this node/service
        if archive_uri:
            aiservice = AIService(task, _get_archive_uuid(task))
        elif ai_service:
            aiservice = AIService(task, ai_service)
        else:
            if cpu_arch == "x86":
                ai_service = "default-i386"
            elif cpu_arch == 'SPARC':
                ai_service = "default-sparc"
            else:
                raise exception.InvalidParameterValue(
                    _("Invalid node architecture of '%s'.") % (cpu_arch))
            aiservice = AIService(task, ai_service)

        # Check if AI Service exists, log message if already removed
        if not aiservice.exists:
            # There is nothing to clean up as service removed
            LOG.info(_LI("AI Service %s already removed.") % (aiservice.name))
        else:
            for mac in driver_utils.get_node_mac_addresses(task):
                # 1. Delete AI Client for this MAC Address
                if mac.lower() in aiservice.clients:
                    aiservice.delete_client(mac)

                # 2. Delete AI Manifest for this MAC Address
                manifest_name = mac.replace(':', '')
                if manifest_name in aiservice.manifests:
                    aiservice.delete_manifest(manifest_name)

                # 3. Remove AI Profiles for this MAC Address
                profile_prefix = mac.replace(':', '') + "-"

                # Remove all profiles associated with this MAC address
                for profile_name in aiservice.profiles:
                    if profile_prefix in profile_name:
                        aiservice.delete_profile(profile_name)

        # Ensure local copy of archive_uri is removed if not needed
        if archive_uri:
            url = urlparse(archive_uri)
            if url.scheme == "glance":
                temp_uar = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                        url.netloc)
                _image_refcount_adjust(temp_uar, -1)
            elif PLATFORM != "SunOS":
                temp_uar = os.path.join(CONF.solaris_ipmi.imagecache_dirname,
                                        url.path.replace("/", ""))
                _image_refcount_adjust(temp_uar, -1)

    def take_over(self, _task):
        """Take over management of this task's node from a dead conductor."""
        """ TODO(mattk): Determine if this is required"""
        LOG.debug("SolarisDeploy.take_over()")


class SolarisManagement(base.ManagementInterface):
    """Management class for solaris nodes."""

    def get_properties(self):
        """Return Solaris driver properties"""
        return COMMON_PROPERTIES

    def __init__(self):
        try:
            ipmitool._check_option_support(['timing', 'single_bridge',
                                            'dual_bridge'])
        except OSError:
            raise exception.DriverLoadError(
                driver=self.__class__.__name__,
                reason=_("Unable to locate usable ipmitool command in "
                         "the system path when checking ipmitool version"))
        ipmitool._check_temp_dir()

    def validate(self, task):
        """Check that 'driver_info' contains IPMI credentials.

        Validates whether the 'driver_info' property of the supplied
        task's node contains the required credentials information.

        :param task: a task from TaskManager.
        :raises: InvalidParameterValue if required IPMI parameters
            are missing.
        :raises: MissingParameterValue if a required parameter is missing.

        """
        _parse_driver_info(task.node)

    def get_supported_boot_devices(self, task=None):
        """Get a list of the supported boot devices.

        :param task: a task from TaskManager.
        :returns: A list with the supported boot devices defined
                  in :mod:`ironic.common.boot_devices`.

        """
        if task is None:
            return [boot_devices.PXE, boot_devices.DISK, boot_devices.CDROM,
                    boot_devices.BIOS, boot_devices.SAFE]
        else:
            # Get architecture of node and return supported boot devices
            cpu_arch = _get_node_architecture(task.node)
            if cpu_arch == 'x86':
                return [boot_devices.PXE, boot_devices.DISK,
                        boot_devices.CDROM, boot_devices.BIOS,
                        boot_devices.SAFE]
            elif cpu_arch == 'SPARC':
                return [boot_devices.DISK, boot_devices.WANBOOT]
            else:
                raise exception.InvalidParameterValue(
                    _("Invalid node architecture of '%s'.") % (cpu_arch))

    @task_manager.require_exclusive_lock
    def set_boot_device(self, task, device, persistent=False):
        """Set the boot device for the task's node.

        Set the boot device to use on next reboot of the node.

        :param task: a task from TaskManager.
        :param device: the boot device, one of
                       :mod:`ironic.common.boot_devices`.
        :param persistent: Boolean value. True if the boot device will
                           persist to all future boots, False if not.
                           Default: False.
        :raises: InvalidParameterValue if an invalid boot device is specified
        :raises: MissingParameterValue if required ipmi parameters are missing.
        :raises: IPMIFailure on an error from ipmitool.

        """
        LOG.debug("SolarisManagement.set_boot_device: %s" % device)

        cpu_arch = _get_node_architecture(task.node)
        archive_uri = task.node.driver_info.get('archive_uri')
        publishers = task.node.driver_info.get('publishers')
        fmri = task.node.driver_info.get('fmri')

        if task.node.driver_info.get('ipmi_force_boot_device', False):
            driver_utils.force_persistent_boot(task,
                                               device,
                                               persistent)
            # Reset persistent to False, in case of BMC does not support
            # persistent or we do not have admin rights.
            persistent = False

        if cpu_arch == 'x86':
            if device not in self.get_supported_boot_devices(task=task):
                raise exception.InvalidParameterValue(_(
                    "Invalid boot device %s specified.") % device)
            cmd = ["chassis", "bootdev", device]
            if persistent:
                cmd.append("options=persistent")
        elif cpu_arch == 'SPARC':
            # Set bootmode script to network DHCP or disk
            if device == boot_devices.WANBOOT:
                boot_cmd = 'set /HOST/bootmode script="'
                script_str = 'boot net:dhcp - install'
                if archive_uri:
                    new_uri, auth_token = _format_archive_uri(task,
                                                              archive_uri)
                    script_str += ' archive_uri=%s' % (new_uri)

                    if auth_token is not None:
                        # Add auth_token to boot arg, AI archive transfer will
                        # use this by setting X-Auth-Token header when using
                        # curl to retrieve archive from glance.
                        script_str += ' auth_token=%s' % \
                            (task.context.auth_token)

                if publishers:
                    pub_list = [pub.strip() for pub in publishers.split('+')
                                if pub.strip()]
                    script_str += ' publishers=%s' % ('+'.join(pub_list))

                if fmri:
                    pkg_list = [pkg.strip() for pkg in fmri.split('+')
                                if pkg.strip()]
                    script_str += ' fmri=%s' % ('+'.join(pkg_list))

                # bootmode script property has a size restriction of 255
                # characters raise error if this is breached.
                if len(script_str) > 255:
                    raise exception.InvalidParameterValue(_(
                        "SPARC firmware bootmode script length exceeds 255:"
                        " %s") % script_str)
                boot_cmd += script_str + '"'
                cmd = ['sunoem', 'cli', boot_cmd]
            elif device == boot_devices.DISK:
                cmd = ['sunoem', 'cli',
                       'set /HOST/bootmode script=""']
            else:
                raise exception.InvalidParameterValue(_(
                    "Invalid boot device %s specified.") % (device))
        else:
            raise exception.InvalidParameterValue(
                _("Invalid node architecture of '%s'.") % (cpu_arch))

        driver_info = _parse_driver_info(task.node)
        try:
            _out, _err = _exec_ipmitool(driver_info, cmd)
        except (exception.PasswordFileFailedToCreate,
                processutils.ProcessExecutionError) as err:
            LOG.warning(_LW('IPMI set boot device failed for node %(node)s '
                            'when executing "ipmitool %(cmd)s". '
                            'Error: %(error)s'),
                        {'node': driver_info['uuid'],
                         'cmd': cmd, 'error': err})
            raise exception.IPMIFailure(cmd=cmd)

    def get_boot_device(self, task):
        """Get the current boot device for the task's node.

        Returns the current boot device of the node.

        :param task: a task from TaskManager.
        :raises: InvalidParameterValue if required IPMI parameters
            are missing.
        :raises: IPMIFailure on an error from ipmitool.
        :raises: MissingParameterValue if a required parameter is missing.
        :returns: a dictionary containing:

            :boot_device: the boot device, one of
                :mod:`ironic.common.boot_devices` or None if it is unknown.
            :persistent: Whether the boot device will persist to all
                future boots or not, None if it is unknown.

        """
        LOG.debug("SolarisManagement.get_boot_device")
        driver_info = task.node.driver_info
        driver_internal_info = task.node.driver_internal_info

        if (driver_info.get('ipmi_force_boot_device', False) and
                driver_internal_info.get('persistent_boot_device') and
                driver_internal_info.get('is_next_boot_persistent', True)):
            return {
                'boot_device': driver_internal_info['persistent_boot_device'],
                'persistent': True
            }

        cpu_arch = _get_node_architecture(task.node)
        driver_info = _parse_driver_info(task.node)
        response = {'boot_device': None, 'persistent': None}

        if cpu_arch == 'x86':
            cmd = ["chassis", "bootparam", "get", "5"]
        elif cpu_arch == 'SPARC':
            cmd = ['sunoem', 'getval', '/HOST/bootmode/script']
        else:
            raise exception.InvalidParameterValue(
                _("Invalid node architecture of '%s'.") % (cpu_arch))

        try:
            out, _err = _exec_ipmitool(driver_info, cmd)
        except (exception.PasswordFileFailedToCreate,
                processutils.ProcessExecutionError) as err:
            LOG.warning(_LW('IPMI get boot device failed for node %(node)s '
                            'when executing "ipmitool %(cmd)s". '
                            'Error: %(error)s'),
                        {'node': driver_info['uuid'],
                         'cmd': cmd, 'error': err})
            raise exception.IPMIFailure(cmd=cmd)

        if cpu_arch == 'x86':
            re_obj = re.search('Boot Device Selector : (.+)?\n', out)
            if re_obj:
                boot_selector = re_obj.groups('')[0]
                if 'PXE' in boot_selector:
                    response['boot_device'] = boot_devices.PXE
                elif 'Hard-Drive' in boot_selector:
                    if 'Safe-Mode' in boot_selector:
                        response['boot_device'] = boot_devices.SAFE
                    else:
                        response['boot_device'] = boot_devices.DISK
                elif 'BIOS' in boot_selector:
                    response['boot_device'] = boot_devices.BIOS
                elif 'CD/DVD' in boot_selector:
                    response['boot_device'] = boot_devices.CDROM

            response['persistent'] = 'Options apply to all future boots' in out
        elif cpu_arch == 'SPARC':
            if "net:dhcp" in out:
                response['boot_device'] = boot_devices.WANBOOT
            else:
                response['boot_device'] = boot_devices.DISK
        LOG.debug(response)
        return response

    def get_sensors_data(self, task):
        """Get sensors data.

        :param task: a TaskManager instance.
        :raises: FailedToGetSensorData when getting the sensor data fails.
        :raises: FailedToParseSensorData when parsing sensor data fails.
        :raises: InvalidParameterValue if required ipmi parameters are missing
        :raises: MissingParameterValue if a required parameter is missing.
        :returns: returns a dict of sensor data group by sensor type.

        """
        driver_info = _parse_driver_info(task.node)
        # with '-v' option, we can get the entire sensor data including the
        # extended sensor informations
        cmd = ['sdr', '-v']
        try:
            out, _err = _exec_ipmitool(driver_info, cmd)
        except (exception.PasswordFileFailedToCreate,
                processutils.ProcessExecutionError) as err:
            raise exception.FailedToGetSensorData(node=task.node.uuid,
                                                  error=err)

        return ipmitool._parse_ipmi_sensors_data(task.node, out)


class SolarisInspect(base.InspectInterface):
    """Inspect class for solaris nodes."""

    def get_properties(self):
        """Return Solaris driver properties"""
        return COMMON_PROPERTIES

    def validate(self, task):
        """Validate driver_info containts IPMI credentials.

        Ensure 'driver_info' containers the required IPMI
        properties used to access a nodes properties.

        :param task: a TaskManager instance
        :raises: InvalidParameterValue if required IPMI parameters
            are missing.
        :raises: MissingParameterValue if a required parameter is missing.
        """
        _parse_driver_info(task.node)

    def inspect_hardware(self, task):
        """Inspect hardware to get the hardware properties.

        Inspects hardware to get the defined IPMI_PROPERTIES.
        Failure occures if any of the defined IPMI_PROPERTIES are not
        determinable from the node.

        :param task: a TaskManager instance
        :raises: HardwareInspectionFailure if properties could
                 not be retrieved successfully.
        :returns: the resulting state of inspection.
        """
        LOG.debug("SolarisInspect.inspect_hardware")

        ipmi_props = self._get_ipmi_properties(task)

        keys, _none = zip(*IPMI_PROPERTIES)
        vallist = [line.split(': ')[1]
                   for line in ipmi_props.strip().splitlines()]
        propdict = dict(zip(keys, vallist))

        # Installed memory size is returned in GB, Nova assumes this is MB
        # so convert if returned in GB
        try:
            size_bytes = strutils.string_to_bytes(
                propdict['memory_mb'].replace(' ', ''))
            propdict['memory_mb'] = int(size_bytes / float(1 << 20))
        except ValueError:
            # Size conversion failed, just ensure value is an int
            propdict['memory_mb'] = int(propdict['memory_mb'])

        if propdict['local_gb'] == 'Not Available':
            del propdict['local_gb']
        else:
            # Local disk size can be returned with size type identifier
            # remove identifier as this needs to be an int value
            try:
                size_bytes = strutils.string_to_bytes(
                    propdict['local_gb'].replace(' ', ''))
                propdict['local_gb'] = int(size_bytes / float(1 << 30))
            except ValueError:
                # Size conversion failed, just ensure value is an int
                propdict['local_gb'] = int(propdict['local_gb'])

        cpu_props = self._get_cpu_cores(task, propdict['cpus'])

        vallist = [line.split(': ')[1]
                   for line in cpu_props.strip().splitlines()]

        try:
            total_cores = sum(map(int, vallist))
            propdict['cores'] = total_cores
        except ValueError:
            propdict['cores'] = 'N/A'

        node_properties = task.node.properties
        node_properties.update(propdict)
        task.node.properties = node_properties
        task.node.save()

        self._create_port_if_not_exist(task.node, node_properties['mac'])
        LOG.info(_LI("Node %s inspected."), task.node.uuid)
        return states.MANAGEABLE

    def _get_ipmi_properties(self, task):
        """Retrieve IPMI_PROPERTIES from node
        :param task: a TaskManager instance.
        :returns: ipmitool retrieved property values
        """
        fh = tempfile.NamedTemporaryFile()
        for _none, prop in IPMI_PROPERTIES:
            fh.write('sunoem getval %s\n' % prop)
        fh.seek(0)
        cmd = ["exec", fh.name]
        driver_info = _parse_driver_info(task.node)

        try:
            out, _err = _exec_ipmitool(driver_info, cmd)
        except (exception.PasswordFileFailedToCreate,
                processutils.ProcessExecutionError) as err:
            LOG.warning(_LW('IPMI inspect properties failed for node %(node)s '
                            'when executing "ipmitool %(cmd)s". '
                            'Error: %(error)s'),
                        {'node': task.node.uuid,
                         'cmd': cmd, 'error': err})
            raise exception.IPMIFailure(cmd=cmd)
        fh.close()

        return out

    def _get_cpu_cores(self, task, cpus):
        """Retrieve IPMI_PROPERTIES from node
        :param task: a TaskManager instance.
        :param cpus: CPU numbers to use.
        :returns: ipmitool retrieved property values
        """
        fh = tempfile.NamedTemporaryFile()
        for i in range(int(cpus)):
            fh.write('sunoem getval %s\n' % (CPU_LOCATION % i))
        fh.seek(0)
        cmd = ["exec", fh.name]
        driver_info = _parse_driver_info(task.node)

        try:
            out, _err = _exec_ipmitool(driver_info, cmd)
        except (exception.PasswordFileFailedToCreate,
                processutils.ProcessExecutionError) as err:
            LOG.warning(_LW('IPMI CPU inspection failed for node %(node)s '
                            'when executing "ipmitool %(cmd)s". '
                            'Error: %(error)s'),
                        {'node': task.node.uuid,
                         'cmd': cmd, 'error': err})
            raise exception.IPMIFailure(cmd=cmd)
        fh.close()
        return out

    def _create_port_if_not_exist(self, node, mac):
        """Create ironic port if not existing for this MAC
        :param task: Node to creaate port for.
        :param mac: MAC address to use for port.
        """
        node_id = node.id
        port_dict = {'address': mac, 'node_id': node_id}
        mydbapi = dbapi.get_instance()
        try:
            mydbapi.create_port(port_dict)
            LOG.info(_LI("Port created for MAC address %(mac)s for node "
                         "%(node)s."), {'mac': mac, 'node': node.uuid})
        except exception.MACAlreadyExists:
            LOG.warn(_LW("Port already exists for MAC address %(mac)s "
                         "for node %(node)s."),
                     {'mac': mac, 'node': node.uuid})


class AIService():
    """AI Service"""

    def __init__(self, task, name):
        """Initialize AIService object

        :param task: a TaskManager instance
        :param name: AI Service name
        """
        LOG.debug("AIService.__init__()")
        self.task = task
        self.name = name
        self._clients = list()
        self._image_path = None
        self._manifests = list()
        self._profiles = list()
        self._ssh_obj = None
        self._derived_manifest = None

    @property
    def ssh_obj(self):
        """paramiko.SSHClient active connection"""
        LOG.debug("AIService.ssh_obj")
        if self._ssh_obj is None:
            self._ssh_obj = self._get_ssh_connection()
        return self._ssh_obj

    @property
    def manifests(self):
        """list() of manifest names for this service"""
        LOG.debug("AIService.manifests")
        if not self._manifests:
            self._manifests = self._get_manifest_names()
        return self._manifests

    @property
    def profiles(self):
        """list() of profile names for this service"""
        LOG.debug("AIService.profiles")
        if not self._profiles:
            self._profiles = self._get_profile_names()
        return self._profiles

    @property
    def clients(self):
        """list() of all client names(mac addresses) On AI Server"""
        LOG.debug("AIService.clients")
        if not self._clients:
            self._clients = self._get_all_client_names()
        return self._clients

    @property
    def exists(self):
        """True/False indicator of this service exists of not"""
        LOG.debug("AIService.exists")
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm list -n " + self.name
        try:
            stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            return False

        if self.name != self._parse_service_name(stdout):
            return False
        else:
            return True

    @property
    def image_path(self):
        """image_path for this service"""
        LOG.debug("AIService.image_path")
        if self._image_path is None:
            self._image_path = self._get_image_path()
        return self._image_path

    @property
    def derived_manifest(self):
        """Access default derived manifest URI"""
        LOG.debug("AIService.derived_manifest")
        if not self._derived_manifest:
            self._derived_manifest = CONF.ai.derived_manifest
        return self._derived_manifest

    def create_service(self, archive_uri):
        """Create a new AI Service for this object

        :param archive_uri: archive_uri to create service from
        """

        LOG.debug("AIService.create_service(): %s" % (self.name))

        if PLATFORM == "SunOS":
            # 1. Fetch archive
            mount_dir, temp_uar = _mount_archive(self.task, archive_uri)
            iso, uuid = _get_archive_iso_and_uuid(mount_dir)
        else:
            # 1. Fetch archive and Extract ISO file
            temp_uar = _fetch_uri(self.task, archive_uri)
            iso, uuid = _get_archive_iso_and_uuid(temp_uar, extract_iso=True)

        # 2. scp AI ISO from archive to AI Server
        remote_iso = os.path.join("/tmp", uuid) + ".iso"
        try:
            self.copy_remote_file(iso, remote_iso)
        except:
            if PLATFORM == "SunOS":
                _umount_archive(mount_dir)
                if urlparse(archive_uri).scheme == "glance":
                    _image_refcount_adjust(temp_uar, -1)
            else:
                shutil.rmtree(os.path.dirname(iso))
                _image_refcount_adjust(temp_uar, -1)
            raise

        if PLATFORM != "SunOS":
            # Remove temp extracted ISO file
            shutil.rmtree(os.path.dirname(iso))

        # 3. Create a new AI Service
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm create-service " + \
            " -y -n " + uuid + " -s " + remote_iso

        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
            self.name = uuid
            self._clients = []
            self._manifests = []
            self._profiles = []

        except Exception as _err:
            self.delete_remote_file(remote_iso)
            if PLATFORM == "SunOS":
                _umount_archive(mount_dir)
            else:
                _image_refcount_adjust(temp_uar, -1)
            raise AICreateServiceFail(
                _("Failed to create AI Service %s") % (uuid))

        # 4. Remove copy of AI ISO on AI Server
        self.delete_remote_file(remote_iso)

        if PLATFORM == "SunOS":
            # 5. Unmount UAR
            _umount_archive(mount_dir)

        # 6. Decrement reference count for image
        if temp_uar is not None:
            _image_refcount_adjust(temp_uar, -1)

    def delete_service(self):
        """Delete the current AI Service"""
        LOG.debug("AIService.delete_service():name: %s" % (self.name))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm delete-service" + \
            " -r -y -n " + self.name

        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AIDeleteServiceFail(
                _("Failed to delete AI Service %s") % (self.name))

    def create_client(self, mac, cpu_arch, archive_uri, auth_token,
                      publishers, fmri):
        """Create a client associated with this service

        :param mac: MAC Address of client to create
        :param cpu_arch: Machine architecture for this node
        :param archive_uri: URI of archive to install node from
        :param auth_token: Authorization token for glance UAR retrieval
        :param publishers: IPS publishers list in name@origin format
        :param fmri: IPS package FMRIs to install
        :returns: Nothing exception raised if deletion fails
        """
        LOG.debug("AIService.create_client():mac: %s" % (mac))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm create-client -e " + \
            mac + " -n " + self.name

        # Add specific boot arguments for 'x86' clients only
        if cpu_arch == 'x86':
            ai_cmd += " -b install=true,console=ttya"

            if archive_uri:
                ai_cmd += ",archive_uri=%s" % (archive_uri)

            if auth_token:
                ai_cmd += ",auth_token=%s" % (auth_token)

            if publishers:
                pub_list = [pub.strip() for pub in publishers.split('+')
                            if pub.strip()]
                ai_cmd += ",publishers='%s'" % ('+'.join(pub_list))

            if fmri:
                pkg_list = [pkg.strip() for pkg in fmri.split('+')
                            if pkg.strip()]
                ai_cmd += ",fmri='%s'" % ('+'.join(pkg_list))

        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AICreateClientFail(_("Failed to create AI Client %s") %
                                     (mac))

        # If cpu_arch x86 customize grub reducing grub menu timeout to 0
        if cpu_arch == 'x86':
            custom_grub = "/tmp/%s.grub" % (mac)
            ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm export -e " + \
                mac + " -G | /usr/bin/sed -e 's/timeout=30/timeout=0/'" + \
                " > %s" % (custom_grub)
            try:
                _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
            except Exception as _err:
                raise AICreateClientFail(
                    _("Failed to create custom grub menu for %s.") % (mac))

            ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm set-client -e " + \
                mac + " -G %s" % (custom_grub)
            try:
                _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
            except Exception as _err:
                raise AICreateClientFail(
                    _("Failed to customize AI Client %s grub menu.") % (mac))

            self.delete_remote_file(custom_grub)

        self._clients = self._get_all_client_names()

    def delete_client(self, mac):
        """Delete a specific client regardless of service association

        :param mac: MAC Address of client to remove
        :returns: Nothing exception raised if deletion fails
        """
        LOG.debug("AIService.delete_client():mac: %s" % (mac))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm delete-client -e " + mac
        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AIDeleteClientFail(_("Failed to delete AI Client %s") %
                                     (mac))

        # update list of clients for this service
        self._clients = self._get_all_client_names()

    def create_manifest(self, manifest_name, manifest_path, mac):
        """Create a manifest associated with this service

        :param manifest_name: manifest_name to create
        :param manifest_path: path to manifest file to use
        :param mac: MAC address to add as criteria
        :returns: Nothing exception raised if creation fails
        """
        LOG.debug("AIService.create_manifest():manifest_name: "
                  "'%s', manifest_path: '%s', mac: '%s'" %
                  (manifest_name, manifest_path, mac))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm create-manifest -n " + \
            self.name + " -m " + manifest_name + " -f " + manifest_path + \
            " -c mac=" + mac
        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AICreateManifestFail(_("Failed to create AI Manifest %s.") %
                                       (manifest_name))

        # Update list of manifests for this service
        self._manifests = self._get_manifest_names()

    def delete_manifest(self, manifest_name):
        """Delete a specific manifest

        :param manifest_name: name of manifest to remove
        :returns: Nothing exception raised if deletion fails
        """
        LOG.debug("AIService.delete_manifest():manifest_name: %s" %
                  (manifest_name))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm delete-manifest -m " + \
            manifest_name + " -n " + self.name
        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AIDeleteManifestFail(_("Failed to delete AI Manifest %s") %
                                       (manifest_name))

        # Update list of manifests for this service
        self._manifests = self._get_manifest_names()

    def create_profile(self, profile_name, profile_path, mac, env):
        """Create a profile associated with this service

        :param profile)_name: profile name to create
        :param profile_path: path to profile file to use
        :param mac: MAC address to add as criteria
        :param env: Environment to apply profile to
        :returns: Nothing exception raised if creation fails
        """
        LOG.debug("AIService.create_profile():profile_name: "
                  "'%s', profile_path: '%s', mac: '%s'" %
                  (profile_name, profile_path, mac))

        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm create-profile -n " + \
            self.name + " -p " + profile_name + " -f " + profile_path + \
            " -c mac=" + mac

        if env is not None:
            ai_cmd = ai_cmd + " -e " + env

        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AICreateProfileFail(_("Failed to create AI Profile %s.") %
                                      (profile_name))

        # Update list of profiles for this service
        self._profiles = self._get_profile_names()

    def delete_profile(self, profile_name):
        """Delete a specific profile

        :param profile_name: name of profile to remove
        :returns: Nothing exception raised if deletion fails
        """
        LOG.debug("AIService.delete_profile():profile_name: %s" %
                  (profile_name))
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm delete-profile -p " + \
            profile_name + " -n " + self.name
        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as _err:
            raise AIDeleteProfileFail(_("Failed to delete AI Profile %s") %
                                      (profile_name))

        # Update list of profiles for this service
        self._profiles = self._get_profile_names()

    def copy_remote_file(self, local, remote):
        """Using scp copy local file to remote location

        :param local: Local file path to copy
        :param remote: Remote file path to copy to
        :returns: Nothing, exception raised on failure
        """
        LOG.debug("AIService.copy_remote_file():local: %s, remote: %s" %
                  (local, remote))
        try:
            scp = SCPClient(self.ssh_obj.get_transport())
            scp.put(local, remote)
        except Exception as err:
            err_msg = _("Failed to copy file to remote server: %s") % err
            raise SolarisIPMIError(msg=err_msg)

    def delete_remote_file(self, path):
        """Remove remote file in AI Server

        :param path: Path of remote file to remove
        :return: Nothing exception raised on failure
        """
        LOG.debug("AIService.delete_remote_file():path: %s" %
                  (path))

        ai_cmd = "/usr/bin/rm -f " + path
        try:
            _stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)
        except Exception as err:
            err_msg = _("Failed to delete remote file: %s") % err
            raise SolarisIPMIError(msg=err_msg)

    def _get_image_path(self):
        """Retrieve image_path for this service

        :returns: image_path property
        """
        LOG.debug("AIService._get_image_path()")
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm list -vn " + self.name
        stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd)

        for line in stdout.splitlines():
            words = line.split()
            if len(words) > 2 and words[0] == "Image" and words[1] == "Path":
                image_path = words[-1]
        LOG.debug("AIService._get_image_path():image_path: %s" % (image_path))
        return image_path

    def _parse_client(self, list_out):
        """Return service name and client from installadm list -e output

        :param list_out: stdout from installadm list -e
        :returns: Service Name and MAC Address
        """
        LOG.debug("AIService._parse_client():list_out: %s" % (list_out))
        lines = list_out.splitlines()
        service_name = None
        client_name = None

        if len(lines[2].split()[0]) > 0:
            service_name = lines[2].split()[0]

        if len(lines[2].split()[1]) > 0:
            client_name = lines[2].split()[1]

        LOG.debug("AIService._parse_client():service_name: %s" %
                  (service_name))
        LOG.debug("AIService._parse_client():client_name: %s" % (client_name))
        return service_name, client_name

    def _parse_service_name(self, list_out):
        """Given installadm list -n output, parse out service name

        :param list_out: stdout from installadm list -n
        :returns: Service Name
        """
        LOG.debug("AIService._parse_service_name():list_out: %s" % (list_out))
        service_name = None

        lines = list_out.splitlines()
        if len(lines[2].split()[0]) > 0:
            service_name = lines[2].split()[0]

        LOG.debug("AIService._parse_service_name():service_name: %s" %
                  (service_name))
        return service_name

    def _get_ssh_connection(self):
        """Returns an SSH client connected to a node.

        :returns: paramiko.SSHClient, an active ssh connection.
        """
        LOG.debug("AIService._get_ssh_connection()")
        return utils.ssh_connect(self._get_ssh_dict())

    def _get_ssh_dict(self):
        """Generate SSH Dictionary for SSH Connection via paramiko

        :returns: dictionary for paramiko connection
        """
        LOG.debug("AIService._get_ssh_dict()")
        if not CONF.ai.server or CONF.ai.server == "None" or \
                not CONF.ai.username or CONF.ai.username == "None":
            raise exception.InvalidParameterValue(_(
                "SSH server and username must be set."))

        ssh_dict = {
            'host': CONF.ai.server,
            'username': CONF.ai.username,
            'port': int(CONF.ai.port),
            'timeout': int(CONF.ai.timeout)
            }

        key_contents = key_filename = password = None
        if CONF.ai.ssh_key_contents and CONF.ai.ssh_key_contents != "None":
            key_contents = CONF.ai.ssh_key_contents
        if CONF.ai.ssh_key_file and CONF.ai.ssh_key_file != "None":
            key_filename = CONF.ai.ssh_key_file
        if CONF.ai.password and CONF.ai.password != "None":
            password = CONF.ai.password

        if len(filter(None, (key_filename, key_contents))) != 1:
            raise exception.InvalidParameterValue(_(
                "SSH requires one and only one of "
                "ssh_key_file or ssh_key_contents to be set."))
        if password:
            ssh_dict['password'] = password

        if key_contents:
            ssh_dict['key_contents'] = key_contents
        else:
            if not os.path.isfile(key_filename):
                raise exception.InvalidParameterValue(_(
                    "SSH key file %s not found.") % key_filename)
            ssh_dict['key_filename'] = key_filename
        LOG.debug("AIService._get_ssh_dict():ssh_dict: %s" % (ssh_dict))
        return ssh_dict

    def _get_manifest_names(self):
        """Get a list of manifest names for this service

        :returns: list() of manifest names
        """
        LOG.debug("AIService._get_manifest_names()")
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm list -mn " + self.name
        stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd,
                                   err_msg=_("Failed to retrieve manifests"
                                             " for service %s") % (self.name))
        return self._parse_names(stdout)

    def _get_profile_names(self):
        """Get a list of profile names for this service

        :returns: list() of profile names
        """
        LOG.debug("AIService._get_profile_names()")
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm list -pn " + self.name
        stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd,
                                   err_msg=_("Failed to retrieve profiles for "
                                             "service %s") % (self.name))
        return self._parse_names(stdout)

    def _get_all_client_names(self):
        """Get a list of client names for this service

        :returns: list() of client/mac names
        """
        LOG.debug("AIService._get_all_client_names()")
        ai_cmd = "/usr/bin/pfexec /usr/sbin/installadm list -c"
        stdout, _rc = _ssh_execute(self.ssh_obj, ai_cmd,
                                   err_msg=_("Failed to retrieve clients for "
                                             "service %s") % (self.name))
        # Store client names all in lower case
        return [client.lower() for client in self._parse_names(stdout)]

    def _parse_names(self, list_out):
        """Parse client/manifest/profile names from installadm list output

        Note: when we convert to using RAD, parsing installadm CLI output
            will not be required, as API will return a list of names.

        :param list_out: stdout from installadm list -c or -mn or -pn
        :returns: a list of client/manifest/profile names
        """
        LOG.debug("AIService._parse_names():list_out: %s" %
                  (list_out))
        names = []
        lines = list_out.splitlines()

        # Get index into string for client/manifest/profile names
        # client/manifest/profile names are all in 2nd column of output
        if len(lines) > 1:
            col_start = lines[1].index(" --") + 1
            col_end = lines[1][col_start:].index(" --") + 1 + col_start

            for line in range(2, len(lines)):
                if lines[line][col_start:col_end].strip():
                    names.append(lines[line][col_start:col_end].strip())

        LOG.debug("AIService._parse_names():names: %s" % (names))
        return names


# Custom Exceptions
class AICreateServiceFail(exception.IronicException):
    """Exception type for AI Service creation failure"""
    pass


class AIDeleteServiceFail(exception.IronicException):
    """Exception type for AI Service deletion failure"""
    pass


class AICreateClientFail(exception.IronicException):
    """Exception type for AI Client creation failure"""
    pass


class AIDeleteClientFail(exception.IronicException):
    """Exception type for AI Client deletion failure"""
    pass


class AICreateManifestFail(exception.IronicException):
    """Exception type for AI Manifest creation failure"""
    pass


class AIDeleteManifestFail(exception.IronicException):
    """Exception type for AI Manifest deletion failure"""
    pass


class AICreateProfileFail(exception.IronicException):
    """Exception type for AI Profile creation failure"""
    pass


class AIDeleteProfileFail(exception.IronicException):
    """Exception type for AI Profile deletion failure"""
    pass


class SolarisIPMIError(exception.IronicException):
    """Generic Solaris IPMI driver exception"""
    message = _("%(msg)s")
