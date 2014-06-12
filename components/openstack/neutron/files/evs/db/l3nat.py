# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2012 Nicira Networks, Inc.  All rights reserved.
#
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
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
# @author: Dan Wendlandt, Nicira, Inc
# @author: Girish Moodalbail, Oracle, Inc.
#

"""
Based off generic l3_agent (neutron/agent/l3_agent) code
"""

import sqlalchemy as sa

from neutron.api.v2 import attributes
from neutron.common import constants as l3_constants
from neutron.common import exceptions as q_exc
from neutron.db import l3_db
from neutron.extensions import l3
from neutron.extensions import external_net
from neutron.openstack.common import log as logging
from neutron.openstack.common import uuidutils
from neutron.plugins.evs.db import api as evs_db


LOG = logging.getLogger(__name__)

DEVICE_OWNER_ROUTER_INTF = l3_constants.DEVICE_OWNER_ROUTER_INTF
DEVICE_OWNER_ROUTER_GW = l3_constants.DEVICE_OWNER_ROUTER_GW
DEVICE_OWNER_FLOATINGIP = l3_constants.DEVICE_OWNER_FLOATINGIP


class Router(evs_db.EVS_DB_BASE):
    """Represents a v2 neutron router."""

    id = sa.Column(sa.String(36), primary_key=True,
                   default=uuidutils.generate_uuid)
    name = sa.Column(sa.String(255))
    status = sa.Column(sa.String(16))
    admin_state_up = sa.Column(sa.Boolean)
    tenant_id = sa.Column(sa.String(255))
    gw_port_id = sa.Column(sa.String(36))
    gw_port_network_id = sa.Column(sa.String(36))


class FloatingIP(evs_db.EVS_DB_BASE):
    """Represents a floating IP address.

    This IP address may or may not be allocated to a tenant, and may or
    may not be associated with an internal port/ip address/router.
    """

    id = sa.Column(sa.String(36), primary_key=True,
                   default=uuidutils.generate_uuid)
    floating_ip_address = sa.Column(sa.String(64), nullable=False)
    floating_network_id = sa.Column(sa.String(36), nullable=False)
    floating_port_id = sa.Column(sa.String(36), nullable=False)
    fixed_port_id = sa.Column(sa.String(36))
    fixed_ip_address = sa.Column(sa.String(64))
    router_id = sa.Column(sa.String(36), sa.ForeignKey('routers.id'))
    tenant_id = sa.Column(sa.String(255))


class EVS_L3_NAT_db_mixin(l3_db.L3_NAT_db_mixin):
    """Mixin class to add L3/NAT router methods"""

    Router = Router
    FloatingIP = FloatingIP

    def _make_router_dict(self, router, fields=None,
                          process_extensions=True):
        res = {'id': router['id'],
               'name': router['name'],
               'tenant_id': router['tenant_id'],
               'admin_state_up': router['admin_state_up'],
               'status': router['status'],
               'external_gateway_info': None,
               'gw_port_id': router['gw_port_id']}
        if router['gw_port_id']:
            nw_id = router['gw_port_network_id']
            res['external_gateway_info'] = {'network_id': nw_id}
        if process_extensions:
            self._apply_dict_extend_functions(
                l3.ROUTERS, res, router)
        return self._fields(res, fields)

    def create_router(self, context, router):
        return super(EVS_L3_NAT_db_mixin, self).\
            create_router(evs_db.get_evs_context(context), router)

    def update_router(self, context, id, router):
        return super(EVS_L3_NAT_db_mixin, self).\
            update_router(evs_db.get_evs_context(context), id, router)

    def _update_router_gw_info(self, context, router_id, info, router=None):
        """This method overrides the base class method and it's contents
        are exactly same as the base class method except that the Router
        DB columns are different for EVS and OVS"""

        router = router or self._get_router(context, router_id)
        gw_port_id = router['gw_port_id']
        # network_id attribute is required by API, so it must be present
        gw_port_network_id = router['gw_port_network_id']

        network_id = info.get('network_id', None) if info else None
        if network_id:
            self._get_network(context, network_id)
            if not self._network_is_external(context, network_id):
                msg = _("Network %s is not a valid external "
                        "network") % network_id
                raise q_exc.BadRequest(resource='router', msg=msg)

        # figure out if we need to delete existing port
        if gw_port_id and gw_port_network_id != network_id:
            fip_count = self.get_floatingips_count(context.elevated(),
                                                   {'router_id': [router_id]})
            if fip_count:
                raise l3.RouterExternalGatewayInUseByFloatingIp(
                    router_id=router_id, net_id=gw_port_network_id)
            with context.session.begin(subtransactions=True):
                router['gw_port_id'] = None
                router['gw_port_network_id'] = None
                context.session.add(router)
            self.delete_port(context.elevated(), gw_port_id,
                             l3_port_check=False)

        if network_id is not None and (gw_port_id is None or
                                       gw_port_network_id != network_id):
            subnets = self._get_subnets_by_network(context,
                                                   network_id)
            for subnet in subnets:
                self._check_for_dup_router_subnet(context, router_id,
                                                  network_id, subnet['id'],
                                                  subnet['cidr'])

            # Port has no 'tenant-id', as it is hidden from user
            gw_port = self._core_plugin.create_port(context.elevated(), {
                'port':
                {'tenant_id': '',  # intentionally not set
                 'network_id': network_id,
                 'mac_address': attributes.ATTR_NOT_SPECIFIED,
                 'fixed_ips': attributes.ATTR_NOT_SPECIFIED,
                 'device_id': router_id,
                 'device_owner': DEVICE_OWNER_ROUTER_GW,
                 'admin_state_up': True,
                 'name': ''}})

            if not gw_port['fixed_ips']:
                self._core_plugin.delete_port(context.elevated(),
                                              gw_port['id'],
                                              l3_port_check=False)
                msg = (_('No IPs available for external network %s') %
                       network_id)
                raise q_exc.BadRequest(resource='router', msg=msg)

            with context.session.begin(subtransactions=True):
                router['gw_port_id'] = gw_port['id']
                router['gw_port_network_id'] = gw_port['network_id']
                context.session.add(router)

    def delete_router(self, context, id):
        super(EVS_L3_NAT_db_mixin, self).\
            delete_router(evs_db.get_evs_context(context), id)

    def get_router(self, context, id, fields=None):
        return super(EVS_L3_NAT_db_mixin, self).\
            get_router(evs_db.get_evs_context(context), id, fields)

    def get_routers(self, context, filters=None, fields=None,
                    sorts=None, limit=None, marker=None, page_reverse=False):

        query = evs_db.get_session().query(self.Router)
        if filters is not None:
            for key, value in filters.iteritems():
                column = getattr(self.Router, key, None)
                if column:
                    query = query.filter(column.in_(value))

        routers = query.all()
        retlist = []
        for router in routers:
            retlist.append(self._make_router_dict(router, fields))
        return retlist

    def get_routers_count(self, context, filters=None):
        return len(self.get_routers(context, filters))

    def add_router_interface(self, context, router_id, interface_info):
        return super(EVS_L3_NAT_db_mixin, self).\
            add_router_interface(evs_db.get_evs_context(context),
                                 router_id, interface_info)

    def remove_router_interface(self, context, router_id, interface_info):
        return super(EVS_L3_NAT_db_mixin, self).\
            remove_router_interface(evs_db.get_evs_context(context),
                                    router_id, interface_info)

    def create_floatingip(self, context, floatingip):
        return super(EVS_L3_NAT_db_mixin, self).\
            create_floatingip(evs_db.get_evs_context(context), floatingip)

    def update_floatingip(self, context, id, floatingip):
        return super(EVS_L3_NAT_db_mixin, self).\
            update_floatingip(evs_db.get_evs_context(context), id, floatingip)

    def delete_floatingip(self, context, id):
        super(EVS_L3_NAT_db_mixin, self).\
            delete_floatingip(evs_db.get_evs_context(context), id)

    def get_floatingip(self, context, id, fields=None):
        return super(EVS_L3_NAT_db_mixin, self).\
            get_floatingip(evs_db.get_evs_context(context), id, fields)

    def get_floatingips(self, context, filters=None, fields=None,
                        sorts=None, limit=None, marker=None,
                        page_reverse=False):

        query = evs_db.get_session().query(self.FloatingIP)
        if filters:
            for key, value in filters.iteritems():
                column = getattr(self.FloatingIP, key, None)
                if column:
                    query = query.filter(column.in_(value))

        floatingips = query.all()
        retlist = []
        for floatingip in floatingips:
            retlist.append(self._make_floatingip_dict(floatingip, fields))
        return retlist

    def get_floatingips_count(self, context, filters=None):
        return len(self.get_floatingips(context, filters))

    def prevent_l3_port_deletion(self, context, port_id):
        """ Checks to make sure a port is allowed to be deleted, raising
        an exception if this is not the case.  This should be called by
        any plugin when the API requests the deletion of a port, since
        some ports for L3 are not intended to be deleted directly via a
        DELETE to /ports, but rather via other API calls that perform the
        proper deletion checks.
        """
        port = self.get_port(context, port_id)
        if port['device_owner'] in [DEVICE_OWNER_ROUTER_INTF,
                                    DEVICE_OWNER_ROUTER_GW,
                                    DEVICE_OWNER_FLOATINGIP]:
            raise l3.L3PortInUse(port_id=port_id,
                                 device_owner=port['device_owner'])

    def disassociate_floatingips(self, context, port_id):
        super(EVS_L3_NAT_db_mixin, self).\
            disassociate_floatingips(evs_db.get_evs_context(context), port_id)

    def get_sync_data(self, context, router_ids=None, active=None):
        return super(EVS_L3_NAT_db_mixin, self).\
            get_sync_data(evs_db.get_evs_context(context), router_ids, active)

    def _get_by_id(self, context, model, id):
        return context.session.query(model).\
            filter(model.id == id).one()

    def allow_l3_port_deletion(self, context, port_id):
        """ If an L3 agent is using this port, then we need to send
        a notification to L3 agent to release the port before we can
        delete the port"""
        pass
