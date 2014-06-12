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

"""
Solaris-specific customizations for Horizon
"""

from openstack_dashboard.dashboards.admin.networks.forms import CreateNetwork
from openstack_dashboard.dashboards.admin.networks.ports.forms import \
    CreatePort
from openstack_dashboard.dashboards.admin.networks.ports.tables import \
    DeletePort, PortsTable
from openstack_dashboard.dashboards.admin.networks.subnets.tables import \
    DeleteSubnet, SubnetsTable
from openstack_dashboard.dashboards.admin.networks.tables import \
    DeleteNetwork, NetworksTable
from openstack_dashboard.dashboards.project.access_and_security.tabs import \
    AccessAndSecurityTabs, APIAccessTab, FloatingIPsTab, KeypairsTab
from openstack_dashboard.dashboards.project.instances.tabs import \
    InstanceDetailTabs, LogTab, OverviewTab
from openstack_dashboard.dashboards.project.instances.workflows import \
    create_instance
from openstack_dashboard.dashboards.project.networks.ports.tables import \
    PortsTable as projectPortsTable
from openstack_dashboard.dashboards.project.networks.subnets.tables import \
    DeleteSubnet as projectDeleteSubnet
from openstack_dashboard.dashboards.project.networks.subnets.tables import \
    SubnetsTable as projectSubnetsTable
from openstack_dashboard.dashboards.project.networks.tables import \
    CreateSubnet as projectCreateSubnet
from openstack_dashboard.dashboards.project.networks.tables import \
    DeleteNetwork as projectDeleteNetwork
from openstack_dashboard.dashboards.project.networks.tables import \
    NetworksTable as projectNetworksTable
from openstack_dashboard.dashboards.project.networks.workflows import \
    CreateNetworkInfoAction, CreateSubnetDetailAction, CreateSubnetInfoAction

# remove VolumeOptions and PostCreationStep from LaunchInstance
create_instance.LaunchInstance.default_steps = \
    (create_instance.SelectProjectUser,
     create_instance.SetInstanceDetails,
     create_instance.SetAccessControls,
     create_instance.SetNetwork)

# Remove the Security Groups tab from Project/Access and Security
AccessAndSecurityTabs.tabs = (KeypairsTab, FloatingIPsTab, APIAccessTab)

# remove the 'Console' tab from Instance Detail
InstanceDetailTabs.tabs = (OverviewTab, LogTab)

# Disable 'admin_state' and 'shared' checkboxes on Create Networks
CreateNetwork.base_fields['admin_state'].widget.attrs['disabled'] = True
CreateNetwork.base_fields['shared'].widget.attrs['disabled'] = True

# Disable 'admin_state' checkbox on Create Port
CreatePort.base_fields['admin_state'].widget.attrs['disabled'] = True

# Remove the ability to Update Ports
PortsTable._meta.row_actions = (DeletePort,)

# Remove the ability to Update Subnets
SubnetsTable._meta.row_actions = (DeleteSubnet,)

# Remove the ability to Edit Networks
NetworksTable._meta.row_actions = (DeleteNetwork,)

# Remove the ability to Update project Ports
projectPortsTable._meta.row_actions = ()

# Remove the ability to Update project Subnets
projectSubnetsTable._meta.row_actions = (projectDeleteSubnet,)

# Remove the ability to Edit project Networks
projectNetworksTable._meta.row_actions = (projectCreateSubnet,
                                          projectDeleteNetwork)

# Disable 'admin_state' checkbox on Create project Networks
CreateNetworkInfoAction.base_fields['admin_state'].widget.attrs['disabled'] = \
    True

# Disable 'no_gateway' checkbox on Create project Networks
CreateSubnetInfoAction.base_fields['no_gateway'].widget.attrs['disabled'] = \
    True

# change 'allocation_pools' and 'host_routes' to readonly
base_fields = CreateSubnetDetailAction.base_fields
base_fields['allocation_pools'].widget.attrs['readonly'] = 'readonly'
base_fields['host_routes'].widget.attrs['readonly'] = 'readonly'
