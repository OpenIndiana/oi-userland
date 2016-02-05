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
# This script updates the schema for networks, subnets and agents table.
# This is needed since we do not run Juno to Kilo alembic migrations.
#

from alembic.migration import MigrationContext
from alembic.operations import Operations
import ConfigParser
import sqlalchemy as sa


def main():
    print "Start Kilo migrations."
    print "Add new parameters to networks, subnets and agents table."

    config = ConfigParser.RawConfigParser()
    config.readfp(open("/etc/neutron/neutron.conf"))
    if config.has_option("database", 'connection'):
        SQL_CONNECTION = config.get("database", 'connection')
        neutron_engine = sa.create_engine(SQL_CONNECTION)
        conn = neutron_engine.connect()
        ctx = MigrationContext.configure(conn)
        op = Operations(ctx)

        op.add_column('networks', sa.Column('mtu', sa.Integer(),
                      nullable=True))
        op.add_column('networks', sa.Column('vlan_transparent', sa.Boolean(),
                      nullable=True))
        op.add_column('agents', sa.Column('load', sa.Integer(),
                      server_default='0', nullable=False))
        op.add_column('subnets',
                      sa.Column('subnetpool_id',
                                sa.String(length=36),
                                nullable=True,
                                index=True))
    else:
        print "\nNo database connection found."

    print "\nEnd Migration."


if __name__ == '__main__':
    main()
