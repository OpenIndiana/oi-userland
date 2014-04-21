# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2011 Justin Santa Barbara
# All Rights Reserved.
#
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
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
Driver for Solaris Zones (nee Containers):
"""

import glob
import os
import platform
import shutil
import tempfile
import uuid

import rad.bindings.com.oracle.solaris.rad.kstat as kstat
import rad.bindings.com.oracle.solaris.rad.zonesbridge as zonesbridge
import rad.bindings.com.oracle.solaris.rad.zonemgr as zonemgr
import rad.client
import rad.connect
from solaris_install.archive.checkpoints import InstantiateUnifiedArchive
from solaris_install.archive import LOGFILE as ARCHIVE_LOGFILE
from solaris_install.archive import UnifiedArchive
from solaris_install.engine import InstallEngine

from eventlet import greenthread
from lxml import etree
from oslo.config import cfg

from nova.compute import power_state
from nova.compute import task_states
from nova.compute import vm_mode
from nova import conductor
from nova import context as nova_context
from nova import exception
from nova.image import glance
from nova.network import quantumv2
from nova.openstack.common import fileutils
from nova.openstack.common import jsonutils
from nova.openstack.common import log as logging
from nova import paths
from nova import utils
from nova.virt import driver
from nova.virt import event as virtevent
from nova.virt import images
from nova.virt.solariszones import sysconfig
from nova import volume

solariszones_opts = [
    cfg.StrOpt('glancecache_dirname',
               default='$state_path/images',
               help='Default path to Glance cache for Solaris Zones.'),
    cfg.StrOpt('solariszones_snapshots_directory',
               default='$instances_path/snapshots',
               help='Location where solariszones driver will store snapshots '
                    'before uploading them to the Glance image service'),
]

CONF = cfg.CONF
CONF.register_opts(solariszones_opts)
LOG = logging.getLogger(__name__)

# These should match the strings returned by the zone_state_str()
# function in the (private) libzonecfg library. These values are in turn
# returned in the 'state' string of the Solaris Zones' RAD interface by
# the zonemgr(3RAD) provider.
ZONE_STATE_CONFIGURED = 'configured'
ZONE_STATE_INCOMPLETE = 'incomplete'
ZONE_STATE_UNAVAILABLE = 'unavailable'
ZONE_STATE_INSTALLED = 'installed'
ZONE_STATE_READY = 'ready'
ZONE_STATE_RUNNING = 'running'
ZONE_STATE_SHUTTING_DOWN = 'shutting_down'
ZONE_STATE_DOWN = 'down'
ZONE_STATE_MOUNTED = 'mounted'

# Mapping between zone state and Nova power_state.
SOLARISZONES_POWER_STATE = {
    ZONE_STATE_CONFIGURED:      power_state.NOSTATE,
    ZONE_STATE_INCOMPLETE:      power_state.BUILDING,
    ZONE_STATE_UNAVAILABLE:     power_state.NOSTATE,
    ZONE_STATE_INSTALLED:       power_state.SHUTDOWN,
    ZONE_STATE_READY:           power_state.RUNNING,
    ZONE_STATE_RUNNING:         power_state.RUNNING,
    ZONE_STATE_SHUTTING_DOWN:   power_state.RUNNING,
    ZONE_STATE_DOWN:            power_state.RUNNING,
    ZONE_STATE_MOUNTED:         power_state.NOSTATE
}

# Solaris Zones brands as defined in brands(5).
ZONE_BRAND_LABELED = 'labeled'
ZONE_BRAND_SOLARIS = 'solaris'
ZONE_BRAND_SOLARIS_KZ = 'solaris-kz'
ZONE_BRAND_SOLARIS10 = 'solaris10'

# Mapping between supported zone brands and the name of the corresponding
# brand template.
ZONE_BRAND_TEMPLATE = {
    ZONE_BRAND_SOLARIS:         'SYSdefault',
    ZONE_BRAND_SOLARIS_KZ:      'SYSsolaris-kz',
}

MAX_CONSOLE_BYTES = 102400


def lookup_resource_property(zone, resource, prop, filter=None):
    """Lookup specified property from specified Solaris Zone resource."""
    try:
        val = zone.getResourceProperties(zonemgr.Resource(resource, filter),
                                         [prop])
    except rad.client.ObjectError:
        return None
    except Exception:
        raise
    return val[0].value if val else None


def lookup_resource_property_value(zone, resource, prop, value):
    """Lookup specified property with value from specified Solaris Zone
       resource. Returns property if matching value is found, else None
    """
    try:
        resources = zone.getResources(zonemgr.Resource(resource))
        for resource in resources:
            for propertee in resource.properties:
                if propertee.name == prop and propertee.value == value:
                    return propertee
        else:
            return None
    except rad.client.ObjectError:
        return None
    except Exception:
        raise


class ZoneConfig(object):
    """ ZoneConfig - context manager for access zone configurations.
    Automatically opens the configuration for a zone and commits any changes
    before exiting
    """
    def __init__(self, zone):
        """ zone is a zonemgr object representing either a kernel zone or
        non-glboal zone.
        """
        self.zone = zone
        self.editing = False

    def __enter__(self):
        """ enables the editing of the zone.
        """
        try:
            self.zone.editConfig()
            self.editing = True
            return self
        except rad.client.ObjectError as err:
            LOG.error(_("Unable to initialize editing of instance '%s' via "
                        "zonemgr(3RAD): %s") % (self.zone.name, err))
            raise

    def __exit__(self, exc_type, exc_val, exc_tb):
        """ looks for any kind of exception before exiting.  If one is found,
        cancel any configuration changes and reraise the exception.  If not,
        commit the new configuration.
        """
        if exc_type is not None and self.editing:
            # We received some kind of exception.  Cancel the config and raise.
            self.zone.cancelConfig()
            raise
        else:
            # commit the config
            try:
                self.zone.commitConfig()
            except rad.client.ObjectError as err:
                LOG.error(_("Unable to commit the new configuration for "
                            "instance '%s' via zonemgr(3RAD): %s")
                          % (self.zone.name, err))
                raise

    def setprop(self, resource, prop, value):
        """ sets a property for an existing resource OR creates a new resource
        with the given property(s).
        """
        current = lookup_resource_property(self.zone, resource, prop)
        if current is not None and current == value:
            # the value is already set
            return

        try:
            if current is None:
                self.zone.addResource(zonemgr.Resource(
                    resource, [zonemgr.Property(prop, value)]))
            else:
                self.zone.setResourceProperties(
                    zonemgr.Resource(resource),
                    [zonemgr.Property(prop, value)])
        except rad.client.ObjectError as err:
            LOG.error(_("Unable to set '%s' property on '%s' resource for "
                        "instance '%s' via zonemgr(3RAD): %s")
                      % (prop, resource, self.zone.name, err))
            raise

    def addresource(self, resource, props=None):
        """ creates a new resource with an optional property list.
        """
        if props is None:
            props = []

        try:
            self.zone.addResource(zonemgr.Resource(resource, props))
        except rad.client.ObjectError as err:
            LOG.error(_("Unable to create new resource '%s' for instance '%s'"
                        "via zonemgr(3RAD): %s")
                      % (resource, self.zone.name, err))
            raise

    def removeresources(self, resource, props=None):
        """ removes resources whose properties include the optional property
            list specified in props.
        """
        if props is None:
            props = []

        try:
            self.zone.removeResources(zonemgr.Resource(resource, props))
        except rad.client.ObjectError as err:
            LOG.error(_("Unable to remove resource '%s' for instance '%s' via "
                        "zonemgr(3RAD): %s") % (resource, self.zone.name, err))
            raise


class SolarisZonesDriver(driver.ComputeDriver):
    """Solaris Zones Driver using the zonemgr(3RAD) and kstat(3RAD) providers.

    The interface to this class talks in terms of 'instances' (Amazon EC2 and
    internal Nova terminology), by which we mean 'running virtual machine'
    (XenAPI terminology) or domain (Xen or libvirt terminology).

    An instance has an ID, which is the identifier chosen by Nova to represent
    the instance further up the stack.  This is unfortunately also called a
    'name' elsewhere.  As far as this layer is concerned, 'instance ID' and
    'instance name' are synonyms.

    Note that the instance ID or name is not human-readable or
    customer-controlled -- it's an internal ID chosen by Nova.  At the
    nova.virt layer, instances do not have human-readable names at all -- such
    things are only known higher up the stack.

    Most virtualization platforms will also have their own identity schemes,
    to uniquely identify a VM or domain.  These IDs must stay internal to the
    platform-specific layer, and never escape the connection interface.  The
    platform-specific layer is responsible for keeping track of which instance
    ID maps to which platform-specific ID, and vice versa.

    Some methods here take an instance of nova.compute.service.Instance.  This
    is the data structure used by nova.compute to store details regarding an
    instance, and pass them into this layer.  This layer is responsible for
    translating that generic data structure into terms that are specific to the
    virtualization platform.

    """

    capabilities = {
        "has_imagecache": False,
        "supports_recreate": False,
    }

    def __init__(self, virtapi):
        self.virtapi = virtapi
        self._compute_event_callback = None
        self._conductor_api = conductor.API()
        self._host_stats = {}
        self._initiator = None
        self._install_engine = None
        self._pagesize = os.sysconf('SC_PAGESIZE')
        self._uname = os.uname()
        self._validated_archives = list()
        self._volume_api = volume.API()

    def _init_rad(self):
        """Connect to RAD providers for kernel statistics and Solaris
        Zones. By connecting to the local rad(1M) service through a
        UNIX domain socket, kernel statistics can be read via
        kstat(3RAD) and Solaris Zones can be configured and controlled
        via zonemgr(3RAD).
        """

        # TODO(dcomay): Arrange to call this in the event of losing the
        # connection to RAD.
        try:
            self._rad_instance = rad.connect.connect_unix()
            self._kstat_control = self._rad_instance.get_object(
                kstat.Control())
        except Exception as reason:
            msg = (_('Unable to connect to svc:/system/rad:local: %s')
                   % reason)
            raise exception.NovaException(msg)

    def init_host(self, host):
        """Initialize anything that is necessary for the driver to function,
        including catching up with currently running VM's on the given host."""
        # TODO(Vek): Need to pass context in for access to auth_token

        self._init_rad()

    def _get_iscsi_initiator(self):
        """ Return the iSCSI initiator node name IQN for this host """
        out, err = utils.execute('/usr/sbin/iscsiadm', 'list',
                                 'initiator-node')
        # Sample first line of command output:
        # Initiator node name: iqn.1986-03.com.sun:01:e00000000000.4f757217
        initiator_name_line = out.splitlines()[0]
        initiator_iqn = initiator_name_line.rsplit(' ', 1)[1]
        return initiator_iqn

    def _get_zone_by_name(self, name):
        """Return a Solaris Zones object via RAD by name."""
        try:
            zone = self._rad_instance.get_object(
                zonemgr.Zone(), rad.client.ADRGlobPattern({'name': name}))
        except rad.client.NotFoundError:
            return None
        except Exception:
            raise

        return zone

    def _get_state(self, zone):
        """Return the running state, one of the power_state codes."""
        return SOLARISZONES_POWER_STATE[zone.state]

    def _pages_to_kb(self, pages):
        """Convert a number of pages of memory into a total size in KBytes."""
        return (pages * self._pagesize) / 1024

    def _get_max_mem(self, zone):
        """Return the maximum memory in KBytes allowed."""
        max_mem = lookup_resource_property(zone, 'capped-memory', 'physical')
        if max_mem is not None:
            return utils.to_bytes(max_mem) / 1024

        # If physical property in capped-memory doesn't exist, this may
        # represent a non-global zone so just return the system's total
        # memory.
        return self._pages_to_kb(os.sysconf('SC_PHYS_PAGES'))

    def _get_mem(self, zone):
        """Return the memory in KBytes used by the domain."""

        # There isn't any way of determining this from the hypervisor
        # perspective in Solaris, so just return the _get_max_mem() value
        # for now.
        return self._get_max_mem(zone)

    def _get_num_cpu(self, zone):
        """Return the number of virtual CPUs for the domain.

        In the case of kernel zones, the number of virtual CPUs a zone
        ends up with depends on whether or not there were 'virtual-cpu'
        or 'dedicated-cpu' resources in the configuration or whether
        there was an assigned pool in the configuration. This algorithm
        attempts to emulate what the virtual platform code does to
        determine a number of virtual CPUs to use.
        """

        # If a 'virtual-cpu' resource exists, use the minimum number of
        # CPUs defined there.
        ncpus = lookup_resource_property(zone, 'virtual-cpu', 'ncpus')
        if ncpus is not None:
            min = ncpus.split('-', 1)[0]
            if min.isdigit():
                return int(min)

        # Otherwise if a 'dedicated-cpu' resource exists, use the maximum
        # number of CPUs defined there.
        ncpus = lookup_resource_property(zone, 'dedicated-cpu', 'ncpus')
        if ncpus is not None:
            max = ncpus.split('-', 1)[-1]
            if max.isdigit():
                return int(max)

        # Finally if neither resource exists but the zone was assigned a
        # pool in the configuration, the number of CPUs would be the size
        # of the processor set. Currently there's no way of easily
        # determining this so use the system's notion of the total number
        # of online CPUs.
        return os.sysconf('SC_NPROCESSORS_ONLN')

    def _get_kstat_by_name(self, kstat_class, module, instance, name):
        """Return Kstat snapshot data via RAD as a dictionary."""
        pattern = {
            'class':    kstat_class,
            'module':   module,
            'instance': instance,
            'name':     name
        }
        try:
            self._kstat_control.update()
            kstat_object = self._rad_instance.get_object(
                kstat.Kstat(), rad.client.ADRGlobPattern(pattern))
        except Exception as reason:
            LOG.warning(_("Unable to retrieve kstat object '%s:%s:%s' of "
                          "class '%s' via kstat(3RAD): %s")
                        % (module, instance, name, kstat_class, reason))
            return None

        kstat_data = {}
        for named in kstat_object.fresh_snapshot().data.NAMED:
            kstat_data[named.name] = getattr(named.value,
                                             str(named.value.discriminant))

        return kstat_data

    def _get_cpu_time(self, zone):
        """Return the CPU time used in nanoseconds."""
        if zone.id == -1:
            return 0

        kstat_data = self._get_kstat_by_name('zones', 'cpu', str(zone.id),
                                             'sys_zone_aggr')
        if kstat_data is None:
            return 0

        return kstat_data['cpu_nsec_kernel'] + kstat_data['cpu_nsec_user']

    def get_info(self, instance):
        """Get the current status of an instance, by name (not ID!)

        Returns a dict containing:

        :state:           the running state, one of the power_state codes
        :max_mem:         (int) the maximum memory in KBytes allowed
        :mem:             (int) the memory in KBytes used by the domain
        :num_cpu:         (int) the number of virtual CPUs for the domain
        :cpu_time:        (int) the CPU time used in nanoseconds
        """
        # TODO(Vek): Need to pass context in for access to auth_token
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            LOG.error(_("Unable to find instance '%s' via zonemgr(3RAD)")
                      % name)
            raise exception.InstanceNotFound(instance_id=name)

        return {
            'state':    self._get_state(zone),
            'max_mem':  self._get_max_mem(zone),
            'mem':      self._get_mem(zone),
            'num_cpu':  self._get_num_cpu(zone),
            'cpu_time': self._get_cpu_time(zone)
        }

    def get_num_instances(self):
        """Return the total number of virtual machines.

        Return the number of virtual machines that the hypervisor knows
        about.

        .. note::

            This implementation works for all drivers, but it is
            not particularly efficient. Maintainers of the virt drivers are
            encouraged to override this method with something more
            efficient.
        """
        return len(self.list_instances())

    def instance_exists(self, instance_id):
        """Checks existence of an instance on the host.

        :param instance_id: The ID / name of the instance to lookup

        Returns True if an instance with the supplied ID exists on
        the host, False otherwise.

        .. note::

            This implementation works for all drivers, but it is
            not particularly efficient. Maintainers of the virt drivers are
            encouraged to override this method with something more
            efficient.
        """
        return instance_id in self.list_instances()

    def _get_list_zone_object(self):
        """Return a list of all Solaris Zones objects via RAD."""
        return self._rad_instance.list_objects(zonemgr.Zone())

    def list_instances(self):
        """
        Return the names of all the instances known to the virtualization
        layer, as a list.
        """
        # TODO(Vek): Need to pass context in for access to auth_token
        instances_list = []
        for zone in self._get_list_zone_object():
            instances_list.append(self._rad_instance.get_object(zone).name)

        return instances_list

    def list_instance_uuids(self):
        """
        Return the UUIDS of all the instances known to the virtualization
        layer, as a list.
        """
        raise NotImplementedError()

    def _fetch_image(self, context, instance):
        """Fetch an image using Glance given the instance's image_ref."""
        glancecache_dirname = CONF.glancecache_dirname
        fileutils.ensure_tree(glancecache_dirname)
        image = ''.join([glancecache_dirname, '/', instance['image_ref']])
        if os.path.exists(image):
            LOG.debug(_("Using existing, cached Glance image: id %s")
                      % instance['image_ref'])
            return image

        LOG.debug(_("Fetching new Glance image: id %s")
                  % instance['image_ref'])
        try:
            images.fetch(context, instance['image_ref'], image,
                         instance['user_id'], instance['project_id'])
        except Exception as reason:
            LOG.error(_("Unable to fetch Glance image: id %s: %s")
                      % (instance['image_ref'], reason))
            raise

        return image

    def _validate_image(self, image, instance):
        """Validate a glance image for compatibility with the instance"""
        # Skip if the image was already checked and confirmed as valid
        if instance['image_ref'] in self._validated_archives:
            return

        if self._install_engine is None:
            self._install_engine = InstallEngine(ARCHIVE_LOGFILE)

        try:
            init_ua_cp = InstantiateUnifiedArchive(instance['image_ref'],
                                                   image)
            init_ua_cp.execute()
        except Exception:
            reason = (_("Image query failed. Possibly invalid or corrupt. "
                        "Log file location: %s:%s")
                      % (self._uname[1], ARCHIVE_LOGFILE))
            LOG.error(reason)
            raise exception.ImageUnacceptable(image_id=instance['image_ref'],
                                              reason=reason)

        try:
            ua = self._install_engine.doc.volatile.get_first_child(
                class_type=UnifiedArchive)
            # Validate the image at this point to ensure:
            # - contains one deployable system
            deployables = ua.archive_objects
            if len(deployables) != 1:
                reason = (_('Image must contain only 1 deployable system'))
                raise exception.ImageUnacceptable(
                    image_id=instance['image_ref'],
                    reason=reason)
            # - matching architecture
            deployable_arch = deployables[0].system.arch
            compute_arch = platform.processor()
            if deployable_arch != compute_arch:
                reason = (_('Image architecture "%s" is incompatible with this'
                          'compute host architecture: "%s"')
                          % (deployable_arch, compute_arch))
                raise exception.ImageUnacceptable(
                    image_id=instance['image_ref'],
                    reason=reason)
            # - single root pool only
            streams = deployables[0].zfs_streams
            stream_pools = set(stream.zpool for stream in streams)
            if len(stream_pools) > 1:
                reason = (_('Image contains more than one zpool: "%s"')
                          % (stream_pools))
                raise exception.ImageUnacceptable(
                    image_id=instance['image_ref'],
                    reason=reason)
            # - looks like it's OK
            self._validated_archives.append(instance['image_ref'])
        finally:
            # Clear the reference to the UnifiedArchive object in the engine
            # data cache to avoid collision with the next checkpoint execution.
            self._install_engine.doc.volatile.delete_children(
                class_type=UnifiedArchive)

    def _suri_from_volume_info(self, connection_info):
        """Returns a suri(5) formatted string based on connection_info
           Currently supports local ZFS volume and iSCSI driver types.
        """
        driver_type = connection_info['driver_volume_type']
        if driver_type not in ['iscsi', 'local']:
            raise exception.VolumeDriverNotFound(driver_type=driver_type)
        if driver_type == 'local':
            suri = 'dev:/dev/zvol/dsk/%s' % connection_info['volume_path']
        elif driver_type == 'iscsi':
            data = connection_info['data']
            # suri(5) format:
            #       iscsi://<host>[:<port>]/target.<IQN>,lun.<LUN>
            # Sample iSCSI connection data values:
            # target_portal: 192.168.1.244:3260
            # target_iqn: iqn.2010-10.org.openstack:volume-a89c.....
            # target_lun: 1
            suri = 'iscsi://%s/target.%s,lun.%d' % (data['target_portal'],
                                                    data['target_iqn'],
                                                    data['target_lun'])
            # TODO(npower): need to handle CHAP authentication also

        return suri

    def _set_global_properties(self, name, extra_specs, brand):
        """Set Solaris Zone's global properties if supplied via flavor."""
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        # TODO(dcomay): Should figure this out via the brands themselves.
        zonecfg_items = [
            'bootargs',
            'brand',
            'hostid'
        ]
        if brand == ZONE_BRAND_SOLARIS:
            zonecfg_items.extend(
                ['file-mac-profile', 'fs-allowed', 'limitpriv'])

        with ZoneConfig(zone) as zc:
            for key, value in extra_specs.iteritems():
                # Ignore not-zonecfg-scoped brand properties.
                if not key.startswith('zonecfg:'):
                    continue
                _scope, prop = key.split(':', 1)
                # Ignore the 'brand' property if present.
                if prop == 'brand':
                    continue
                # Ignore but warn about unsupported zonecfg-scoped properties.
                if prop not in zonecfg_items:
                    LOG.warning(_("Ignoring unsupported zone property '%s' "
                                  "set on flavor for instance '%s'")
                                % (prop, name))
                    continue
                zc.setprop('global', prop, value)

    def _connect_boot_volume(self, context, instance, extra_specs):
        """Provision a (Cinder) volume service backed boot volume"""
        brand = extra_specs.get('zonecfg:brand', ZONE_BRAND_SOLARIS)
        connection_info = None
        try:
            vol = self._volume_api.create(
                context,
                instance['root_gb'],
                instance['display_name'] + "-rootzpool",
                "Boot volume for instance '%s' (%s)"
                % (instance['name'], instance['uuid']))
            # TODO(npower): Polling is what nova/compute/manager also does when
            # creating a new volume, so we do likewise here.
            while True:
                volume = self._volume_api.get(context, vol['id'])
                if volume['status'] != 'creating':
                    break
                greenthread.sleep(1)

        except Exception as reason:
            LOG.error(_("Unable to create root zpool volume for instance '%s':"
                        "%s") % (instance['name'], reason))
            raise

        instance_uuid = instance['uuid']
        # TODO(npower): Adequate for default boot device. We currently
        # ignore this value, but cinder gets stroppy about this if we set it to
        # None
        mountpoint = "c1d0"

        try:
            connector = self.get_volume_connector(instance)
            connection_info = self._volume_api.initialize_connection(context,
                                                                     volume,
                                                                     connector)
            # Check connection_info to determine if the provided volume is
            # local to this compute node. If it is, then don't use it for
            # Solaris branded zones in order to avoid a know ZFS deadlock issue
            # when using a zpool within another zpool on the same system.
            delete_boot_volume = False
            if brand == ZONE_BRAND_SOLARIS:
                driver_type = connection_info['driver_volume_type']
                if driver_type == 'local':
                    LOG.warning(_("Detected 'local' zvol driver volume type "
                                "from volume service, which should not be "
                                "used as a boot device for 'solaris' branded "
                                "zones."))
                    delete_boot_volume = True
                elif driver_type == 'iscsi':
                    # Check for a potential loopback iSCSI situation
                    data = connection_info['data']
                    target_portal = data['target_portal']
                    # Strip off the port number (eg. 127.0.0.1:3260)
                    host = target_portal.rsplit(':', 1)
                    # Strip any enclosing '[' and ']' brackets for
                    # IPV6 addresses.
                    target_host = host[0].strip('[]')

                    # Check if target_host is an IP or hostname matching the
                    # connector host or IP, which would mean the provisioned
                    # iSCSI LUN is on the same host as the instance.
                    if target_host in [connector['ip'], connector['host']]:
                        LOG.warning(_("iSCSI connection info from volume "
                                    "service indicates that the target is a "
                                    "local volume, which should not be used "
                                    "as a boot device for 'solaris' branded "
                                    "zones."))
                        delete_boot_volume = True
                else:
                    # Some other connection type that we don't understand
                    # Let zone use some local fallback instead.
                    LOG.warning(_("Unsupported volume driver type '%s' "
                                "can not be used as a boot device for "
                                "'solaris' branded zones."))
                    delete_boot_volume = True

            if delete_boot_volume:
                LOG.warning(_("Volume '%s' is being discarded") % volume['id'])
                self._volume_api.delete(context, volume)
                return None

            # Notify Cinder DB of the volume attachment.
            self._volume_api.attach(context, volume, instance_uuid, mountpoint)
            values = {
                'instance_uuid': instance['uuid'],
                'connection_info': jsonutils.dumps(connection_info),
                # TODO(npower): device_name also ignored currently, but Cinder
                # breaks without it. Figure out a sane mapping scheme.
                'device_name': mountpoint,
                'delete_on_termination': True,
                'virtual_name': None,
                'snapshot_id': None,
                'volume_id': volume['id'],
                'volume_size': instance['root_gb'],
                'no_device': None}
            self._conductor_api.block_device_mapping_update_or_create(context,
                                                                      values)

        except Exception as reason:
            LOG.error(_("Unable to attach root zpool volume '%s' to instance "
                        "%s: %s") % (volume['id'], instance['name'], reason))
            self._volume_api.detach(context, volume)
            self._volume_api.delete(context, volume)
            raise

        return connection_info

    def _set_boot_device(self, name, connection_info, brand):
        """Set the boot device specified by connection_info"""
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        suri = self._suri_from_volume_info(connection_info)

        with ZoneConfig(zone) as zc:
            # ZOSS device configuration is different for the solaris-kz brand
            if brand == ZONE_BRAND_SOLARIS_KZ:
                zc.zone.setResourceProperties(
                    zonemgr.Resource(
                        "device",
                        [zonemgr.Property("bootpri", "0")]),
                    [zonemgr.Property("storage", suri)])
            else:
                zc.addresource(
                    "rootzpool",
                    [zonemgr.Property("storage", listvalue=[suri])])

    def _set_num_cpu(self, name, vcpus, brand):
        """Set number of VCPUs in a Solaris Zone configuration."""
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        # The Solaris Zone brand type is used to specify the type of
        # 'cpu' resource set in the Solaris Zone configuration.
        if brand == ZONE_BRAND_SOLARIS:
            vcpu_resource = 'capped-cpu'
        else:
            vcpu_resource = 'virtual-cpu'

        # TODO(dcomay): Until 17881862 is resolved, this should be turned into
        # an appropriate 'rctl' resource for the 'capped-cpu' case.
        with ZoneConfig(zone) as zc:
            zc.setprop(vcpu_resource, 'ncpus', str(vcpus))

    def _set_memory_cap(self, name, memory_mb, brand):
        """Set memory cap in a Solaris Zone configuration."""
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        # The Solaris Zone brand type is used to specify the type of
        # 'memory' cap set in the Solaris Zone configuration.
        if brand == ZONE_BRAND_SOLARIS:
            mem_resource = 'swap'
        else:
            mem_resource = 'physical'

        with ZoneConfig(zone) as zc:
            zc.setprop('capped-memory', mem_resource, '%dM' % memory_mb)

    def _set_network(self, context, name, instance, network_info, brand,
                     sc_dir):
        """ add networking information to the zone.
        """
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        tenant_id = None
        for netid, network in enumerate(network_info):
            if tenant_id is None:
                tenant_id = network['network']['meta']['tenant_id']
            network_uuid = network['network']['id']
            port_uuid = network['id']
            ip = network['network']['subnets'][0]['ips'][0]['address']
            ip_version = network['network']['subnets'][0]['version']
            route = network['network']['subnets'][0]['gateway']['address']
            dns_list = network['network']['subnets'][0]['dns']
            nameservers = []
            for dns in dns_list:
                if dns['type'] == 'dns':
                    nameservers.append(dns['address'])

            with ZoneConfig(zone) as zc:
                if netid == 0:
                    zc.setprop('anet', 'configure-allowed-address', 'false')
                    zc.setprop('anet', 'evs', network_uuid)
                    zc.setprop('anet', 'vport', port_uuid)
                else:
                    zc.addresource(
                        'anet',
                        [zonemgr.Property('configure-allowed-address',
                                          'false'),
                         zonemgr.Property('evs', network_uuid),
                         zonemgr.Property('vport', port_uuid)])

                filter = [zonemgr.Property('vport', port_uuid)]
                if brand == ZONE_BRAND_SOLARIS:
                    linkname = lookup_resource_property(zc.zone, 'anet',
                                                        'linkname', filter)
                else:
                    id = lookup_resource_property(zc.zone, 'anet', 'id',
                                                  filter)
                    linkname = 'net%s' % id

            # create the required sysconfig file
            network_plugin = quantumv2.get_client(context)
            port = network_plugin.show_port(port_uuid)['port']
            subnet_uuid = port['fixed_ips'][0]['subnet_id']
            subnet = network_plugin.show_subnet(subnet_uuid)['subnet']

            if subnet['enable_dhcp']:
                tree = sysconfig.create_ncp_defaultfixed('dhcp', linkname,
                                                         netid, ip_version)
            else:
                tree = sysconfig.create_ncp_defaultfixed('static', linkname,
                                                         netid, ip_version, ip,
                                                         route, nameservers)

            fp = os.path.join(sc_dir, 'evs-network-%d.xml' % netid)
            sysconfig.create_sc_profile(fp, tree)

        if tenant_id is not None:
            # set the tenant id
            with ZoneConfig(zone) as zc:
                zc.setprop('global', 'tenant', tenant_id)

    def _verify_sysconfig(self, sc_dir, instance):
        """ verify the SC profile(s) passed in contain an entry for
        system/config-user to configure the root account.  If an SSH key is
        specified, configure root's profile to use it.

        """
        usercheck = lambda e: e.attrib.get('name') == 'system/config-user'
        hostcheck = lambda e: e.attrib.get('name') == 'system/identity'

        root_account_needed = True
        hostname_needed = True
        sshkey = instance.get('key_data')
        name = instance.get('display_name')

        # find all XML files in sc_dir
        for root, dirs, files in os.walk(sc_dir):
            for fname in [f for f in files if f.endswith(".xml")]:
                root = etree.parse(os.path.join(root, fname))

                # look for config-user properties
                if filter(usercheck, root.findall('service')):
                    # a service element was found for config-user.  Verify
                    # root's password is set, the admin account name is set and
                    # the admin's password is set
                    pgs = root.iter('property_group')
                    for pg in pgs:
                        if pg.attrib.get('name') == 'root_account':
                            root_account_needed = False

                # look for identity properties
                if filter(hostcheck, root.findall('service')):
                    for props in root.iter('propval'):
                        if props.attrib.get('name') == 'nodename':
                            hostname_needed = False

        # Verify all of the requirements were met.  Create the required SMF
        # profile(s) if needed.
        if root_account_needed:
            fp = os.path.join(sc_dir, 'config-root.xml')

            if sshkey is not None:
                # set up the root account as 'normal' with no expiration and
                # an ssh key
                tree = sysconfig.create_default_root_account(sshkey=sshkey)
            else:
                # set up the root account as 'normal' but to expire immediately
                tree = sysconfig.create_default_root_account(expire='0')

            sysconfig.create_sc_profile(fp, tree)

        elif sshkey is not None:
            fp = os.path.join(sc_dir, 'config-root-ssh-keys.xml')
            tree = sysconfig.create_root_ssh_keys(sshkey)
            sysconfig.create_sc_profile(fp, tree)

        if hostname_needed and name is not None:
            fp = os.path.join(sc_dir, 'hostname.xml')
            sysconfig.create_sc_profile(fp, sysconfig.create_hostname(name))

    def _create_config(self, context, instance, network_info,
                       connection_info, extra_specs, sc_dir):
        """Create a new Solaris Zone configuration."""
        name = instance['name']
        if self._get_zone_by_name(name) is not None:
            raise exception.InstanceExists(name=name)

        # If unspecified, default zone brand is ZONE_BRAND_SOLARIS
        brand = extra_specs.get('zonecfg:brand', ZONE_BRAND_SOLARIS)
        template = ZONE_BRAND_TEMPLATE.get(brand)
        # TODO(dcomay): Detect capability via libv12n(3LIB) or virtinfo(1M).
        if template is None:
            msg = (_("Invalid brand '%s' specified for instance '%s'"
                   % (brand, name)))
            raise exception.NovaException(msg)

        sc_profile = extra_specs.get('install:sc_profile')
        if sc_profile is not None:
            if os.path.isfile(sc_profile):
                shutil.copy(sc_profile, sc_dir)
            elif os.path.isdir(sc_profile):
                shutil.copytree(sc_profile, os.path.join(sc_dir, 'sysconfig'))

        self._verify_sysconfig(sc_dir, instance)

        zonemanager = self._rad_instance.get_object(zonemgr.ZoneManager())
        try:
            zonemanager.create(name, None, template)
            self._set_global_properties(name, extra_specs, brand)
            if connection_info:
                self._set_boot_device(name, connection_info, brand)
            self._set_num_cpu(name, instance['vcpus'], brand)
            self._set_memory_cap(name, instance['memory_mb'], brand)
            self._set_network(context, name, instance, network_info, brand,
                              sc_dir)
        except Exception as reason:
            LOG.error(_("Unable to create configuration for instance '%s' via "
                        "zonemgr(3RAD): %s") % (name, reason))
            raise

    def _install(self, instance, image, extra_specs, sc_dir):
        """Install a new Solaris Zone root file system."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        # log the zone's configuration
        with ZoneConfig(zone) as zc:
            LOG.debug("-" * 80)
            LOG.debug(zc.zone.exportConfig(True))
            LOG.debug("-" * 80)

        options = ['-a ', image]

        if os.listdir(sc_dir):
            # the directory isn't empty so pass it along to install
            options.extend(['-c ', sc_dir])

        try:
            LOG.debug(_("installing instance '%s' (%s)") %
                      (name, instance['display_name']))
            zone.install(options=options)
        except Exception as reason:
            LOG.error(_("Unable to install root file system for instance '%s' "
                        "via zonemgr(3RAD): %s") % (name, reason))
            raise

        LOG.debug(_("installation of instance '%s' (%s) complete") %
                  (name, instance['display_name']))

        if os.listdir(sc_dir):
            # remove the sc_profile temp directory
            shutil.rmtree(sc_dir)

    def _power_on(self, instance):
        """Power on a Solaris Zone."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        try:
            zone.boot()
        except Exception as reason:
            LOG.error(_("Unable to power on instance '%s' via zonemgr(3RAD): "
                        "%s") % (name, reason))
            raise exception.InstancePowerOnFailure(reason=reason)

    def _uninstall(self, instance):
        """Uninstall an existing Solaris Zone root file system."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        try:
            zone.uninstall(['-F'])
        except Exception as reason:
            LOG.error(_("Unable to uninstall root file system for instance "
                        "'%s' via zonemgr(3RAD): %s") % (name, reason))
            raise

    def _delete_config(self, instance):
        """Delete an existing Solaris Zone configuration."""
        name = instance['name']
        if self._get_zone_by_name(name) is None:
            raise exception.InstanceNotFound(instance_id=name)

        zonemanager = self._rad_instance.get_object(zonemgr.ZoneManager())
        try:
            zonemanager.delete(name)
        except Exception as reason:
            LOG.error(_("Unable to delete configuration for instance '%s' via "
                        "zonemgr(3RAD): %s") % (name, reason))
            raise

    def spawn(self, context, instance, image_meta, injected_files,
              admin_password, network_info=None, block_device_info=None):
        """
        Create a new instance/VM/domain on the virtualization platform.

        Once this successfully completes, the instance should be
        running (power_state.RUNNING).

        If this fails, any partial instance should be completely
        cleaned up, and the virtualization platform should be in the state
        that it was before this call began.

        :param context: security context
        :param instance: Instance object as returned by DB layer.
                         This function should use the data there to guide
                         the creation of the new instance.
        :param image_meta: image object returned by nova.image.glance that
                           defines the image from which to boot this instance
        :param injected_files: User files to inject into instance.
        :param admin_password: Administrator password to set in instance.
        :param network_info:
           :py:meth:`~nova.network.manager.NetworkManager.get_instance_nw_info`
        :param block_device_info: Information about block devices to be
                                  attached to the instance.
        """
        inst_type = self.virtapi.instance_type_get(
            nova_context.get_admin_context(read_deleted='yes'),
            instance['instance_type_id'])
        extra_specs = inst_type['extra_specs'].copy()

        image = self._fetch_image(context, instance)
        self._validate_image(image, instance)

        # create a new directory for SC profiles
        sc_dir = tempfile.mkdtemp(prefix="nova-sysconfig-",
                                  dir=CONF.state_path)
        os.chmod(sc_dir, 0755)

        # Attempt to provision a (Cinder) volume service backed boot volume
        connection_info = self._connect_boot_volume(context, instance,
                                                    extra_specs)

        LOG.debug(_("creating zone configuration for '%s' (%s)") %
                  (instance['name'], instance['display_name']))
        self._create_config(context, instance, network_info,
                            connection_info, extra_specs, sc_dir)
        try:
            self._install(instance, image, extra_specs, sc_dir)
            self._power_on(instance)
        except Exception as reason:
            LOG.error(_("Unable to spawn instance '%s' via zonemgr(3RAD): %s")
                      % (instance['name'], reason))
            self._uninstall(instance)
            self._delete_config(instance)
            raise

    def _power_off(self, instance, halt_type):
        """Power off a Solaris Zone."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        try:
            if halt_type == 'SOFT':
                zone.shutdown()
            else:
                zone.halt()
            return
        except rad.client.ObjectError as reason:
            result = reason.get_payload()
            if result.code == zonemgr.ErrorCode.COMMAND_ERROR:
                LOG.warning(_("Ignoring command error returned while trying "
                              "to power off instance '%s' via zonemgr(3RAD): "
                              "%s" % (name, reason)))
                return
        except Exception as reason:
            LOG.error(_("Unable to power off instance '%s' via zonemgr(3RAD): "
                        "%s") % (name, reason))
            raise exception.InstancePowerOffFailure(reason=reason)

    def destroy(self, instance, network_info, block_device_info=None,
                destroy_disks=True):
        """Destroy (shutdown and delete) the specified instance.

        If the instance is not found (for example if networking failed), this
        function should still succeed.  It's probably a good idea to log a
        warning in that case.

        :param instance: Instance object as returned by DB layer.
        :param network_info:
           :py:meth:`~nova.network.manager.NetworkManager.get_instance_nw_info`
        :param block_device_info: Information about block devices that should
                                  be detached from the instance.
        :param destroy_disks: Indicates if disks should be destroyed

        """
        # TODO(Vek): Need to pass context in for access to auth_token
        name = instance['name']
        zone = self._get_zone_by_name(name)
        # If instance cannot be found, just return.
        if zone is None:
            LOG.warning(_("Unable to find instance '%s' via zonemgr(3RAD)")
                        % name)
            return

        try:
            if self._get_state(zone) == power_state.RUNNING:
                self._power_off(instance, 'HARD')
            if self._get_state(zone) == power_state.SHUTDOWN:
                self._uninstall(instance)
            if self._get_state(zone) == power_state.NOSTATE:
                self._delete_config(instance)
        except Exception as reason:
            LOG.warning(_("Unable to destroy instance '%s' via zonemgr(3RAD): "
                          "%s") % (name, reason))

    def reboot(self, context, instance, network_info, reboot_type,
               block_device_info=None, bad_volumes_callback=None):
        """Reboot the specified instance.

        After this is called successfully, the instance's state
        goes back to power_state.RUNNING. The virtualization
        platform should ensure that the reboot action has completed
        successfully even in cases in which the underlying domain/vm
        is paused or halted/stopped.

        :param instance: Instance object as returned by DB layer.
        :param network_info:
           :py:meth:`~nova.network.manager.NetworkManager.get_instance_nw_info`
        :param reboot_type: Either a HARD or SOFT reboot
        :param block_device_info: Info pertaining to attached volumes
        :param bad_volumes_callback: Function to handle any bad volumes
            encountered
        """
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        try:
            if reboot_type == 'SOFT':
                zone.shutdown(['-r'])
            else:
                zone.reboot()
        except Exception as reason:
            LOG.error(_("Unable to reboot instance '%s' via zonemgr(3RAD): %s")
                      % (name, reason))
            raise exception.InstanceRebootFailure(reason=reason)

    def get_console_pool_info(self, console_type):
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def _get_console_output(self, instance):
        """Builds a string containing the console output (capped at
        MAX_CONSOLE_BYTES characters) by reassembling the log files
        that Solaris Zones framework maintains for each zone.
        """
        console_str = ""
        avail = MAX_CONSOLE_BYTES

        # Examine the log files in most-recently modified order, keeping
        # track of the size of each file and of how many characters have
        # been seen. If there are still characters left to incorporate,
        # then the contents of the log file in question are prepended to
        # the console string built so far. When the number of characters
        # available has run out, the last fragment under consideration
        # will likely begin within the middle of a line. As such, the
        # start of the fragment up to the next newline is thrown away.
        # The remainder constitutes the start of the resulting console
        # output which is then prepended to the console string built so
        # far and the result returned.
        logfile_pattern = '/var/log/zones/%s.console*' % instance['name']
        logfiles = sorted(glob.glob(logfile_pattern), key=os.path.getmtime,
                          reverse=True)
        for file in logfiles:
            size = os.path.getsize(file)
            if size == 0:
                continue
            avail -= size
            with open(file, 'r') as log:
                if avail < 0:
                    (fragment, _) = utils.last_bytes(log, avail + size)
                    remainder = fragment.find('\n') + 1
                    console_str = fragment[remainder:] + console_str
                    break
                fragment = ''
                for line in log.readlines():
                    fragment += line
                console_str = fragment + console_str

        return console_str

    def get_console_output(self, instance):
        # TODO(Vek): Need to pass context in for access to auth_token
        return self._get_console_output(instance)

    def get_vnc_console(self, instance):
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def get_spice_console(self, instance):
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def _get_zone_diagnostics(self, zone):
        """Return data about Solaris Zone diagnostics."""
        if zone.id == -1:
            return None

        diagnostics = {}
        id = str(zone.id)

        kstat_data = self._get_kstat_by_name('zone_caps', 'caps', id,
                                             ''.join(('lockedmem_zone_', id)))
        if kstat_data is not None:
            diagnostics['lockedmem'] = kstat_data['usage']

        kstat_data = self._get_kstat_by_name('zone_caps', 'caps', id,
                                             ''.join(('nprocs_zone_', id)))
        if kstat_data is not None:
            diagnostics['nprocs'] = kstat_data['usage']

        kstat_data = self._get_kstat_by_name('zone_caps', 'caps', id,
                                             ''.join(('swapresv_zone_', id)))
        if kstat_data is not None:
            diagnostics['swapresv'] = kstat_data['usage']

        kstat_data = self._get_kstat_by_name('zones', 'cpu', id,
                                             'sys_zone_aggr')
        if kstat_data is not None:
            for key in kstat_data.keys():
                if key not in ('class', 'crtime', 'snaptime'):
                    diagnostics[key] = kstat_data[key]

        return diagnostics

    def get_diagnostics(self, instance):
        """Return data about VM diagnostics."""
        # TODO(Vek): Need to pass context in for access to auth_token
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            LOG.error(_("Unable to find instance '%s' via zonemgr(3RAD)")
                      % name)
            raise exception.InstanceNotFound(instance_id=name)

        return self._get_zone_diagnostics(zone)

    def get_all_bw_counters(self, instances):
        """Return bandwidth usage counters for each interface on each
           running VM"""
        raise NotImplementedError()

    def get_all_volume_usage(self, context, compute_host_bdms):
        """Return usage info for volumes attached to vms on
           a given host"""
        raise NotImplementedError()

    def get_host_ip_addr(self):
        """
        Retrieves the IP address of the dom0
        """
        # TODO(Vek): Need to pass context in for access to auth_token
        return CONF.my_ip

    def attach_volume(self, connection_info, instance, mountpoint):
        """Attach the disk to the instance at mountpoint using info."""
        # TODO(npower): Apply mountpoint in a meaningful way to the zone
        # (I don't think this is even possible for Solaris brand zones)
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        zprop = lookup_resource_property_value(zone, "global", "brand",
                                               ZONE_BRAND_SOLARIS_KZ)
        if not zprop:
            # Only Solaris Kernel zones are currently supported.
            raise NotImplementedError()

        suri = self._suri_from_volume_info(connection_info)

        with ZoneConfig(zone) as zc:
            zc.addresource("device", [zonemgr.Property("storage", suri)])

    def detach_volume(self, connection_info, instance, mountpoint):
        """Detach the disk attached to the instance."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        zprop = lookup_resource_property_value(zone, "global", "brand",
                                               ZONE_BRAND_SOLARIS_KZ)
        if not zprop:
            # Only Solaris Kernel zones are currently supported.
            raise NotImplementedError()

        suri = self._suri_from_volume_info(connection_info)

        # Check if the specific property value exists before attempting removal
        prop = lookup_resource_property_value(zone, "device", "storage", suri)
        if not prop:
            LOG.warning(_("Storage resource '%s' is not attached to instance "
                        "'%s'") % (suri, name))
            return

        with ZoneConfig(zone) as zc:
            zc.removeresources("device", [zonemgr.Property("storage", suri)])

    def attach_interface(self, instance, image_meta, network_info):
        """Attach an interface to the instance."""
        raise NotImplementedError()

    def detach_interface(self, instance, network_info):
        """Detach an interface from the instance."""
        raise NotImplementedError()

    def migrate_disk_and_power_off(self, context, instance, dest,
                                   instance_type, network_info,
                                   block_device_info=None):
        """
        Transfers the disk of a running instance in multiple phases, turning
        off the instance before the end.
        """
        raise NotImplementedError()

    def snapshot(self, context, instance, image_id, update_task_state):
        """
        Snapshots the specified instance.

        :param context: security context
        :param instance: Instance object as returned by DB layer.
        :param image_id: Reference to a pre-created image that will
                         hold the snapshot.
        """
        # Get original base image info
        (base_service, base_id) = glance.get_remote_image_service(
            context, instance['image_ref'])
        try:
            base = base_service.show(context, base_id)
        except exception.ImageNotFound:
            base = {}

        snapshot_service, snapshot_id = glance.get_remote_image_service(
            context, image_id)

        # Build updated snapshot image metadata
        snapshot = snapshot_service.show(context, snapshot_id)
        metadata = {
            'is_public': False,
            'status': 'active',
            'name': snapshot['name'],
            'properties': {
                'image_location': 'snapshot',
                'image_state': 'available',
                'owner_id': instance['project_id'],
            }
        }
        # Match architecture, hypervisor_type and vm_mode properties to base
        # image.
        for prop in ['architecture', 'hypervisor_type', 'vm_mode']:
            if prop in base.get('properties', {}):
                base_prop = base['properties'][prop]
                metadata['properties'][prop] = base_prop

        # Set generic container and disk formats initially in case the glance
        # service rejects unified archives (uar) and zfs in metadata
        metadata['container_format'] = 'ovf'
        metadata['disk_format'] = 'raw'

        update_task_state(task_state=task_states.IMAGE_PENDING_UPLOAD)
        snapshot_directory = CONF.solariszones_snapshots_directory
        fileutils.ensure_tree(snapshot_directory)
        snapshot_name = uuid.uuid4().hex

        with utils.tempdir(dir=snapshot_directory) as tmpdir:
            out_path = os.path.join(tmpdir, snapshot_name)

            # TODO(npower): archiveadm invocation needs --root-only arg
            # passed once it is available. Assume the instance contains
            # root pool only for now.
            zone_name = instance['name']
            utils.execute('/usr/sbin/archiveadm', 'create', '--root-only',
                          '-z', zone_name, out_path)

            LOG.info(_("Snapshot extracted, beginning image upload"),
                     instance=instance)
            try:
                # Upload the archive image to the image service
                update_task_state(task_state=task_states.IMAGE_UPLOADING,
                                  expected_state=
                                  task_states.IMAGE_PENDING_UPLOAD)
                with open(out_path, 'r') as image_file:
                    snapshot_service.update(context,
                                            image_id,
                                            metadata,
                                            image_file)
                    LOG.info(_("Snapshot image upload complete"),
                             instance=instance)
                try:
                    # Try to update the image metadata container and disk
                    # formats more suitably for a unified archive if the
                    # glance server recognises them.
                    metadata['container_format'] = 'uar'
                    metadata['disk_format'] = 'zfs'
                    snapshot_service.update(context,
                                            image_id,
                                            metadata,
                                            None)
                except exception.Invalid as invalid:
                    LOG.warning(_("Image service rejected image metadata "
                                  "container and disk formats 'uar' and "
                                  "'zfs'. Using generic values 'ovf' and "
                                  "'raw' as fallbacks."))
            finally:
                # Delete the snapshot image file source
                os.unlink(out_path)

    def finish_migration(self, context, migration, instance, disk_info,
                         network_info, image_meta, resize_instance,
                         block_device_info=None):
        """Completes a resize, turning on the migrated instance

        :param network_info:
           :py:meth:`~nova.network.manager.NetworkManager.get_instance_nw_info`
        :param image_meta: image object returned by nova.image.glance that
                           defines the image from which this instance
                           was created
        """
        raise NotImplementedError()

    def confirm_migration(self, migration, instance, network_info):
        """Confirms a resize, destroying the source VM."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def finish_revert_migration(self, instance, network_info,
                                block_device_info=None):
        """Finish reverting a resize, powering back on the instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def pause(self, instance):
        """Pause the specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def unpause(self, instance):
        """Unpause paused VM instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def _suspend(self, instance):
        """Suspend a Solaris Zone."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        if self._uname[4] != 'i86pc':
            # Only x86 platforms are currently supported.
            raise NotImplementedError()

        zprop = lookup_resource_property_value(zone, "global", "brand",
                                               ZONE_BRAND_SOLARIS_KZ)
        if not zprop:
            # Only Solaris Kernel zones are currently supported.
            raise NotImplementedError()

        try:
            zone.suspend()
        except Exception as reason:
            # TODO(dcomay): Try to recover in cases where zone has been
            # resumed automatically.
            LOG.error(_("Unable to suspend instance '%s' via zonemgr(3RAD): "
                        "%s") % (name, reason))
            raise exception.InstanceSuspendFailure(reason=reason)

    def suspend(self, instance):
        """suspend the specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        self._suspend(instance)

    def resume(self, instance, network_info, block_device_info=None):
        """resume the specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        try:
            self._power_on(instance)
        except Exception as reason:
            raise exception.InstanceResumeFailure(reason=reason)

    def resume_state_on_host_boot(self, context, instance, network_info,
                                  block_device_info=None):
        """resume guest state when a host is booted."""
        name = instance['name']
        zone = self._get_zone_by_name(name)
        if zone is None:
            raise exception.InstanceNotFound(instance_id=name)

        # TODO(dcomay): Should reconcile with value of zone's autoboot
        # property.
        if self._get_state(zone) not in (power_state.CRASHED,
                                         power_state.SHUTDOWN):
            return

        self._power_on(instance)

    def rescue(self, context, instance, network_info, image_meta,
               rescue_password):
        """Rescue the specified instance."""
        raise NotImplementedError()

    def unrescue(self, instance, network_info):
        """Unrescue the specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def power_off(self, instance):
        """Power off the specified instance."""
        self._power_off(instance, 'SOFT')

    def power_on(self, context, instance, network_info,
                 block_device_info=None):
        """Power on the specified instance."""
        self._power_on(instance)

    def soft_delete(self, instance):
        """Soft delete the specified instance."""
        raise NotImplementedError()

    def restore(self, instance):
        """Restore the specified instance."""
        raise NotImplementedError()

    def _get_zpool_property(self, prop, zpool):
        """Get the value of property from the zpool."""
        try:
            value = None
            (out, _err) = utils.execute('/usr/sbin/zpool', 'get', prop, zpool)
        except exception.ProcessExecutionError as err:
            LOG.error(_("Failed to get property '%s' from zpool '%s': %s")
                      % (prop, zpool, err.stderr))
            return value

        zpool_prop = out.splitlines()[1].split()
        if zpool_prop[1] == prop:
            value = zpool_prop[2]

        return value

    def _update_host_stats(self):
        """Update currently known host stats."""
        host_stats = {}
        host_stats['vcpus'] = os.sysconf('SC_NPROCESSORS_ONLN')
        pages = os.sysconf('SC_PHYS_PAGES')
        host_stats['memory_mb'] = self._pages_to_kb(pages) / 1024

        out, err = utils.execute('/usr/sbin/zfs', 'list', '-Ho', 'name', '/')
        root_zpool = out.split('/')[0]
        size = self._get_zpool_property('size', root_zpool)
        if size is None:
            host_stats['local_gb'] = 0
        else:
            host_stats['local_gb'] = utils.to_bytes(size)/(1024 ** 3)

        # Account for any existing processor sets by looking at the the
        # number of CPUs not assigned to any processor sets.
        kstat_data = self._get_kstat_by_name('misc', 'unix', '0', 'pset')
        if kstat_data is not None:
            host_stats['vcpus_used'] = \
                host_stats['vcpus'] - kstat_data['ncpus']
        else:
            host_stats['vcpus_used'] = 0

        # Subtract the number of free pages from the total to get the
        # used.
        kstat_data = self._get_kstat_by_name('pages', 'unix', '0',
                                             'system_pages')
        if kstat_data is not None:
            host_stats['memory_mb_used'] = \
                self._pages_to_kb((pages - kstat_data['freemem'])) / 1024
        else:
            host_stats['memory_mb_used'] = 0

        host_stats['local_gb_used'] = 0
        host_stats['hypervisor_type'] = 'solariszones'
        host_stats['hypervisor_version'] = int(self._uname[2].replace('.', ''))
        host_stats['hypervisor_hostname'] = self._uname[1]
        if self._uname[4] == 'i86pc':
            architecture = 'x86_64'
        else:
            architecture = 'sparc64'
        host_stats['cpu_info'] = str({'arch': architecture})
        host_stats['disk_available_least'] = 0

        supported_instances = [
            (architecture, 'solariszones', 'zones')
        ]
        host_stats['supported_instances'] = supported_instances

        self._host_stats = host_stats

    def get_available_resource(self, nodename):
        """Retrieve resource information.

        This method is called when nova-compute launches, and
        as part of a periodic task

        :param nodename:
            node which the caller want to get resources from
            a driver that manages only one node can safely ignore this
        :returns: Dictionary describing resources
        """
        self._update_host_stats()
        host_stats = self._host_stats

        resources = {}
        resources['vcpus'] = host_stats['vcpus']
        resources['memory_mb'] = host_stats['memory_mb']
        resources['local_gb'] = host_stats['local_gb']
        resources['vcpus_used'] = host_stats['vcpus_used']
        resources['memory_mb_used'] = host_stats['memory_mb_used']
        resources['local_gb_used'] = host_stats['local_gb_used']
        resources['hypervisor_type'] = host_stats['hypervisor_type']
        resources['hypervisor_version'] = host_stats['hypervisor_version']
        resources['hypervisor_hostname'] = host_stats['hypervisor_hostname']
        resources['cpu_info'] = host_stats['cpu_info']
        resources['disk_available_least'] = host_stats['disk_available_least']

        return resources

    def pre_live_migration(self, ctxt, instance_ref, block_device_info,
                           network_info, disk_info, migrate_data=None):
        """Prepare an instance for live migration

        :param ctxt: security context
        :param instance_ref: instance object that will be migrated
        :param block_device_info: instance block device information
        :param network_info: instance network information
        :param disk_info: instance disk information
        :param migrate_data: implementation specific data dict.
        """
        raise NotImplementedError()

    def live_migration(self, ctxt, instance_ref, dest,
                       post_method, recover_method, block_migration=False,
                       migrate_data=None):
        """Live migration of an instance to another host.

        :params ctxt: security context
        :params instance_ref:
            nova.db.sqlalchemy.models.Instance object
            instance object that is migrated.
        :params dest: destination host
        :params post_method:
            post operation method.
            expected nova.compute.manager.post_live_migration.
        :params recover_method:
            recovery method when any exception occurs.
            expected nova.compute.manager.recover_live_migration.
        :params block_migration: if true, migrate VM disk.
        :params migrate_data: implementation specific params.

        """
        raise NotImplementedError()

    def post_live_migration_at_destination(self, ctxt, instance_ref,
                                           network_info,
                                           block_migration=False,
                                           block_device_info=None):
        """Post operation of live migration at destination host.

        :param ctxt: security context
        :param instance_ref: instance object that is migrated
        :param network_info: instance network information
        :param block_migration: if true, post operation of block_migration.
        """
        raise NotImplementedError()

    def check_can_live_migrate_destination(self, ctxt, instance_ref,
                                           src_compute_info, dst_compute_info,
                                           block_migration=False,
                                           disk_over_commit=False):
        """Check if it is possible to execute live migration.

        This runs checks on the destination host, and then calls
        back to the source host to check the results.

        :param ctxt: security context
        :param instance_ref: nova.db.sqlalchemy.models.Instance
        :param src_compute_info: Info about the sending machine
        :param dst_compute_info: Info about the receiving machine
        :param block_migration: if true, prepare for block migration
        :param disk_over_commit: if true, allow disk over commit
        """
        raise NotImplementedError()

    def check_can_live_migrate_destination_cleanup(self, ctxt,
                                                   dest_check_data):
        """Do required cleanup on dest host after check_can_live_migrate calls

        :param ctxt: security context
        :param dest_check_data: result of check_can_live_migrate_destination
        """
        raise NotImplementedError()

    def check_can_live_migrate_source(self, ctxt, instance_ref,
                                      dest_check_data):
        """Check if it is possible to execute live migration.

        This checks if the live migration can succeed, based on the
        results from check_can_live_migrate_destination.

        :param context: security context
        :param instance_ref: nova.db.sqlalchemy.models.Instance
        :param dest_check_data: result of check_can_live_migrate_destination
        """
        raise NotImplementedError()

    def refresh_security_group_rules(self, security_group_id):
        """This method is called after a change to security groups.

        All security groups and their associated rules live in the datastore,
        and calling this method should apply the updated rules to instances
        running the specified security group.

        An error should be raised if the operation cannot complete.

        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def refresh_security_group_members(self, security_group_id):
        """This method is called when a security group is added to an instance.

        This message is sent to the virtualization drivers on hosts that are
        running an instance that belongs to a security group that has a rule
        that references the security group identified by `security_group_id`.
        It is the responsibility of this method to make sure any rules
        that authorize traffic flow with members of the security group are
        updated and any new members can communicate, and any removed members
        cannot.

        Scenario:
            * we are running on host 'H0' and we have an instance 'i-0'.
            * instance 'i-0' is a member of security group 'speaks-b'
            * group 'speaks-b' has an ingress rule that authorizes group 'b'
            * another host 'H1' runs an instance 'i-1'
            * instance 'i-1' is a member of security group 'b'

            When 'i-1' launches or terminates we will receive the message
            to update members of group 'b', at which time we will make
            any changes needed to the rules for instance 'i-0' to allow
            or deny traffic coming from 'i-1', depending on if it is being
            added or removed from the group.

        In this scenario, 'i-1' could just as easily have been running on our
        host 'H0' and this method would still have been called.  The point was
        that this method isn't called on the host where instances of that
        group are running (as is the case with
        :py:meth:`refresh_security_group_rules`) but is called where references
        are made to authorizing those instances.

        An error should be raised if the operation cannot complete.

        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def refresh_provider_fw_rules(self):
        """This triggers a firewall update based on database changes.

        When this is called, rules have either been added or removed from the
        datastore.  You can retrieve rules with
        :py:meth:`nova.db.provider_fw_rule_get_all`.

        Provider rules take precedence over security group rules.  If an IP
        would be allowed by a security group ingress rule, but blocked by
        a provider rule, then packets from the IP are dropped.  This includes
        intra-project traffic in the case of the allow_project_net_traffic
        flag for the libvirt-derived classes.

        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def reset_network(self, instance):
        """reset networking for specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        pass

    def ensure_filtering_rules_for_instance(self, instance_ref, network_info):
        """Setting up filtering rules and waiting for its completion.

        To migrate an instance, filtering rules to hypervisors
        and firewalls are inevitable on destination host.
        ( Waiting only for filtering rules to hypervisor,
        since filtering rules to firewall rules can be set faster).

        Concretely, the below method must be called.
        - setup_basic_filtering (for nova-basic, etc.)
        - prepare_instance_filter(for nova-instance-instance-xxx, etc.)

        to_xml may have to be called since it defines PROJNET, PROJMASK.
        but libvirt migrates those value through migrateToURI(),
        so , no need to be called.

        Don't use thread for this method since migration should
        not be started when setting-up filtering rules operations
        are not completed.

        :params instance_ref: nova.db.sqlalchemy.models.Instance object

        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def filter_defer_apply_on(self):
        """Defer application of IPTables rules."""
        pass

    def filter_defer_apply_off(self):
        """Turn off deferral of IPTables rules and apply the rules now."""
        pass

    def unfilter_instance(self, instance, network_info):
        """Stop filtering instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def set_admin_password(self, context, instance_id, new_pass=None):
        """
        Set the root password on the specified instance.

        The first parameter is an instance of nova.compute.service.Instance,
        and so the instance is being specified as instance.name. The second
        parameter is the value of the new password.
        """
        raise NotImplementedError()

    def inject_file(self, instance, b64_path, b64_contents):
        """
        Writes a file on the specified instance.

        The first parameter is an instance of nova.compute.service.Instance,
        and so the instance is being specified as instance.name. The second
        parameter is the base64-encoded path to which the file is to be
        written on the instance; the third is the contents of the file, also
        base64-encoded.
        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def change_instance_metadata(self, context, instance, diff):
        """
        Applies a diff to the instance metadata.

        This is an optional driver method which is used to publish
        changes to the instance's metadata to the hypervisor.  If the
        hypervisor has no means of publishing the instance metadata to
        the instance, then this method should not be implemented.
        """
        pass

    def inject_network_info(self, instance, nw_info):
        """inject network info for specified instance."""
        # TODO(Vek): Need to pass context in for access to auth_token
        pass

    def poll_rebooting_instances(self, timeout, instances):
        """Poll for rebooting instances

        :param timeout: the currently configured timeout for considering
                        rebooting instances to be stuck
        :param instances: instances that have been in rebooting state
                          longer than the configured timeout
        """
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def host_power_action(self, host, action):
        """Reboots, shuts down or powers up the host."""
        raise NotImplementedError()

    def host_maintenance_mode(self, host, mode):
        """Start/Stop host maintenance window. On start, it triggers
        guest VMs evacuation."""
        raise NotImplementedError()

    def set_host_enabled(self, host, enabled):
        """Sets the specified host's ability to accept new instances."""
        # TODO(Vek): Need to pass context in for access to auth_token
        raise NotImplementedError()

    def get_host_uptime(self, host):
        """Returns the result of calling "uptime" on the target host."""
        # TODO(Vek): Need to pass context in for access to auth_token
        return utils.execute('/usr/bin/uptime')[0]

    def plug_vifs(self, instance, network_info):
        """Plug VIFs into networks."""
        # TODO(Vek): Need to pass context in for access to auth_token
        pass

    def unplug_vifs(self, instance, network_info):
        """Unplug VIFs from networks."""
        raise NotImplementedError()

    def get_host_stats(self, refresh=False):
        """Return currently known host stats."""
        if refresh:
            self._update_host_stats()

        return self._host_stats

    def block_stats(self, instance_name, disk_id):
        """
        Return performance counters associated with the given disk_id on the
        given instance_name.  These are returned as [rd_req, rd_bytes, wr_req,
        wr_bytes, errs], where rd indicates read, wr indicates write, req is
        the total number of I/O requests made, bytes is the total number of
        bytes transferred, and errs is the number of requests held up due to a
        full pipeline.

        All counters are long integers.

        This method is optional.  On some platforms (e.g. XenAPI) performance
        statistics can be retrieved directly in aggregate form, without Nova
        having to do the aggregation.  On those platforms, this method is
        unused.

        Note that this function takes an instance ID.
        """
        raise NotImplementedError()

    def interface_stats(self, instance_name, iface_id):
        """
        Return performance counters associated with the given iface_id on the
        given instance_id.  These are returned as [rx_bytes, rx_packets,
        rx_errs, rx_drop, tx_bytes, tx_packets, tx_errs, tx_drop], where rx
        indicates receive, tx indicates transmit, bytes and packets indicate
        the total number of bytes or packets transferred, and errs and dropped
        is the total number of packets failed / dropped.

        All counters are long integers.

        This method is optional.  On some platforms (e.g. XenAPI) performance
        statistics can be retrieved directly in aggregate form, without Nova
        having to do the aggregation.  On those platforms, this method is
        unused.

        Note that this function takes an instance ID.
        """
        raise NotImplementedError()

    def legacy_nwinfo(self):
        """True if the driver requires the legacy network_info format."""
        # TODO(tr3buchet): update all subclasses and remove this method and
        # related helpers.
        return False

    def macs_for_instance(self, instance):
        """What MAC addresses must this instance have?

        Some hypervisors (such as bare metal) cannot do freeform virtualisation
        of MAC addresses. This method allows drivers to return a set of MAC
        addresses that the instance is to have. allocate_for_instance will take
        this into consideration when provisioning networking for the instance.

        Mapping of MAC addresses to actual networks (or permitting them to be
        freeform) is up to the network implementation layer. For instance,
        with openflow switches, fixed MAC addresses can still be virtualised
        onto any L2 domain, with arbitrary VLANs etc, but regular switches
        require pre-configured MAC->network mappings that will match the
        actual configuration.

        Most hypervisors can use the default implementation which returns None.
        Hypervisors with MAC limits should return a set of MAC addresses, which
        will be supplied to the allocate_for_instance call by the compute
        manager, and it is up to that call to ensure that all assigned network
        details are compatible with the set of MAC addresses.

        This is called during spawn_instance by the compute manager.

        :return: None, or a set of MAC ids (e.g. set(['12:34:56:78:90:ab'])).
            None means 'no constraints', a set means 'these and only these
            MAC addresses'.
        """
        return None

    def manage_image_cache(self, context, all_instances):
        """
        Manage the driver's local image cache.

        Some drivers chose to cache images for instances on disk. This method
        is an opportunity to do management of that cache which isn't directly
        related to other calls into the driver. The prime example is to clean
        the cache and remove images which are no longer of interest.
        """
        pass

    def add_to_aggregate(self, context, aggregate, host, **kwargs):
        """Add a compute host to an aggregate."""
        #NOTE(jogo) Currently only used for XenAPI-Pool
        raise NotImplementedError()

    def remove_from_aggregate(self, context, aggregate, host, **kwargs):
        """Remove a compute host from an aggregate."""
        raise NotImplementedError()

    def undo_aggregate_operation(self, context, op, aggregate,
                                 host, set_error=True):
        """Undo for Resource Pools."""
        raise NotImplementedError()

    def get_volume_connector(self, instance):
        """Get connector information for the instance for attaching to volumes.

        Connector information is a dictionary representing the ip of the
        machine that will be making the connection, the name of the iscsi
        initiator and the hostname of the machine as follows::

            {
                'ip': ip,
                'initiator': initiator,
                'host': hostname
            }
        """
        connector = {'ip': self.get_host_ip_addr(),
                     'host': CONF.host}
        if not self._initiator:
            self._initiator = self._get_iscsi_initiator()

        if self._initiator:
            connector['initiator'] = self._initiator
        else:
            LOG.warning(_("Could not determine iSCSI initiator name"),
                        instance=instance)

        return connector

    def get_available_nodes(self):
        """Returns nodenames of all nodes managed by the compute service.

        This method is for multi compute-nodes support. If a driver supports
        multi compute-nodes, this method returns a list of nodenames managed
        by the service. Otherwise, this method should return
        [hypervisor_hostname].
        """
        stats = self.get_host_stats(refresh=True)
        if not isinstance(stats, list):
            stats = [stats]
        return [s['hypervisor_hostname'] for s in stats]

    def get_per_instance_usage(self):
        """Get information about instance resource usage.

        :returns: dict of  nova uuid => dict of usage info
        """
        return {}

    def instance_on_disk(self, instance):
        """Checks access of instance files on the host.

        :param instance: instance to lookup

        Returns True if files of an instance with the supplied ID accessible on
        the host, False otherwise.

        .. note::
            Used in rebuild for HA implementation and required for validation
            of access to instance shared disk files
        """
        return False

    def register_event_listener(self, callback):
        """Register a callback to receive events.

        Register a callback to receive asynchronous event
        notifications from hypervisors. The callback will
        be invoked with a single parameter, which will be
        an instance of the nova.virt.event.Event class."""

        self._compute_event_callback = callback

    def emit_event(self, event):
        """Dispatches an event to the compute manager.

        Invokes the event callback registered by the
        compute manager to dispatch the event. This
        must only be invoked from a green thread."""

        if not self._compute_event_callback:
            LOG.debug("Discarding event %s" % str(event))
            return

        if not isinstance(event, virtevent.Event):
            raise ValueError(
                _("Event must be an instance of nova.virt.event.Event"))

        try:
            LOG.debug("Emitting event %s" % str(event))
            self._compute_event_callback(event)
        except Exception as ex:
            LOG.error(_("Exception dispatching event %(event)s: %(ex)s")
                      % locals())
