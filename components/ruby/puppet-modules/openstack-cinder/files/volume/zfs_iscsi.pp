# == Class: cinder::volume::zfs_iscsi
#
# Sets up Cinder with the ZFS iSCSI driver
#
# === Parameters
#
# [*zfs_volume_base*]
#   (optional) The ZFS path under which to create zvols for volumes.
#   Defaults to 'rpool/cinder'
#
class cinder::volume::zfs_iscsi (
  $zfs_volume_base = 'rpool/cinder',
) {

  cinder::backend::zfs_iscsi { 'DEFAULT':
    zfs_volume_base => $zfs_volume_base,
  }
}
