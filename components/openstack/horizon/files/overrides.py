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
from django.conf.urls import patterns
from django.conf.urls import url
from django.core.urlresolvers import reverse_lazy
from django.utils.translation import ugettext_lazy as _

from horizon import exceptions
from horizon import forms
from horizon import workflows

from openstack_dashboard import api
from openstack_dashboard.dashboards.admin.flavors import \
    urls as flavor_urls, views as flavor_views, workflows as flavor_workflows
from openstack_dashboard.dashboards.admin.flavors.views import INDEX_URL
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

SOLARIS_ZONE_TYPE_CHOICES = (('solaris-kz', 'Solaris Kernel Zone'),
                             ('solaris', 'Solaris Non-Global Zone'))
SOLARIS_ZONE_TYPE_DEFAULT = SOLARIS_ZONE_TYPE_CHOICES[0][0]


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


# Solaris brand type feature.
# Override CreateFlavorInfoAction adding Solaris Zone Brand drop down
# if SOLARIS_BRANDTYPE is set to True
class SolarisCreateFlavorInfoAction(flavor_workflows.CreateFlavorInfoAction):
    if getattr(settings, 'SOLARIS_BRANDTYPE', True):
        zone_brand = forms.ChoiceField(label=_("Solaris Zone Brand"),
                                       required=True,
                                       choices=SOLARIS_ZONE_TYPE_CHOICES)

    class Meta(object):
        name = _("Flavor Information")
        help_text = _("Flavors define the sizes for RAM, disk, number of "
                      "cores, and other resources and can be selected when "
                      "users deploy instances.")


# Solaris brand type feature.
# Override UpdateFlavorInfoAction adding Solaris Zone Brand drop down
# if SOLARIS_BRANDTYPE is set to True
class SolarisUpdateFlavorInfoAction(flavor_workflows.UpdateFlavorInfoAction):
    if getattr(settings, 'SOLARIS_BRANDTYPE', True):
        zone_brand = forms.ChoiceField(label=_("Solaris Zone Brand"),
                                       required=True,
                                       choices=SOLARIS_ZONE_TYPE_CHOICES)

    class Meta(object):
        name = _("Flavor Information")
        slug = 'update_info'
        help_text = _("Edit the flavor details. Flavors define the sizes for "
                      "RAM, disk, number of cores, and other resources. "
                      "Flavors are selected when users deploy instances.")


# Solaris brand type feature.
# Override CreateFlavor ensuring brand type metadata is saved to flavor
class SolarisCreateFlavor(flavor_workflows.CreateFlavor):
    def handle(self, request, data):
        flavor_id = data.get('flavor_id') or 'auto'
        swap = data.get('swap_mb') or 0
        ephemeral = data.get('eph_gb') or 0
        flavor_access = data['flavor_access']
        is_public = not flavor_access
        rxtx_factor = data.get('rxtx_factor') or 1
        zone_brand = data.get('zone_brand')
        metadata = {'zonecfg:brand': zone_brand}

        # Create the flavor
        try:
            self.object = api.nova.flavor_create(request,
                                                 name=data['name'],
                                                 memory=data['memory_mb'],
                                                 vcpu=data['vcpus'],
                                                 disk=data['disk_gb'],
                                                 ephemeral=ephemeral,
                                                 swap=swap,
                                                 flavorid=flavor_id,
                                                 is_public=is_public,
                                                 rxtx_factor=rxtx_factor,
                                                 metadata=metadata)
        except Exception:
            exceptions.handle(request, _('Unable to create flavor.'))
            return False

        # Update flavor access if the new flavor is not public
        flavor_id = self.object.id
        for project in flavor_access:
            try:
                api.nova.add_tenant_to_flavor(
                    request, flavor_id, project)
            except Exception:
                exceptions.handle(
                    request,
                    _('Unable to set flavor access for project %s.') % project)
        return True


# Solaris brand type feature.
# Override UpdateFlavor ensuring brand type metadata is saved to flavor
class SolarisUpdateFlavor(flavor_workflows.UpdateFlavor):
    def handle(self, request, data):
        flavor_projects = data["flavor_access"]
        is_public = not flavor_projects

        # Update flavor information
        try:
            flavor_id = data['flavor_id']
            # Grab any existing extra specs, because flavor edit is currently
            # implemented as a delete followed by a create.
            extras_dict = api.nova.flavor_get_extras(self.request,
                                                     flavor_id,
                                                     raw=True)
            extras_dict['zonecfg:brand'] = data['zone_brand']
            # Mark the existing flavor as deleted.
            api.nova.flavor_delete(request, flavor_id)
            # Then create a new flavor with the same name but a new ID.
            # This is in the same try/except block as the delete call
            # because if the delete fails the API will error out because
            # active flavors can't have the same name.
            flavor = api.nova.flavor_create(request,
                                            data['name'],
                                            data['memory_mb'],
                                            data['vcpus'],
                                            data['disk_gb'],
                                            ephemeral=data['eph_gb'],
                                            swap=data['swap_mb'],
                                            is_public=is_public,
                                            rxtx_factor=data['rxtx_factor'])
            if (extras_dict):
                api.nova.flavor_extra_set(request, flavor.id, extras_dict)
        except Exception:
            exceptions.handle(request, ignore=True)
            return False

        # Add flavor access if the flavor is not public.
        for project in flavor_projects:
            try:
                api.nova.add_tenant_to_flavor(request, flavor.id, project)
            except Exception:
                exceptions.handle(request, _('Modified flavor information, '
                                             'but unable to modify flavor '
                                             'access.'))
        return True


# Solaris brand type feature.
# Override UpdateView ensuring brand type metadata is retrieved from flavor
class SolarisUpdateView(flavor_views.UpdateView):
    def get_initial(self):
        flavor_id = self.kwargs['id']

        try:
            # Get initial flavor information
            flavor = api.nova.flavor_get(self.request, flavor_id,
                                         get_extras=True)
        except Exception:
            exceptions.handle(self.request,
                              _('Unable to retrieve flavor details.'),
                              redirect=reverse_lazy(INDEX_URL))

        if "zonecfg:brand" not in flavor.extras:
            zone_brand = SOLARIS_ZONE_TYPE_DEFAULT
        else:
            zone_brand = flavor.extras['zonecfg:brand']

        return {'flavor_id': flavor.id,
                'name': flavor.name,
                'vcpus': flavor.vcpus,
                'memory_mb': flavor.ram,
                'disk_gb': flavor.disk,
                'swap_mb': flavor.swap or 0,
                'rxtx_factor': flavor.rxtx_factor or 1,
                'eph_gb': getattr(flavor, 'OS-FLV-EXT-DATA:ephemeral', None),
                'zone_brand': zone_brand}


# Solaris brand type feature.
# Various overrides only peformed if SOLARIS_BRANDTYPE is set to True
if getattr(settings, 'SOLARIS_BRANDTYPE', True):
    flavor_workflows.CreateFlavorInfo.action_class = \
        SolarisCreateFlavorInfoAction
    flavor_workflows.CreateFlavorInfo.contributes += ('zone_brand',)
    flavor_workflows.UpdateFlavorInfo.action_class = \
        SolarisUpdateFlavorInfoAction
    flavor_workflows.UpdateFlavorInfo.contributes += ('zone_brand',)
    flavor_views.CreateView.workflow_class = SolarisCreateFlavor
    flavor_views.UpdateView.workflow_class = SolarisUpdateFlavor
    flavor_urls.urlpatterns = patterns(
        'openstack_dashboard.dashboards.admin.flavors.views',
        url(r'^$', flavor_views.IndexView.as_view(), name='index'),
        url(r'^create/$', flavor_views.CreateView.as_view(), name='create'),
        url(r'^(?P<id>[^/]+)/update/$', SolarisUpdateView.as_view(),
            name='update'),
    )
