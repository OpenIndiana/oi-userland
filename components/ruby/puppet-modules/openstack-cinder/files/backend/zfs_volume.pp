# == Class: cinder::backend::zfs_volume
#
# Configures Cinder volume ZFSVolumeDriver
#
# === Parameters
#
# [*volume_driver*]
#   (optional) Setup cinder-volume to use Solaris ZFS volume driver.
#   Defaults to 'cinder.volume.drivers.solaris.zfs.ZFSVolumeDriver'
#
# [*zfs_volume_base*]
#   (optional) The ZFS path under which to create zvols for volumes.
#   Defaults to 'rpool/cinder'
#
define cinder::backend::zfs_volume(
  $volume_driver       = 'cinder.volume.drivers.solaris.zfs.ZFSVolumeDriver',
  $zfs_volume_base     = 'rpool/cinder'
) {
  
  cinder_config {
    "${name}/volume_driver": value => $volume_driver;
    "${name}/zfs_volume_base": value => $zfs_volume_base;
    "${name}/san_is_local": value => true;
  }
}
