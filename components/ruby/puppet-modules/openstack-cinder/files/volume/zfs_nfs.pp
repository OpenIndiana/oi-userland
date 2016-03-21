# == Class: cinder::volume::zfs_nfs
#
# Sets up Cinder with the ZfsNfsVolumeDriver
#
# === Parameters
#
# [*nfs_servers*]
#   (Required) Description
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
#     { 'DEFAULT/nfs_option' => { 'value' => value1 } }

class cinder::volume::zfs_nfs (
  $nfs_servers,
  $nfs_round_robin = true,
  $extra_options = {},
) {

  cinder::backend::zfs_nfs { 'DEFAULT':
    nfs_servers     => $nfs_servers,
    nfs_round_robin => $nfs_round_robin,
    extra_options   => $extra_options,
  }
}
