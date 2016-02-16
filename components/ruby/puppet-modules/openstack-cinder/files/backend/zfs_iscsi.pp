# == Class: cinder::backend::zfs_iscsi
#
# Configures Cinder volume ZFSISCSIDriver
#
# === Parameters
#
# [*volume_driver*]
#   (optional) Setup cinder-volume to use Solaris ISCSI volume driver.
#   Defaults to 'cinder.volume.drivers.solaris.zfs.ZFSISCSIDriver'
#
# [*zfs_volume_base*]
#   (optional) The ZFS path under which to create zvols for volumes.
#   Defaults to 'rpool/cinder'
#
define cinder::backend::zfs_iscsi(
  $volume_driver       = 'cinder.volume.drivers.solaris.zfs.ZFSISCSIDriver',
  $zfs_volume_base     = 'rpool/cinder'
) {
  
  cinder_config {
    "${name}/volume_driver": value => $volume_driver;
    "${name}/zfs_volume_base": value => $zfs_volume_base;
    "${name}/san_is_local": value => true;
    "${name}/san_ip": value => $::ipaddress;
  }
}
