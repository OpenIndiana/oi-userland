# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
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

from openstack_dashboard.dashboards.admin.instances.forms import \
    LiveMigrateForm
from openstack_dashboard.dashboards.admin.instances import tables \
    as admin_tables
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
from openstack_dashboard.dashboards.project.images.images.tables import \
    EditImage, DeleteImage, ImagesTable, LaunchImage
from openstack_dashboard.dashboards.project.instances import tables \
    as project_tables
from openstack_dashboard.dashboards.project.instances.workflows import \
    create_instance, update_instance
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

# Remove 'PostCreationStep', 'SetAdvanced' from
# Project/Compute/Instances/Launch Instance
create_instance.LaunchInstance.default_steps = (
    create_instance.SelectProjectUser,
    create_instance.SetInstanceDetails,
    create_instance.SetAccessControls,
    create_instance.SetNetwork
)

# Disable 'Security Groups' in Project/Instances/Launch Instance/Access &
# Security. Note that this is unchecked by default.
groups_widget = create_instance.SetAccessControlsAction.base_fields['groups']
groups_widget.widget.attrs['disabled'] = True

# Remove 'UpdateInstanceSecurityGroups' from
# Project/Compute/Instances/Actions/Edit Instance
update_instance.UpdateInstance.default_steps = (
    update_instance.UpdateInstanceInfo,
)

# Remove 'SecurityGroupsTab' tab from Project/Compute/Access & Security
AccessAndSecurityTabs.tabs = (KeypairsTab, FloatingIPsTab, APIAccessTab)

# Remove 'TogglePause', 'MigrateInstance' actions from
# Admin/System/Instances/Actions
admin_tables.AdminInstancesTable._meta.row_actions = (
    project_tables.ConfirmResize,
    project_tables.RevertResize,
    admin_tables.AdminEditInstance,
    project_tables.ConsoleLink,
    project_tables.LogLink,
    project_tables.CreateSnapshot,
    project_tables.ToggleSuspend,
    admin_tables.LiveMigrateInstance,
    project_tables.SoftRebootInstance,
    project_tables.RebootInstance,
    project_tables.TerminateInstance
)

# Remove 'EditInstanceSecurityGroups', 'TogglePause' actions from
# Project/Compute/Instances/Actions
project_tables.InstancesTable._meta.row_actions = (
    project_tables.StartInstance,
    project_tables.ConfirmResize,
    project_tables.RevertResize,
    project_tables.CreateSnapshot,
    project_tables.SimpleAssociateIP,
    project_tables.AssociateIP,
    project_tables.SimpleDisassociateIP,
    project_tables.EditInstance,
    project_tables.DecryptInstancePassword,
    project_tables.ConsoleLink,
    project_tables.LogLink,
    project_tables.ResizeLink,
    project_tables.ToggleSuspend,
    project_tables.SoftRebootInstance,
    project_tables.RebootInstance,
    project_tables.StopInstance,
    project_tables.RebuildInstance,
    project_tables.TerminateInstance
)

# Disable 'disk_over_commit', 'block_migration' in
# Admin/System/Instances/Actions/Live Migrate Instance. Note that this is
# unchecked by default.
LiveMigrateForm.base_fields['disk_over_commit'].widget.attrs['disabled'] = True
LiveMigrateForm.base_fields['block_migration'].widget.attrs['disabled'] = True

# Disable 'admin_state' in Admin/System/Networks/Create Network
admin_state = CreateNetwork.base_fields['admin_state']
admin_state.widget.attrs['disabled'] = True
admin_state.widget.value_from_datadict = lambda *args: True

# Disable 'shared' in Admin/System/Networks/Create Network. Note that this is
# unchecked by default.
CreateNetwork.base_fields['shared'].widget.attrs['disabled'] = True

# Disable 'admin_state' in Admin/System/Networks/Network Name/Create Port
admin_state = CreatePort.base_fields['admin_state']
admin_state.widget.attrs['disabled'] = True
admin_state.widget.value_from_datadict = lambda *args: True

# Remove 'UpdatePort' action from Admin/System/Networks/Network Name/Actions
PortsTable._meta.row_actions = (DeletePort,)

# Remove 'UpdateSubnet' action from
# Admin/System/Networks/Network Name/Subnets/Actions
SubnetsTable._meta.row_actions = (DeleteSubnet,)

# Remove the 'EditNetwork' action from Admin/System/Networks/Actions
NetworksTable._meta.row_actions = (DeleteNetwork,)

# Remove the 'UpdatePort' action from
# Project/Network/Networks/Name/Ports/Actions
projectPortsTable._meta.row_actions = ()

# Remove the 'UpdateSubnet' action from
# Project/Network/Networks/Name/Subnets/Actions
projectSubnetsTable._meta.row_actions = (projectDeleteSubnet,)

# Remove the 'EditNetwork' action from Project/Network/Networks/Actions
projectNetworksTable._meta.row_actions = (projectCreateSubnet,
                                          projectDeleteNetwork)

# Disable 'admin_state' in Project/Network/Networks/Create Network/Network
admin_state = CreateNetworkInfoAction.base_fields['admin_state']
admin_state.widget.attrs['disabled'] = True
admin_state.widget.value_from_datadict = lambda *args: True

# Remove 'CreateVolumeFromImage' checkbox from Project/Compute/Images/Actions
ImagesTable._meta.row_actions = (LaunchImage, EditImage, DeleteImage,)

# Change 'host_routes' field to read-only in
# Project/Network/Networks/Create Network/Subnet Detail
base_fields = CreateSubnetDetailAction.base_fields
base_fields['host_routes'].widget.attrs['readonly'] = 'readonly'
