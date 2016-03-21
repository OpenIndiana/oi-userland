# == Class: cinder::volume::zfssa_iscsi
#
# Setup Cinder wth the volume ZFSSA iSCSI driver
#
# === Parameters
#
# [*ip*]
#   (required) IP address of ZFS Storage Appliance.
#
# [*login*]
#   (required) Username to login to ZFS Storage Appliance.
#
# [*password*]
#   (required) Password for user in *login*.
#
# [*zfssa_pool*]
#   (required) Storage pool name
#
# [*zfssa_target_portal*]
#   (required) Address of the iSCSI target portal in IP:port format.
#
# [*zfssa_target_interfaces*]
#   (required) Interface names where iSCSI targets are available.
#   Example:
#   "e1000g0,vnic1"
#
# [*zfssa_project*]
#   (optional) Project name in *zfssa_pool*. Defaults to 'default'.
#
# [*zfssa_initiator*]
#   (optional) iSCSI initator name. Requires setting *zfssa_initiator_group*
#
# [*zfssa_initiator_group*]
#   (optional) iSCSI initiator group name. Required if *zfssa_initiator* is set.
#
# [*zfssa_initiator_config*]
#   (optional) iSCSI initator configuration.
#
# [*zfssa_initiator_user*]
#   (optional) CHAP user name for the iSCSI initator. Requires setting
#     *zfssa_initiator_password*
#
# [*zfssa_initiator_password*]
#   (optional) CHAP password. Required if *zfssa_initiator_user* is set.
#
# [*zfssa_target_group*]
#   (optional) iSCSI target group name.
#
# [*zfssa_target_user*]
#   (optional) CHAP user name for the iSCSI target. Requires setting
#     *zfssa_target_password*
#
# [*zfssa_target_password*]
#   (optional) CHAP password. Required if *zfssa_target_user* is set.
#
# [*zfssa_lun_volblocksize*]
#   (optional) Volume block size. Valid sizes are 512, 1k, 2k, 4k, 8k,
#     16k, 32k, 64k, 128k. Default is 8k
#
# [*zfssa_lun_sparse*]
#   (optional) Flag to enable sparse allocation (thin-provisioning).
#   Default is False.
#
# [*zfssa_lun_compression*]
#   (optional) Data compression to use on the lun. Valid values are off, lzjb,
#    gzip, gzip-2, gzip-9.
#
# [*zfssa_lun_logbias*]
#   (optional) Synchronous log bias. Valid values are latency, throughput.
#
# [*extra_options*]
#   (optional) Hash of extra options to pass to the backend stanza
#   Defaults to: {}
#   Example :
#     { 'zfssa_param' => { 'value' => value1 } }

class cinder::volume::zfssa_iscsi(
  $hostname,
  $login,
  $password,
  $zfssa_pool,
  $zfssa_target_portal,
  $zfssa_target_interfaces,
  $zfssa_project             = undef,
  $zfssa_initiator           = undef,
  $zfssa_initiator_group     = undef,
  $zfssa_initiator_config    = undef,
  $zfssa_initiator_user      = undef,
  $zfssa_initiator_password  = undef,
  $zfssa_target_group        = undef,
  $zfssa_target_user         = undef,
  $zfssa_target_password     = undef,
  $zfssa_lun_volblocksize    = undef,
  $zfssa_lun_sparse          = undef,
  $zfssa_lun_compression     = undef,
  $zfssa_lun_logbias         = undef,
  $zfssa_rest_timeout        = undef,
  $extra_options       = {},
) {

  cinder::backend::zfssa_iscsi { 'DEFAULT':
    hostname                 => $hostname,
    login                    => $login,
    password                 => $password,
    zfssa_pool               => $zfssa_pool,
    zfssa_project            => $zfssa_project,
    zfssa_lun_volblocksize   => $zfssa_lun_volblocksize,
    zfssa_lun_sparse         => $zfssa_lun_sparse,
    zfssa_lun_compression    => $zfssa_lun_compresssion,
    zfssa_lun_logbias        => $zfssa_lun_logbias,
    zfssa_initiator_group    => $zfssa_initiator_group,
    zfssa_initiator          => $zfssa_initiator,
    zfssa_initiator_user     => $zfssa_initiator_user,
    zfssa_initiator_password => $zfssa_initiator_password,
    zfssa_initiator_config   => $zfssa_initiator_config,
    zfssa_target_group       => $zfssa_target_group,
    zfssa_target_user        => $zfssa_target_user,
    zfssa_target_password    => $zfssa_target_password,
    zfssa_target_portal      => $zfssa_target_portal,
    zfssa_target_interfaces  => $zfssa_target_interfaces,
    zfssa_rest_timeout       => $zfssa_rest_timeout,
    extra_options            => $extra_options
  }
}

