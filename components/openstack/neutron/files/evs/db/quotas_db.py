# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2011 OpenStack Foundation.
# All Rights Reserved.
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
# @author: Girish Moodalbail, Oracle, Inc.
#

import sqlalchemy as sa

from quantum.db import quota_db
from quantum.openstack.common import uuidutils
from quantum.plugins.evs.db import api as evs_db


class Quota(evs_db.EVS_DB_BASE):
    """Represent a single quota override for a tenant.

    If there is no row for a given tenant id and resource, then the
    default for the quota class is used.
    """

    id = sa.Column(sa.String(36), primary_key=True,
                   default=uuidutils.generate_uuid)
    tenant_id = sa.Column(sa.String(255), index=True)
    resource = sa.Column(sa.String(255))
    limit = sa.Column(sa.Integer)


class EVSDbQuotaDriver(quota_db.DbQuotaDriver):
    """
    Driver to perform necessary checks to enforce quotas and obtain
    quota information.  The default driver utilizes the local
    database.
    """

    @staticmethod
    def get_tenant_quotas(context, resources, tenant_id):
        """
        Given a list of resources, retrieve the quotas for the given
        tenant.

        :param context: The request context, for access checks.
        :param resources: A dictionary of the registered resource keys.
        :param tenant_id: The ID of the tenant to return quotas for.
        :return dict: from resource name to dict of name and limit
        """

        return quota_db.DbQuotaDriver().\
            get_tenant_quotas(evs_db.get_evs_context(context), resources,
                              tenant_id)

    @staticmethod
    def delete_tenant_quota(context, tenant_id):
        """Delete the quota entries for a given tenant_id.

        Atfer deletion, this tenant will use default quota values in conf.
        """

        quota_db.DbQuotaDriver().\
            delete_tenant_quota(evs_db.get_evs_context(context), tenant_id)

    @staticmethod
    def get_all_quotas(context, resources):
        """
        Given a list of resources, retrieve the quotas for the all
        tenants.

        :param context: The request context, for access checks.
        :param resources: A dictionary of the registered resource keys.
        :return quotas: list of dict of tenant_id:, resourcekey1:
        resourcekey2: ...
        """

        return quota_db.DbQuotaDriver().\
            get_all_quotas(evs_db.get_evs_context(context), resources)

    @staticmethod
    def update_quota_limit(context, tenant_id, resource, limit):
        quota_db.DbQuotaDriver().\
            update_quota_limit(evs_db.get_evs_context(context), tenant_id,
                               resource, limit)

    def limit_check(self, context, tenant_id, resources, values):
        """Check simple quota limits.

        For limits--those quotas for which there is no usage
        synchronization function--this method checks that a set of
        proposed values are permitted by the limit restriction.

        This method will raise a QuotaResourceUnknown exception if a
        given resource is unknown or if it is not a simple limit
        resource.

        If any of the proposed values is over the defined quota, an
        OverQuota exception will be raised with the sorted list of the
        resources which are too high.  Otherwise, the method returns
        nothing.

        :param context: The request context, for access checks.
        :param tenant_id: The tenant_id to check the quota.
        :param resources: A dictionary of the registered resources.
        :param values: A dictionary of the values to check against the
                       quota.
        """

        super(EVSDbQuotaDriver, self).\
            limit_check(evs_db.get_evs_context(context), tenant_id, resources,
                        values)
