# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
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
# @author: Girish Moodalbail, Oracle, Inc.

from openstack_common import get_ovsdb_info

from oslo_config import cfg
from oslo_log import log as logging
from oslo_serialization import jsonutils

from neutron.agent.common import ovs_lib
from neutron.agent.linux import utils
from neutron.agent.solaris import net_lib
from neutron.common import exceptions
from neutron.plugins.common import constants as p_const


LOG = logging.getLogger(__name__)

OPTS = [
    cfg.StrOpt('admin_user',
               help=_("Admin username")),
    cfg.StrOpt('admin_password',
               help=_("Admin password"),
               secret=True),
    cfg.StrOpt('admin_tenant_name',
               help=_("Admin tenant name")),
    cfg.StrOpt('auth_url',
               help=_("Authentication URL")),
    cfg.StrOpt('auth_strategy', default='keystone',
               help=_("The type of authentication to use")),
    cfg.StrOpt('auth_region',
               help=_("Authentication region")),
    cfg.StrOpt('endpoint_type',
               default='publicURL',
               help=_("Network service endpoint type to pull from "
                      "the keystone catalog")),
]


class OVSInterfaceDriver(object):
    """Driver used to manage Solaris OVS VNICs.

    This class provides methods to create/delete a Crossbow VNIC and
    add it as a port of OVS bridge.
    TODO(gmoodalb): More methods to implement here for MITAKA??
    """

    # TODO(gmoodalb): dnsmasq uses old style `ifreq', so 16 is the maximum
    # length including the NUL character. If we change it to use new style
    # `lifreq', then we will be able to extend the length to 32 characters.
    VNIC_NAME_MAXLEN = 15
    VNIC_NAME_PREFIX = 'dh'
    VNIC_NAME_SUFFIX = '_0'
    VNIC_NAME_LEN_WO_SUFFIX = VNIC_NAME_MAXLEN - \
        len(VNIC_NAME_SUFFIX)

    def __init__(self, conf):
        self.conf = conf
        self._neutron_client = None

    @property
    def neutron_client(self):
        if self._neutron_client:
            return self._neutron_client
        from neutronclient.v2_0 import client
        self._neutron_client = client.Client(
            username=self.conf.admin_user,
            password=self.conf.admin_password,
            tenant_name=self.conf.admin_tenant_name,
            auth_url=self.conf.auth_url,
            auth_strategy=self.conf.auth_strategy,
            region_name=self.conf.auth_region,
            endpoint_type=self.conf.endpoint_type
        )
        return self._neutron_client

    def fini_l3(self, device_name):
        ipif = net_lib.IPInterface(device_name)
        ipif.delete_ip()

    def init_l3(self, device_name, ip_cidrs, addrconf=False):
        """Set the L3 settings for the interface using data from the port.
           ip_cidrs: list of 'X.X.X.X/YY' strings
        """
        ipif = net_lib.IPInterface(device_name)
        for ip_cidr in ip_cidrs:
            ipif.create_address(ip_cidr)
        if addrconf:
            ipif.create_addrconf()

    # TODO(gmoodalb): - probably take PREFIX?? for L3
    def get_device_name(self, port):
        vnicname = (self.VNIC_NAME_PREFIX +
                    port.id)[:self.VNIC_NAME_LEN_WO_SUFFIX]
        vnicname += self.VNIC_NAME_SUFFIX
        return vnicname.replace('-', '_')

    def plug(self, tenant_id, network_id, port_id, datalink_name, mac_address,
             network=None, bridge=None, namespace=None, prefix=None,
             protection=False, mtu=None, vif_type=None):
        """Plug in the interface."""

        if net_lib.Datalink.datalink_exists(datalink_name):
            LOG.info(_("Device %s already exists"), datalink_name)
            return

        if bridge is None:
            bridge = self.conf.ovs_integration_bridge

        # check if bridge exists
        ovs = ovs_lib.OVSBridge(bridge)
        if not ovs.bridge_exists(bridge):
            raise exceptions.BridgeDoesNotExist(bridge=bridge)

        if network is None:
            network = self.neutron_client.show_network(network_id)['network']

        network_type = network.get('provider:network_type')
        vid = None
        lower_link = None
        if network_type == p_const.TYPE_VXLAN:
            lower_link = 'ovs.vxlan1'
        elif network_type in [p_const.TYPE_VLAN, p_const.TYPE_FLAT]:
            phys_network = network.get('provider:physical_network')
            # For integration bridge the ovs agent will take care of
            # adding the vlan id
            if bridge != self.conf.ovs_integration_bridge:
                vid = network.get('provider:segmentation_id')
            # need to determine the bridge mapping
            try:
                results = get_ovsdb_info('Open_vSwitch', ['other_config'])
            except Exception as err:
                LOG.error(_("Failed to retrieve other_config from %s: %s"),
                          bridge, err)
                raise
            other_config = results[0]['other_config']
            if not other_config:
                msg = (_("'other_config' column in 'Open_vSwitch' OVSDB table "
                         "is not configured. Please configure it so that "
                         "lower-link can be determined for the VNICs"))
                raise exceptions.Invalid(message=msg)
            bridge_mappings = other_config.get('bridge_mappings')
            if not bridge_mappings:
                msg = (_("'bridge_mappings' info is not set in 'other_config' "
                         "column of 'Open_vSwitch' OVSDB table. Please "
                         "configure it so that lower-link can be determined "
                         "for the VNICs"))
                raise exceptions.Invalid(message=msg)
            for bridge_mapping in bridge_mappings.split(','):
                if phys_network not in bridge_mapping:
                    continue
                lower_link = bridge_mapping.split(':')[1]
                break
        else:
            # TYPE_GRE and TYPE_LOCAL
            msg = (_("Unsupported network type: %s") % network_type)
            LOG.error(msg)
            raise exceptions.Invalid(message=msg)

        # if lower_link is not set or empty, we need to fail
        if not lower_link:
            msg = (_("Failed to determine the lower_link for VNIC "
                     "%s on physical_network %s") %
                   (datalink_name, phys_network))
            LOG.error(msg)
            raise exceptions.Invalid(message=msg)

        if vif_type == 'binding_failed':
            msg = (_('Port binding has failed for %s. Ensure that '
                     'OVS agent is running and/or bridge_mappings are '
                     'correctly configured. Port will not have network '
                     'connectivity') % datalink_name)
            LOG.error(msg)

        dl = net_lib.Datalink(datalink_name)
        dl.create_vnic(lower_link, mac_address, vid, temp=True)

        attrs = [('external_ids', {'iface-id': port_id,
                                   'iface-status': 'active',
                                   'attached-mac': mac_address})]
        ovs.replace_port(datalink_name, *attrs)

    def unplug(self, datalink_name, bridge=None, namespace=None, prefix=None):
        """Unplug the interface."""

        # remove any IP addresses on top of this datalink, otherwise we will
        # get 'device busy' error while deleting the datalink
        self.fini_l3(datalink_name)

        dl = net_lib.Datalink(datalink_name)
        dl.delete_vnic()

        if bridge is None:
            bridge = self.conf.ovs_integration_bridge

        # check if bridge exists
        ovs = ovs_lib.OVSBridge(bridge)
        if not ovs.bridge_exists(bridge):
            raise exceptions.BridgeDoesNotExist(bridge=bridge)

        try:
            ovs.delete_port(datalink_name)
            LOG.debug("Unplugged interface '%s'", datalink_name)
        except RuntimeError as err:
            LOG.error(_("Failed unplugging interface '%s': %s") %
                      (datalink_name, err))

    @property
    def use_gateway_ips(self):
        """Whether to use gateway IPs instead of unique IP allocations.

        In each place where the DHCP agent runs, and for each subnet for
        which DHCP is handling out IP addresses, the DHCP port needs -
        at the Linux level - to have an IP address within that subnet.
        Generally this needs to be a unique Neutron-allocated IP
        address, because the subnet's underlying L2 domain is bridged
        across multiple compute hosts and network nodes, and for HA
        there may be multiple DHCP agents running on that same bridged
        L2 domain.

        However, if the DHCP ports - on multiple compute/network nodes
        but for the same network - are _not_ bridged to each other,
        they do not need each to have a unique IP address.  Instead
        they can all share the same address from the relevant subnet.
        This works, without creating any ambiguity, because those
        ports are not all present on the same L2 domain, and because
        no data within the network is ever sent to that address.
        (DHCP requests are broadcast, and it is the network's job to
        ensure that such a broadcast will reach at least one of the
        available DHCP servers.  DHCP responses will be sent _from_
        the DHCP port address.)

        Specifically, for networking backends where it makes sense,
        the DHCP agent allows all DHCP ports to use the subnet's
        gateway IP address, and thereby to completely avoid any unique
        IP address allocation.  This behaviour is selected by running
        the DHCP agent with a configured interface driver whose
        'use_gateway_ips' property is True.

        When an operator deploys Neutron with an interface driver that
        makes use_gateway_ips True, they should also ensure that a
        gateway IP address is defined for each DHCP-enabled subnet,
        and that the gateway IP address doesn't change during the
        subnet's lifetime.
        """
        return False
