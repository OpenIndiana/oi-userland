# vim: tabstop=4 shiftwidth=4 softtabstop=4
# Copyright (c) 2012 OpenStack LLC.
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
"""
Drivers for Solaris ZFS operations in local and iSCSI modes
"""

import abc
import os

from oslo.config import cfg

from cinder import exception
from cinder import flags
from cinder.image import image_utils
from cinder.openstack.common import log as logging
from cinder.volume import driver

from solaris_install.target.size import Size

FLAGS = flags.FLAGS
LOG = logging.getLogger(__name__)

solaris_zfs_opts = [
    cfg.StrOpt('zfs_volume_base',
               default='rpool/cinder',
               help='The base dataset for ZFS volumes.'), ]

FLAGS.register_opts(solaris_zfs_opts)


class ZFSVolumeDriver(driver.VolumeDriver):
    """Local ZFS volume operations."""
    protocol = 'local'

    def __init__(self, *args, **kwargs):
        super(ZFSVolumeDriver, self).__init__(*args, **kwargs)
        self.configuration.append_config_values(solaris_zfs_opts)

    def check_for_setup_error(self):
        """Check the setup error."""
        pass

    def create_volume(self, volume):
        """Create a volume."""
        size = '%sG' % volume['size']
        zfs_volume = self._get_zfs_volume_name(volume)

        # Create a ZFS volume
        cmd = ['/usr/sbin/zfs', 'create', '-V', size, zfs_volume]
        self._execute(*cmd)
        LOG.debug(_("Created ZFS volume '%s'") % volume['name'])

    def create_volume_from_snapshot(self, volume, snapshot):
        """Create a cloned volume from a snapshot."""
        if volume['size'] != snapshot['volume_size']:
            exception_message = (_("Could not create volume '%s' because "
                                   "its volume size of '%s' is different "
                                   "from that of the snapshot, '%s'.")
                                 % (volume['name'], volume['size'],
                                    snapshot['volume_size']))
            raise exception.VolumeBackendAPIException(data=exception_message)

        # Create a ZFS clone
        zfs_snapshot = self._get_zfs_snap_name(snapshot)
        zfs_volume = self._get_zfs_volume_name(volume)
        cmd = ['/usr/sbin/zfs', 'clone', zfs_snapshot, zfs_volume]
        self._execute(*cmd)

        LOG.debug(_("Created cloned volume '%s'") % volume['name'])

    def create_cloned_volume(self, volume, src_vref):
        """Create a clone of the specified volume."""
        if volume['size'] != src_vref['size']:
            exception_message = (_("Could not clone volume '%s' because "
                                   "its volume size of '%s' is different "
                                   "from that of the source volume, '%s'.")
                                 % (volume['name'], volume['size'],
                                    src_vref['size']))
            raise exception.VolumeBackendAPIException(data=exception_message)

        src_volume_name = src_vref['name']
        volume_name = volume['name']
        tmp_snapshot = {'volume_name': src_volume_name,
                        'name': 'tmp-snapshot-%s' % volume['id']}
        self.create_snapshot(tmp_snapshot)

        # Create a ZFS clone
        zfs_snapshot = self._get_zfs_snap_name(tmp_snapshot)
        zfs_volume = self._get_zfs_volume_name(volume)
        cmd = ['/usr/sbin/zfs', 'clone', zfs_snapshot, zfs_volume]
        self._execute(*cmd)

        LOG.debug(_("Created cloned volume '%s' from source volume '%s'")
                  % (volume_name, src_volume_name))

    def delete_volume(self, volume):
        """Delete a volume.

        Firstly, the volume should be checked if it is a cloned one. If yes,
        its parent snapshot with prefix 'tmp-snapshot-' should be deleted as
        well after it is removed.
        """
        zvol = self._get_zvol_path(volume)
        if not os.path.exists(zvol):
            LOG.debug(_("The volume path '%s' doesn't exist") % zvol)
            return

        zfs_volume = self._get_zfs_volume_name(volume)
        origin_snapshot = self._get_zfs_property('origin', zfs_volume)
        tmp_cloned_vol = False

        # Check if it is the temporary snapshot created for the cloned volume
        if origin_snapshot.startswith(self.configuration.zfs_volume_base):
            prop_type = self._get_zfs_property('type', origin_snapshot)
            tmp_snap_prefix = 'tmp-snapshot-%s' % volume['id']
            if prop_type == 'snapshot' and tmp_snap_prefix in origin_snapshot:
                tmp_cloned_vol = True

        cmd = ['/usr/sbin/zfs', 'destroy', zfs_volume]
        self._execute(*cmd)
        LOG.debug(_("Deleted volume '%s'") % volume['name'])

        if tmp_cloned_vol:
            self._execute('/usr/sbin/zfs', 'destroy', origin_snapshot)
            LOG.debug(_("Deleted parent snapshot '%s' of volume '%s'")
                      % (origin_snapshot, volume['name']))

    def create_snapshot(self, snapshot):
        """Create a snapshot."""
        cmd = ['/usr/sbin/zfs', 'snapshot', self._get_zfs_snap_name(snapshot)]
        self._execute(*cmd)

        LOG.debug(_("Created snapshot '%s'") % snapshot['name'])

    def delete_snapshot(self, snapshot):
        """Delete a snapshot."""
        cmd = ['/usr/sbin/zfs', 'destroy', self._get_zfs_snap_name(snapshot)]
        self._execute(*cmd)

        LOG.debug(_("Deleted snapshot '%s'") % snapshot['name'])

    def ensure_export(self, context, volume):
        """Synchronously recreate an export for a logical volume."""
        pass

    def create_export(self, context, volume):
        """Export the volume."""
        pass

    def remove_export(self, context, volume):
        """Remove an export for a volume."""
        pass

    def initialize_connection(self, volume, connector):
        """Initialize the connection and returns connection info."""
        volume_path = '%s/volume-%s' % (self.configuration.zfs_volume_base,
                                        volume['id'])
        return {
            'driver_volume_type': 'local',
            'volume_path': volume_path
        }

    def terminate_connection(self, volume, connector, **kwargs):
        """Disconnection from the connector."""
        pass

    def attach_volume(self, context, volume_id, instance_uuid, mountpoint):
        """ Callback for volume attached to instance."""
        pass

    def detach_volume(self, context, volume_id):
        """ Callback for volume detached."""
        pass

    def get_volume_stats(self, refresh=False):
        """Get volume status."""

        if refresh:
            self._update_volume_stats()

        return self._stats

    def copy_image_to_volume(self, context, volume, image_service, image_id):
        """Fetch the image from image_service and write it to the volume."""
        image_utils.fetch_to_raw(context,
                                 image_service,
                                 image_id,
                                 self.local_path(volume))

    def copy_volume_to_image(self, context, volume, image_service, image_meta):
        """Copy the volume to the specified image."""
        image_utils.upload_volume(context,
                                  image_service,
                                  image_meta,
                                  self.local_path(volume))

    def _get_zfs_property(self, prop, dataset):
        """Get the value of property for the dataset."""
        (out, _err) = self._execute('/usr/sbin/zfs', 'get', '-H', '-o',
                                    'value', prop, dataset)
        return out.rstrip()

    def _get_zfs_snap_name(self, snapshot):
        """Get the snapshot path."""
        return "%s/%s@%s" % (self.configuration.zfs_volume_base,
                             snapshot['volume_name'], snapshot['name'])

    def _get_zfs_volume_name(self, volume):
        """Add the pool name to get the ZFS volume."""
        return "%s/%s" % (self.configuration.zfs_volume_base,
                          volume['name'])

    def _get_zvol_path(self, volume):
        """Get the ZFS volume path."""
        return "/dev/zvol/rdsk/%s" % self._get_zfs_volume_name(volume)

    def _update_volume_stats(self):
        """Retrieve volume status info."""

        LOG.debug(_("Updating volume status"))
        stats = {}
        backend_name = self.configuration.safe_get('volume_backend_name')
        stats["volume_backend_name"] = backend_name or self.__class__.__name__
        stats["storage_protocol"] = self.protocol
        stats["driver_version"] = '1.0'
        stats["vendor_name"] = 'Oracle'
        stats['QoS_support'] = False

        dataset = self.configuration.zfs_volume_base
        used_size = self._get_zfs_property('used', dataset)
        avail_size = self._get_zfs_property('avail', dataset)
        stats['total_capacity_gb'] = \
            (Size(used_size) + Size(avail_size)).get(Size.gb_units)
        stats['free_capacity_gb'] = Size(avail_size).get(Size.gb_units)
        stats['reserved_percentage'] = self.configuration.reserved_percentage

        self._stats = stats


class STMFDriver(ZFSVolumeDriver):
    """Abstract base class for common COMSTAR operations."""
    __metaclass__ = abc.ABCMeta

    def __init__(self, *args, **kwargs):
        super(STMFDriver, self).__init__(*args, **kwargs)

    def _check_target(self, target, protocol):
        """Verify if the target exists."""
        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-target')

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("Target:"):
                if target == line.split()[-1]:
                    break
        else:
            LOG.debug(_("The target '%s' doesn't exist") % target)
            return False

        # Verify if the target protocol is iSCSI.
        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-target',
                                    '-v', target)

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("Target:"):
                tmp_target = line.split()[-1]
            if line.startswith("Operational"):
                status = line.split()[-1]
            if line.startswith("Protocol"):
                tmp_protocol = line.split()[-1]
                break

        return (tmp_target == target and status == 'Online' and
                tmp_protocol == protocol)

    def _check_tg(self, tg):
        """Check if the target group exists."""
        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-tg')
        found = False

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("Target"):
                if tg == line.split()[-1]:
                    found = True
                    break
        else:
            LOG.debug(_("The target group '%s' doesn't exist") % tg)

        return found

    def _get_luid(self, volume):
        """Get the LU corresponding to the volume."""
        zvol = self._get_zvol_path(volume)

        (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-lu', '-v')
        luid = None

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("LU Name:"):
                luid = line.split()[-1]
            if line.startswith("Alias") and line.split()[-1] == zvol:
                break
        else:
            luid = None

        if luid is not None:
            LOG.debug(_("Got the LU '%s'") % luid)
        else:
            LOG.debug(_("Failed to get LU for volume '%s'")
                      % volume['name'])
        return luid

    def _get_view_and_lun(self, lu):
        """Check the view entry of the LU and then get the lun and view."""
        view_and_lun = {}
        view_and_lun['valid_value'] = False
        try:
            (out, _err) = self._execute('/usr/sbin/stmfadm', 'list-view',
                                        '-l', lu)
        except exception.ProcessExecutionError as error:
            if 'no views found' in error.stderr:
                LOG.debug(_("No view is found for LU '%s'") % lu)
                return view_and_lun
            else:
                raise

        for line in [l.strip() for l in out.splitlines()]:
            if line.startswith("View Entry:"):
                view_and_lun['view'] = line.split()[-1]
                view_and_lun['valid_value'] = True
            if line.startswith("LUN"):
                view_and_lun['lun'] = line.split()[-1]

        if view_and_lun['lun'] == 'Auto':
            view_and_lun['lun'] = 0

        LOG.debug(_("The view_entry and LUN of LU '%s' are '%s' and '%s'.")
                  % (lu, view_and_lun['view'], view_and_lun['lun']))

        return view_and_lun


class ZFSISCSIDriver(STMFDriver, driver.ISCSIDriver):
    """ZFS volume operations in iSCSI mode."""
    protocol = 'iSCSI'

    def __init__(self, *args, **kwargs):
        super(ZFSISCSIDriver, self).__init__(*args, **kwargs)

    def create_export(self, context, volume):
        """Export the volume."""
        zvol = self._get_zvol_path(volume)

        # Create a Logical Unit (LU)
        self._execute('/usr/sbin/stmfadm', 'create-lu', zvol)
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to create LU for volume '%s'")
                   % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        # Create a target group and a target belonging to the target group
        target_group = 'tg-%s' % volume['name']
        self._execute('/usr/sbin/stmfadm', 'create-tg', target_group)

        target_name = '%s%s' % (self.configuration.iscsi_target_prefix,
                                volume['name'])
        self._execute('/usr/sbin/stmfadm', 'add-tg-member', '-g',
                      target_group, target_name)

        self._execute('/usr/sbin/itadm', 'create-target', '-n', target_name)
        assert self._check_target(target_name, 'iSCSI')

        # Add a logical unit view entry
        if luid is not None:
            self._execute('/usr/sbin/stmfadm', 'add-view', '-t',
                          target_group, luid)

    def remove_export(self, context, volume):
        """Remove an export for a volume.

        All of the related elements about the volume, including the
        target, target group, view entry and lu, are deleted.
        """
        luid = self._get_luid(volume)
        target_group = 'tg-%s' % volume['name']
        target_name = '%s%s' % (self.configuration.iscsi_target_prefix,
                                volume['name'])

        # Remove the view entry
        if luid is not None:
            view_lun = self._get_view_and_lun(luid)
            if view_lun['valid_value']:
                self._execute('/usr/sbin/stmfadm', 'remove-view', '-l',
                              luid, view_lun['view'])

        # Remove the target and its target group
        if self._check_target(target_name, 'iSCSI'):
            self._execute('/usr/sbin/stmfadm', 'offline-target', target_name)
            self._execute('/usr/sbin/itadm', 'delete-target', '-f',
                          target_name)

        if self._check_tg(target_group):
            self._execute('/usr/sbin/stmfadm', 'delete-tg', target_group)

        # Remove the LU
        if luid is not None:
            self._execute('/usr/sbin/stmfadm', 'delete-lu', luid)

    def _get_iscsi_properties(self, volume):
        """Get iSCSI configuration

        Now we use the discovery address as the default approach to add
        objects into the initiator. A discovery address is an IP address:port
        combination used in a SendTargets discovery session in the initiator.

        :target_discovered:    boolean indicating whether discovery was used
        :target_iqn:           the IQN of the iSCSI target
        :target_portal:        the portal of the iSCSI target
        :target_lun:           the lun of the iSCSI target
        :volume_id:            the id of the volume

        :auth_method:, :auth_username:, :auth_password:
            the authentication details. Right now, either auth_method is not
            present meaning no authentication, or auth_method == `CHAP`
            meaning use CHAP with the specified credentials.
        """
        luid = self._get_luid(volume)
        if not luid:
            msg = (_("Failed to get LU for volume '%s'") % volume['name'])
            raise exception.VolumeBackendAPIException(data=msg)

        target_name = '%s%s' % (self.configuration.iscsi_target_prefix,
                                volume['name'])
        properties = {}

        properties['target_discovered'] = True
        properties['target_iqn'] = target_name
        properties['target_portal'] = ('%s:%d' %
                                       (self.configuration.iscsi_ip_address,
                                       self.configuration.iscsi_port))
        view_lun = self._get_view_and_lun(luid)
        if view_lun['valid_value']:
            properties['target_lun'] = view_lun['lun']
        properties['volume_id'] = volume['id']

        auth = volume['provider_auth']
        if auth:
            (auth_method, auth_username, auth_secret) = auth.split()
            properties['auth_method'] = auth_method
            properties['auth_username'] = auth_username
            properties['auth_password'] = auth_secret

        return properties

    def initialize_connection(self, volume, connector):
        """Initialize the connection and returns connection info.

        The iSCSI driver returns a driver_volume_type of 'iscsi'.
        The format of the driver data is defined in _get_iscsi_properties.
        Example return value::

        {
            'driver_volume_type': 'iscsi'
            'data': {
                'target_discovered': True,
                'target_iqn':
                'iqn.1986-03.com.sun:02:200720c6-9bca-cb8f-c061-d427d7ab978f',
                'target_portal': '127.0.0.1:3260',
                'volume_id': 1,
            }
        }

        """
        initiator_name = connector['initiator']
        volume_name = volume['name']
        LOG.debug(_('Connecting the initiator %(initiator_name)s '
                    'for volume %(volume_name)s')
                  % {'initiator_name': initiator_name,
                     'volume_name': volume_name})
        iscsi_properties = self._get_iscsi_properties(volume)

        return {
            'driver_volume_type': 'iscsi',
            'data': iscsi_properties
        }

    def terminate_connection(self, volume, connector, **kwargs):
        """Disconnection from the connector."""
        initiator_name = connector['initiator']
        volume_name = volume['name']

        LOG.debug(_('Disconnecting the initiator %(initiator_name)s '
                    'for volume %(volume_name)s')
                  % {'initiator_name': initiator_name,
                     'volume_name': volume_name})
