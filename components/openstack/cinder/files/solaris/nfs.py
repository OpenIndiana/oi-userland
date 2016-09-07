# vim: tabstop=4 shiftwidth=4 softtabstop=4
# Copyright (c) 2012 OpenStack LLC.
# All Rights Reserved.
#
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
Volume driver for Solaris ZFS NFS storage
"""

import os

from oslo_config import cfg
from oslo_log import log as logging
from oslo_utils import units

from cinder import exception
from cinder.i18n import _, _LI
from cinder.volume.drivers import nfs

ZFS_NFS_VERSION = '1.0.0'

LOG = logging.getLogger(__name__)

solaris_zfs_nfs_opts = [
    cfg.BoolOpt('nfs_round_robin',
                default=True,
                help=('Schedule volumes round robin across NFS shares.')),
]

CONF = cfg.CONF
CONF.register_opts(solaris_zfs_nfs_opts)


class ZfsNfsVolumeDriver(nfs.NfsDriver):
    """Local ZFS NFS volume operations."""

    driver_volume_type = 'nfs'
    driver_prefix = 'nfs'
    volume_backend_name = 'Solaris_NFS'

    def __init__(self, *args, **kwargs):
        super(ZfsNfsVolumeDriver, self).__init__(*args, **kwargs)
        self.configuration.append_config_values(solaris_zfs_nfs_opts)

        self.last_rr_pos = None

        if self.configuration.nfs_mount_options:
            LOG.warning(_("Solaris NFS driver ignores mount options"))

    def _update_volume_stats(self):
        """Retrieve volume status info."""

        stats = {}
        backend_name = self.configuration.safe_get('volume_backend_name')
        stats["volume_backend_name"] = backend_name or self.__class__.__name__
        stats["driver_version"] = ZFS_NFS_VERSION
        stats["vendor_name"] = 'Oracle'
        stats['storage_protocol'] = self.driver_volume_type

        self._ensure_shares_mounted()

        global_capacity = 0
        global_free = 0
        for share in self._mounted_shares:
            capacity, free, used = self._get_capacity_info(share)
            global_capacity += capacity
            global_free += free

        stats['total_capacity_gb'] = global_capacity / float(units.Gi)
        stats['free_capacity_gb'] = global_free / float(units.Gi)
        stats['reserved_percentage'] = 0
        stats['QoS_support'] = False
        self._stats = stats

    def _create_sparsed_file(self, path, size):
        """Creates a sparse file of a given size in GiB."""
        self._execute('/usr/bin/truncate', '-s', '%sG' % size, path)

    def _create_regular_file(self, path, size):
        """Creates a regular file of given size in GiB."""

        block_size_mb = 1
        block_count = size * units.Gi / (block_size_mb * units.Mi)

        self._execute('/usr/bin/dd', 'if=/dev/zero', 'of=%s' % path,
                      'bs=%dM' % block_size_mb,
                      'count=%d' % block_count)

    def _set_rw_permissions(self, path):
        """Sets access permissions for given NFS path.

        :param path: the volume file path.
        """
        os.chmod(path, 0o660)

    def _set_rw_permissions_for_all(self, path):
        """Sets 666 permissions for the path."""
        mode = os.stat(path).st_mode
        os.chmod(path, mode | 0o666)

    def _set_rw_permissions_for_owner(self, path):
        """Sets read-write permissions to the owner for the path."""
        mode = os.stat(path).st_mode
        os.chmod(path, mode | 0o600)

    def _delete(self, path):
        os.unlink(path)

    def _get_capacity_info(self, nfs_share):
        """Calculate available space on the NFS share.

        :param nfs_share: example 172.18.194.100:/var/nfs
        """

        mount_point = self._get_mount_point_for_share(nfs_share)

        st = os.statvfs(mount_point)
        total_available = st.f_frsize * st.f_bavail
        total_size = st.f_frsize * st.f_blocks

        du, _ = self._execute('/usr/bin/gdu', '-sb', '--apparent-size',
                              '--exclude', '*snapshot*', mount_point)
        total_allocated = float(du.split()[0])
        return total_size, total_available, total_allocated

    def _round_robin(self, sharelist):
        """
        Implement a round robin generator for share list
        """

        mylen = len(sharelist)

        if self.last_rr_pos is None:
            start_pos = 0
        else:
            start_pos = (self.last_rr_pos + 1) % mylen

        pos = start_pos
        while True:
            yield sharelist[pos], pos
            pos = (pos + 1) % mylen
            if pos == start_pos:
                break

    def _find_share(self, volume_size_in_gib):
        """Choose NFS share among available ones for given volume size.

        For instances with more than one share that meets the criteria, the
        share with the least "allocated" space will be selected.

        :param volume_size_in_gib: int size in GB
        """

        if not self._mounted_shares:
            raise exception.NfsNoSharesMounted()

        target_share = None
        if self.configuration.nfs_round_robin:
            # Round Robin volume placement on shares

            LOG.debug(_("_find_share using round robin"))

            for nfs_share, pos in self._round_robin(self._mounted_shares):
                if not self._is_share_eligible(nfs_share, volume_size_in_gib):
                    continue
                target_share = nfs_share
                self.last_rr_pos = pos
                break
        else:
            # Place volume on share with the most free space.

            LOG.debug(_("_find_share using select most free"))

            target_share_reserved = 0

            for nfs_share in self._mounted_shares:
                if not self._is_share_eligible(nfs_share, volume_size_in_gib):
                    continue
                total_size, total_available, total_allocated = \
                    self._get_capacity_info(nfs_share)
                if target_share is not None:
                    if target_share_reserved > total_allocated:
                        target_share = nfs_share
                        target_share_reserved = total_allocated
                else:
                    target_share = nfs_share
                    target_share_reserved = total_allocated

        if target_share is None:
            raise exception.NfsNoSuitableShareFound(
                volume_size=volume_size_in_gib)

        LOG.debug('Selected %s as target nfs share.', target_share)

        return target_share

    def extend_volume(self, volume, new_size):
        """Extend an existing volume to the new size."""
        LOG.info(_LI('Extending volume %s.'), volume['id'])
        extend_by = int(new_size) - volume['size']
        if not self._is_share_eligible(volume['provider_location'],
                                       extend_by):
            raise exception.ExtendVolumeError(reason='Insufficient space to'
                                              ' extend volume %s to %sG'
                                              % (volume['id'], new_size))
        path = self.local_path(volume)
        LOG.info(_LI('Resizing file to %sG.'), new_size)
        self._execute('/usr/bin/truncate', '-s', '%sG' % new_size, path)

    def set_nas_security_options(self, is_new_cinder_install):
        """Secure NAS options.

        For Solaris we always operate in a secure mode and do not
        rely on root or any rootwrap utilities.

        With RBAC we can do what we need as the cinder user.  We
        set the nas_secure_file.XXX to be true by default.  We ignore
        any conf file setting for these string vars.

        We don't ever use these nas_secure_file_XXX vars in this driver
        but we still set the value to true.  This might prevent admin/users
        from opening bugs stating we are not running in a secure mode.
        """

        self.configuration.nas_secure_file_operations = 'true'
        self.configuration.nas_secure_file_permissions = 'true'
        self._execute_as_root = False

        LOG.debug('NAS variable secure_file_permissions setting is: %s' %
                  self.configuration.nas_secure_file_permissions)

        LOG.debug('NAS variable secure_file_operations setting is: %s' %
                  self.configuration.nas_secure_file_operations)
