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

from django.conf import settings
from django.utils.translation import ugettext_lazy as _

from horizon import exceptions
from horizon import forms
from horizon import workflows

from openstack_dashboard import api
from openstack_dashboard.dashboards.admin.instances.forms import \
    LiveMigrateForm
from openstack_dashboard.dashboards.admin.instances.tables import \
    AdminInstancesTable, MigrateInstance
from openstack_dashboard.dashboards.project.images.images.tables import \
    ImagesTable, CreateVolumeFromImage
from openstack_dashboard.dashboards.project.instances import tables \
    as project_tables
from openstack_dashboard.dashboards.project.instances.tables import \
    InstancesTable, TogglePause
from openstack_dashboard.dashboards.project.instances.workflows import \
    create_instance, update_instance


# Bootargs feature:
# Add bootargs feature to 'SetAdvanced' workflow action.
# Part of Project/Compute/Instances/Launch Instance
class SolarisSetAdvancedAction(create_instance.SetAdvancedAction):
    if getattr(settings, 'SOLARIS_BOOTARGS', True):
        boot_options = forms.CharField(
            label=_("Instance Boot Options"), required=False, max_length=255,
            help_text=_("Solaris kernel(8) and boot(8) options."))

        bootargs_persist = forms.BooleanField(
            label=_("Make Instance Boot Options Persistent"),
            required=False,
            help_text=_("Instance Boot Options are retained and used for each "
                        "subsequent boot."))

    def __init__(self, request, context, *args, **kwargs):
        super(SolarisSetAdvancedAction, self).__init__(request, context,
                                                       *args, **kwargs)
        try:
            if context.get('workflow_slug') != 'launch_instance' and \
                    getattr(settings, 'SOLARIS_BOOTARGS', True):
                self.fields.pop('boot_options', None)
                self.fields.pop('bootargs_persist', None)
            self.fields.pop('disk_config', None)
            self.fields.pop('config_drive', None)
        except Exception:
            exceptions.handle(request, _('Unable to retrieve extensions '
                                         'information.'))

    class Meta(object):
        name = _("Advanced Options")
        help_text_template = ("project/instances/"
                              "_launch_advanced_help.html")

# Bootargs feature:
# If locally configured to do so add bootargs metadata vars
# to Project/Compute/Instances/Launch Instance/Advanced Options
if getattr(settings, 'SOLARIS_BOOTARGS', True):
    create_instance.SetAdvanced.action_class = SolarisSetAdvancedAction
    create_instance.SetAdvanced.contributes += (
        'boot_options', 'bootargs_persist',
    )

# Remove 'PostCreationStep', 'SetAdvanced' from
# Project/Compute/Instances/Launch Instance
create_instance.LaunchInstance.default_steps = (
    create_instance.SelectProjectUser,
    create_instance.SetInstanceDetails,
    create_instance.SetAccessControls,
    create_instance.SetNetwork
)

# Bootargs feature:
# if locally configured to do so add back 'SetAdvanced'
# to Project/Compute/Instances/Launch Instance
if getattr(settings, 'SOLARIS_BOOTARGS', True):
    create_instance.LaunchInstance.default_steps += (
        create_instance.SetAdvanced,
    )


# Bootargs feature:
# Add bootargs feature to 'UpdateInstance' workflow action class.
# Part of Project/Compute/Instances/Actions/Edit Instance
class UpdateInstanceBootargAction(workflows.Action):
    bootargs = forms.CharField(
        label=_("Instance Boot Options"), required=False, max_length=255,
        help_text=_("Solaris kernel(8) and boot(8) options."))

    bootargs_persist = forms.BooleanField(
        label=_("Make Instance Boot Options Persistent"),
        required=False,
        help_text=_("Instance Boot Options are retained and used for each "
                    "subsequent boot."))

    def handle(self, request, data):
        if data is None:
            return True
        metadata = {'bootargs': data['bootargs'].strip()}
        if metadata['bootargs']:
            metadata['bootargs_persist'] = str(data['bootargs_persist'])
        else:
            metadata['bootargs_persist'] = "False"
        try:
            api.nova.server_set_meta(request,
                                     data['instance_id'],
                                     metadata)
        except Exception:
            exceptions.handle(request, ignore=True)
            return False
        return True

    class Meta(object):
        name = _("Instance Boot Options")
        slug = 'instance_bootargs'
        help_text = _("Edit Instance Boot Options.")


# Bootargs feature:
# Add bootargs To the action class for UpdateInstance
# contained in Project/Compute/Instances/Actions/Edit Instance
class UpdateInstanceBootarg(workflows.Step):
    action_class = UpdateInstanceBootargAction
    depends_on = ("instance_id",)
    contributes = ("bootargs", "bootargs_persist",)


# Bootargs feature:
# if locally configured to do so add UpdateInstanceBootarg
# to Project/Compute/Instances/Actions/Edit Instance
if getattr(settings, 'SOLARIS_BOOTARGS', True):
    update_instance.UpdateInstance.default_steps += (
        UpdateInstanceBootarg,
    )

# Remove 'TogglePause', 'MigrateInstance' actions from
# Admin/System/Instances/Actions
temp = list(AdminInstancesTable._meta.row_actions)
temp.remove(MigrateInstance)
temp.remove(TogglePause)
AdminInstancesTable._meta.row_actions = tuple(temp)

# Remove 'TogglePause' action from Project/Compute/Instances/Actions
temp = list(InstancesTable._meta.row_actions)
temp.remove(TogglePause)
InstancesTable._meta.row_actions = tuple(temp)

# Set the available states for Create Snapshot to only be 'ACTIVE'
project_tables.SNAPSHOT_READY_STATES = ('ACTIVE',)

# Disable 'disk_over_commit', 'block_migration' in
# Admin/System/Instances/Actions/Live Migrate Instance. Note that this is
# unchecked by default.
LiveMigrateForm.base_fields['disk_over_commit'].widget.attrs['disabled'] = True
LiveMigrateForm.base_fields['block_migration'].widget.attrs['disabled'] = True

# Remove 'CreateVolumeFromImage' checkbox from Project/Compute/Images/Actions
temp = list(ImagesTable._meta.row_actions)
temp.remove(CreateVolumeFromImage)
ImagesTable._meta.row_actions = tuple(temp)
