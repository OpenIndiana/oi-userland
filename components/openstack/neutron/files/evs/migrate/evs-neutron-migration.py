#!/usr/bin/python2.7
#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

#
# This script migrates the network, subnet and port information from EVS DB to
# neutron-server DB. It also re-creates routers and floatingips tables with
# Neutron's l3 schema. This script needs to be run for the proper upgrade of
# Neutron from Havana to Juno release.
#

import ConfigParser
import time

from oslo.config import cfg
from oslo.db import exception as excp
from oslo.db import options as db_options
import rad.bindings.com.oracle.solaris.rad.evscntl as evsc
import rad.connect as radcon
import sqlalchemy as sa
from sqlalchemy import MetaData, sql
from sqlalchemy.orm import sessionmaker
from sqlalchemy.schema import DropConstraint

from neutron import context as ctx
from neutron.db import common_db_mixin, model_base
from neutron.plugins.evs.migrate import havana_api 


def create_db_network(nw, engine, ext_ro):
    ''' Method for creating networks table in the neutron-server DB
        Input params:
        @nw - Dictionary with values from EVS DB
        @engine - SQL engine
        @ext_ro - External router
    '''
    # Importing locally because these modules end up importing neutron.wsgi
    # which causes RAD to hang
    from neutron.db import db_base_plugin_v2
    from neutron.db import external_net_db as ext_net
    model_base.BASEV2.metadata.bind = engine
    for _none in range(60):
        try:
            model_base.BASEV2.metadata.create_all(engine)
            break
        except sa.exc.OperationalError as err:
            # mysql is not ready. sleep for 2 more seconds
            time.sleep(2)
    else:
        print "Unable to connect to MySQL:  %s" % err
        print ("Please verify MySQL is properly configured and online "
               "before using svcadm(1M) to clear this service.")
        raise RuntimeError
    ctxt = ctx.get_admin_context()
    inst = db_base_plugin_v2.NeutronDbPluginV2()
    dup = False
    try:
        db_base_plugin_v2.NeutronDbPluginV2.create_network(inst, ctxt, nw)
        print "\nnetwork=%s added" % nw['network']['name']
        if ext_ro:
            ext_nw = ext_net.ExternalNetwork(network_id=nw['network']['id'])
            session = sessionmaker()
            session.configure(bind=engine)
            s = session()
            s.add(ext_nw)
            s.commit()
    except excp.DBDuplicateEntry:
        print "\nnetwork '%s' already exists" % nw['network']['name']
        dup = True
    return dup


def create_db_subnet(sub):
    ''' Method for creating subnets table in the neutron-server DB
        Input params:
        @sub - Dictionary with values from EVS DB
    '''
    # Importing locally because this module ends up importing neutron.wsgi
    # which causes RAD to hang
    from neutron.db import db_base_plugin_v2
    ctxt = ctx.get_admin_context()
    inst = db_base_plugin_v2.NeutronDbPluginV2()
    try:
        db_base_plugin_v2.NeutronDbPluginV2.create_subnet(inst, ctxt, sub)
        print "\nsubnet=%s added" % sub['subnet']['id']
    except excp.DBDuplicateEntry:
        print "\nsubnet '%s' already exists" % sub['subnet']['id']


def create_db_port(port):
    ''' Method for creating ports table in the neutron-server DB
        Input params:
        @port - Dictionary with values from EVS DB
    '''
    # Importing locally because this module ends up importing neutron.wsgi
    # which causes RAD to hang
    from neutron.db import db_base_plugin_v2
    ctxt = ctx.get_admin_context()
    inst = db_base_plugin_v2.NeutronDbPluginV2()
    try:
        db_base_plugin_v2.NeutronDbPluginV2.create_port(inst, ctxt, port)
        print "\nport=%s added" % port['port']['id']
    except excp.DBDuplicateEntry:
        print "\nport '%s' already exists" % port['port']['id']


def main():
    print "Start Migration."

    # Connect to EVS controller
    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/plugins/evs/evs_plugin.ini"))
    if config.has_option("EVS", 'evs_controller'):
        config_suh = config.get("EVS", 'evs_controller')
    else:
        config_suh = 'ssh://evsuser@localhost'
    suh = config_suh.split('://')
    if len(suh) != 2 or suh[0] != 'ssh' or not suh[1].strip():
        raise SystemExit(_("Specified evs_controller is invalid"))
    uh = suh[1].split('@')
    if len(uh) != 2 or not uh[0].strip() or not uh[1].strip():
        raise SystemExit(_("'user' and 'hostname' need to be specified "
                           "for evs_controller"))
    try:
        rc = radcon.connect_ssh(uh[1], user=uh[0])
    except:
        raise SystemExit(_("Cannot connect to EVS Controller"))
    try:
        evs_contr = rc.get_object(evsc.EVSController())
    except:
        raise SystemExit(_("Could not retrieve EVS info from EVS Controller"))
    evsinfo = evs_contr.getEVSInfo()
    if not evsinfo:
        raise SystemExit(_("No data to migrate"))

    config.readfp(open("/etc/neutron/neutron.conf"))
    if config.has_option("database", 'connection'):
        SQL_CONNECTION = config.get("database", 'connection')
    else:
        SQL_CONNECTION = 'sqlite:////var/lib/neutron/neutron.sqlite'

    conf = cfg.CONF
    db_options.set_defaults(cfg.CONF,
                            connection=SQL_CONNECTION,
                            sqlite_db='', max_pool_size=10,
                            max_overflow=20, pool_timeout=10)

    neutron_engine = sa.create_engine(SQL_CONNECTION)
    router_port_ids = {}

    for e in evsinfo:
        ext_ro = False
        for p in e.props:
            if p.name == 'OpenStack:router:external' and p.value == 'True':
                ext_ro = True
        # Populate networks table
        n = {
            'tenant_id': e.tenantname,
            'id': e.uuid,
            'name': e.name,
            'status': 'ACTIVE',
            'admin_state_up': True,
            'shared': False
            }
        nw = {'network': n}
        dup = create_db_network(nw, neutron_engine, ext_ro)
        if dup:
            continue  # No need to iterate over subnets and ports

        # Populate subnets table
        for i in e.ipnets:
            cidr = None
            gateway_ip = None
            enable_dhcp = None
            dns = []
            host = []
            start = []
            for p in i.props:
                if p.name == 'subnet':
                    cidr = p.value
                elif p.name == 'defrouter':
                    gateway_ip = p.value
                elif p.name == 'OpenStack:enable_dhcp':
                    enable_dhcp = p.value == 'True'
                elif p.name == 'OpenStack:dns_nameservers':
                    dns = p.value.split(',')
                elif p.name == 'OpenStack:host_routes':
                    hh = p.value.split(',')
                    for h in range(0, len(hh), 2):
                        d = {hh[h]: hh[h+1]}
                        host.append(d)
                elif p.name == 'pool':
                    ss = p.value.split(',')
                    for s in ss:
                        if '-' in s:
                            d = {'start': s.split('-')[0],
                                 'end': s.split('-')[1]}
                            start.append(d)
                        else:
                            d = {'start': s, 'end': s}
                            start.append(d)
            ip_version = 4 if i.ipvers == evsc.IPVersion.IPV4 else 6

            if i.name.startswith(i.uuid[:8]):
                # Skip autogenerated names
                name = None
            else:
                name = i.name
            s = {
                'tenant_id': i.tenantname,
                'id': i.uuid,
                'name': name,
                'network_id': e.uuid,
                'ip_version': ip_version,
                'cidr': cidr,
                'gateway_ip': gateway_ip,
                'enable_dhcp': enable_dhcp,
                'shared': False,
                'allocation_pools': start,
                'dns_nameservers': dns,
                'host_routes': host
                }

            sub = {'subnet': s}
            create_db_subnet(sub)

        # Populate ports table
        for j in e.vports:
            device_owner = ''
            device_id = ''
            mac_address = None
            ipaddr = None
            for v in j.props:
                if v.name == 'OpenStack:device_owner':
                    device_owner = v.value
                    if v.value in ('network:router_interface',
                                   'network:router_gateway'):
                        router_port_ids[j.uuid] = v.value
                elif v.name == 'OpenStack:device_id':
                    device_id = v.value
                elif v.name == 'macaddr':
                    mac_address = v.value
                elif v.name == 'ipaddr':
                    ipaddr = v.value.split('/')[0]
            if j.name.startswith(j.uuid[:8]):
                # Skip autogenerated names
                name = None
            else:
                name = j.name

            p = {
                'tenant_id': j.tenantname,
                'id': j.uuid,
                'name': name,
                'network_id': e.uuid,
                'mac_address': mac_address,
                'admin_state_up': True,
                'status': 'ACTIVE',
                'device_id': device_id,
                'device_owner': device_owner,
                'fixed_ips': [{'subnet_id': e.ipnets[0].uuid,
                               'ip_address': ipaddr}]
                }
            port = {'port': p}
            create_db_port(port)

    # Change the schema of the floatingips and routers tables by doing
    # the following:
    #     Fetch the floatingip, router entry using EVS API,
    #     Temporarily store the information,
    #     Delete floatingip, router entry,
    #     Remove floatingip, router as a constraint from existing tables,
    #     Drop the routers, floatingips table,
    #     Add router, floatingip entry using Neutron API

    # Importing locally because this module ends up importing neutron.wsgi
    # which causes RAD to hang
    from neutron.db import l3_db
    havana_api.configure_db()
    session = havana_api.get_session()

    # Fetch the floatingip entry using EVS API
    query = session.query(havana_api.FloatingIP)
    floatingips = query.all()
    fl = []
    if floatingips:
        for f in floatingips:
            fi = {
                'id': f['id'],
                'floating_ip_address': f['floating_ip_address'],
                'floating_network_id': f['floating_network_id'],
                'floating_port_id': f['floating_port_id'],
                'fixed_port_id': f['fixed_port_id'],
                'fixed_ip_address': f['fixed_ip_address'],
                'tenant_id': f['tenant_id'],
                'router_id': f['router_id'],
                }
            fl.append(fi)

        # Delete floatingip entry
        ctxt = ctx.get_admin_context()
        ctxt = havana_api.get_evs_context(ctxt)
        with ctxt.session.begin(subtransactions=True):
            cm_db_inst = common_db_mixin.CommonDbMixin()
            query = common_db_mixin.CommonDbMixin._model_query(cm_db_inst,
                                                               ctxt,
                                                               havana_api.
                                                               FloatingIP)
            for fip in query:
                ctxt.session.delete(fip)

    # Fetch the router entry using EVS API
    query = session.query(havana_api.Router)
    routers = []
    try:
        routers = query.all()
    except sa.exc.OperationalError:
        pass
    if routers:
        for r in routers:
            router_id = r['id']
            rt = {
                'tenant_id': r['tenant_id'],
                'id': r['id'],
                'name': r['name'],
                'admin_state_up': r['admin_state_up'],
                'gw_port_id': r['gw_port_id'],
                'status': 'ACTIVE'
                }

        # Delete router entry
        ctxt = ctx.get_admin_context()
        ctxt = havana_api.get_evs_context(ctxt)
        with ctxt.session.begin(subtransactions=True):
            cm_db_inst = common_db_mixin.CommonDbMixin()
            query = common_db_mixin.CommonDbMixin._model_query(cm_db_inst,
                                                               ctxt,
                                                               havana_api.
                                                               Router)
            router = query.filter(havana_api.Router.id == router_id).one()
            ctxt.session.delete(router)

    engine = sa.create_engine(SQL_CONNECTION)
    meta = MetaData()
    conn = engine.connect()
    trans = conn.begin()
    meta.reflect(engine)

    # Remove router as a constraint from existing tables,
    # Drop the routers table to remove old schema
    for t in meta.tables.values():
        for fk in t.foreign_keys:
            if fk.column.table.name == "routers":
                engine.execute(DropConstraint(fk.constraint))
    for t in meta.tables.values():
        if t.name == "routers":
            t.drop(bind=conn)

    # Remove floatingip as a constraint from existing tables,
    # Drop the floatingip table to remove old schema
    for t in meta.tables.values():
        for fk in t.foreign_keys:
            if fk.column.table.name == "floatingips":
                engine.execute(DropConstraint(fk.constraint))
    for t in meta.tables.values():
        if t.name == "floatingips":
            t.drop(bind=conn)
    conn.close()

    # Add the routers and floatingips using the schema in l3_db.py

    setattr(l3_db.Router, 'enable_snat', sa.Column(sa.Boolean,
            default=True, server_default=sql.true(), nullable=False))
    neutron_engine = sa.create_engine(SQL_CONNECTION)
    model_base.BASEV2.metadata.bind = neutron_engine
    model_base.BASEV2.metadata.create_all(neutron_engine)
    if routers:
        ctxt = ctx.get_admin_context()
        with ctxt.session.begin(subtransactions=True):
            router_db = l3_db.Router(id=router_id,
                                     tenant_id=r['tenant_id'],
                                     name=rt['name'],
                                     admin_state_up=rt['admin_state_up'],
                                     gw_port_id=rt['gw_port_id'],
                                     status="ACTIVE")
            ctxt.session.add(router_db)
            print "\nrouter=%s updated" % rt['name']
        with ctxt.session.begin(subtransactions=True):
            for i, j in router_port_ids.iteritems():
                router_port = l3_db.RouterPort(
                    port_id=i,
                    router_id=router_id,
                    port_type=j)
                ctxt.session.add(router_port)

    if floatingips:
        ctxt = ctx.get_admin_context()
        with ctxt.session.begin(subtransactions=True):
            for i in fl:
                fl_db = l3_db.FloatingIP(
                    id=i['id'],
                    floating_ip_address=i['floating_ip_address'],
                    floating_network_id=i['floating_network_id'],
                    floating_port_id=i['floating_port_id'],
                    fixed_port_id=i['fixed_port_id'],
                    fixed_ip_address=i['fixed_ip_address'],
                    router_id=i['router_id'],
                    tenant_id=i['tenant_id'])
                ctxt.session.add(fl_db)
                print "\nfloatingip=%s updated" % i['floating_ip_address']

    print "\nEnd Migration."


if __name__ == '__main__':
    main()
