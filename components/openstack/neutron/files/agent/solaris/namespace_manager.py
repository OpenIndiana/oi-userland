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


class NamespaceManager(object):
    ''' Re-implements neutron.agent.l3.namespace_manager'''

    def __init__(self, *args, **kwargs):
        pass

    def __enter__(self):
        return self

    def __exit__(self, exc_type, value, traceback):
        if exc_type:
            # An exception occurred in the caller's with statement
            return False
        return True

    def keep_router(self, router_id):
        pass

    def keep_ext_net(self, ext_net_id):
        pass

    def get_prefix_and_id(self, ns_name):
        return None

    def is_managed(self, ns_name):
        return False

    def list_all(self):
        return set()

    def ensure_router_cleanup(self, router_id):
        pass

    def _cleanup(self, ns_prefix, ns_id):
        pass
