# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
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

from neutron.common import utils

OPTS = []


class PrefixDelegation(object):
    def __init__(self, *args, **kwargs):
        pass

    @utils.synchronized("l3-agent-pd")
    def enable_subnet(self, router_id, subnet_id, prefix, ri_ifname, mac):
        return

    @utils.synchronized("l3-agent-pd")
    def disable_subnet(self, router_id, subnet_id):
        pass

    @utils.synchronized("l3-agent-pd")
    def update_subnet(self, router_id, subnet_id, prefix):
        pass

    @utils.synchronized("l3-agent-pd")
    def add_gw_interface(self, router_id, gw_ifname):
        pass

    @utils.synchronized("l3-agent-pd")
    def delete_router_pd(self, router):
        pass

    @utils.synchronized("l3-agent-pd")
    def remove_gw_interface(self, router_id):
        pass

    @utils.synchronized("l3-agent-pd")
    def sync_router(self, router_id):
        pass

    @utils.synchronized("l3-agent-pd")
    def remove_stale_ri_ifname(self, router_id, stale_ifname):
        pass

    @utils.synchronized("l3-agent-pd")
    def process_prefix_update(self):
        pass

    def after_start(self):
        pass


@utils.synchronized("l3-agent-pd")
def remove_router(resource, event, l3_agent, **kwargs):
    pass


def get_router_entry(ns_name):
    return {'gw_interface': None,
            'ns_name': None,
            'subnets': {}}


@utils.synchronized("l3-agent-pd")
def add_router(resource, event, l3_agent, **kwargs):
    pass
