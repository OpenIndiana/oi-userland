# == Class: cinder::backend::zfs_nfs
#
# Configures Cinder volume ZfsNfsVolumeDriver
#
# === Parameters
#
# [*nfs_servers*]
#   (Required) Description
#   Defaults to '[]'
#
# [*volume_backend_name*]
#    (optional) Allows for the volume_backend_name to be separate of $name.
#    Defaults to: $name
#
# [*nfs_round_robin*]
#   (optional) Schedule volumes round robin across NFS shares.
#   Defaults to true
#
# [*extra_options*]
#   (optional) Hash of extra options to pass to the backend stanza
#   Defaults to: {}
#   Example :
#     { 'backend_name/nfs_option' => { 'value' => value1 } }


define cinder::backend::zfs_nfs(
  $nfs_servers,
  $volume_backend_name = $name,
  $nfs_round_robin     = true,
  $extra_options       = {},
) {

  cinder_config {
    "${name}/volume_backend_name": value => $volume_backend_name;
    "${name}/volume_driver":       value => 'cinder.volume.drivers.solaris.zfs.ZfsNfsVolumeDriver';
    "${name}/nfs_servers":         value => $nfs_servers;
    "${name}/nfs_round_robin":     value => $nfs_round_robin;
  }

  create_resources('cinder_config', $extra_options)
}
