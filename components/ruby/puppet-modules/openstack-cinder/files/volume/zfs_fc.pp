# == Class: cinder::volume::zfs_fc
#
# Sets up Cinder with the ZFS Fibre Channel driver
#
# === Parameters
#
# [*zfs_volume_base*]
#   (optional) The ZFS path under which to create zvols for volumes.
#   Defaults to 'rpool/cinder'
#
class cinder::volume::zfs_fc (
  $zfs_volume_base = 'rpool/cinder',
) {

  cinder::backend::zfs_fc { 'DEFAULT':
    zfs_volume_base => $zfs_volume_base,
  }
}
