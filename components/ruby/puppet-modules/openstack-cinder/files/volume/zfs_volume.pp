# == Class: cinder::volume::zfs_volume
#
# Sets up Cinder with the ZFS Volume Driver
#
# === Parameters
#
# [*zfs_volume_base*]
#   (optional) The ZFS path under which to create zvols for volumes.
#   Defaults to 'rpool/cinder'
#
class cinder::volume::zfs_volume (
  $zfs_volume_base = 'rpool/cinder',
) {

  cinder::backend::zfs_volume { 'DEFAULT':
    zfs_volume_base => $zfs_volume_base,
  }
}
