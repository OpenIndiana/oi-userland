# vim: tabstop=4 shiftwidth=4 softtabstop=4

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
# @author: Girish Moodalbail, Oracle, Inc.
#

import sqlalchemy as sa
from sqlalchemy.ext import declarative
from sqlalchemy import orm

from oslo.config import cfg

from quantum.context import ContextBase
from quantum.db import model_base


EVS_DB_BASE = declarative.declarative_base(cls=model_base.QuantumBaseV2)
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
        sql_connection = cfg.CONF.DATABASE.sql_connection
        if not sql_connection:
            sql_connection = 'sqlite:////var/lib/quantum/quantum.sqlite'
        EVS_DB_ENGINE = sa.create_engine(sql_connection, echo=True)
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
    """Overrides the Quantum DB session with EVS DB session"""

    evs_context = EVSContext.from_dict(context.to_dict())
    evs_context.session = get_session()

    return evs_context
