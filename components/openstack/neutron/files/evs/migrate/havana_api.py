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

import ConfigParser

from sqlalchemy.ext import declarative
from sqlalchemy import orm
import sqlalchemy as sa

from neutron.context import ContextBase
from neutron.db import model_base
from neutron.openstack.common import uuidutils

EVS_DB_BASE = declarative.declarative_base(cls=model_base.NeutronBaseV2)
EVS_DB_ENGINE = None
EVS_DB_MAKER = None


class EVSContext(ContextBase):
    @property
    def session(self):
        return self._session

    @session.setter
    def session(self, session):
        self._session = session


def configure_db():
    global EVS_DB_ENGINE
    if not EVS_DB_ENGINE:
        config = ConfigParser.RawConfigParser()
        config.readfp(open("/etc/neutron/neutron.conf"))
        if config.has_option("database", 'connection'):
            sql_connection = config.get("database", 'connection')
        else:
            sql_connection = 'sqlite:////var/lib/neutron/neutron.sqlite'
        EVS_DB_ENGINE = sa.create_engine(sql_connection, echo=False)
        EVS_DB_BASE.metadata.create_all(EVS_DB_ENGINE)


def get_session(autocommit=True, expire_on_commit=False):
    global EVS_DB_ENGINE, EVS_DB_MAKER
    assert EVS_DB_ENGINE
    if not EVS_DB_MAKER:
        EVS_DB_MAKER = orm.sessionmaker(bind=EVS_DB_ENGINE,
                                        autocommit=autocommit,
                                        expire_on_commit=expire_on_commit)
    return EVS_DB_MAKER()


def get_evs_context(context):
    """Overrides the Neutron DB session with EVS DB session"""

    evs_context = EVSContext.from_dict(context.to_dict())
    evs_context.session = get_session()

    return evs_context


class Router(EVS_DB_BASE):
    """Represents a v2 neutron router."""

    id = sa.Column(sa.String(36), primary_key=True,
                   default=uuidutils.generate_uuid)
    name = sa.Column(sa.String(255))
    status = sa.Column(sa.String(16))
    admin_state_up = sa.Column(sa.Boolean)
    tenant_id = sa.Column(sa.String(255))
    gw_port_id = sa.Column(sa.String(36))
    gw_port_network_id = sa.Column(sa.String(36))


class FloatingIP(EVS_DB_BASE):
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
