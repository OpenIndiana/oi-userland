#
# == Class: nova::compute::solaris_zones
#
# Configures nova-compute to manage Solaris Zone guests
#
# === Parameters
#
# [*glancecache_dirname*]
#   (optional) Default path to local image cache.
#   Defaults to $state_path/images
#
# [*solariszones_snapshots_directory*]
#   (optional) Location where solariszones driver will store instance
#   snapshots before uploading them to Glance
#   Defaults to $instances_path/snapshots
#
class nova::compute::solaris_zones(
    $glancecache_dirname='$state_path/images',
    $solariszones_snapshots_directory='$instances_path/snapshots',
) {

  nova_config {
    'DEFAULT/glancecache_dirname':   value => $glancecache_dirname;
    'DEFAULT/solariszones_snapshots_directory':   value => $solariszones_snapshots_directory;
    'DEFAULT/compute_driver':        value => 'solariszones.SolarisZonesDriver';
    'DEFAULT/pybasedir':             value => '/usr/lib/python2.7/vendor-packages';
    'DEFAULT/fping_path':            value => '/usr/bin/fping';
    'DEFAULT/network_driver':        value => 'nova.network.solaris_net';
  }
}
