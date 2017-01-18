#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

# Configure the solaris_ipmitool driver in Ironic
#
# === Parameters
#
# [*server*]
#   Host name for AI Server
#
# [*username*]
#   Username to ssh to AI Server.
#
# [*password*]
#   (optional) If ssh_key_file or ssh_key_contents are set, this
#   config setting is used to provide the passphrase if required. If
#   an encrypted key is used, set this to the passphrase.
#
# [*port*]
#   (optional) SSH port to use
#   Defaults to '22'
#
# [*timeout*]
#   (optional) SSH socket timeout value in seconds.
#   Defaults to '10'
#
# [*deploy_interval*]
#   (optional) Interval in seconds to check AI deployment status.
#   Defaults to '10'
#
# [*derivied_manifest*]
#   (optional) Derived Manifest used for deployment.
#   Defaults to 'file:///usr/lib/ironic/ironic-manifest.ksh'
#
# [*ssh_key_file*]
#   (optional) SSH keyfile to use
#
# [*ssh_key_contents*]
#   (optional) SSH key to use
#
# [*imagecache_dirname*]
#   (optional) Default path to image cache
#   Defaults to '/var/lib/ironic/images'
#
# [*imagecache_lock_timeout*]
#   (optional) Timeout to wait when attempting to lock refcount file.
#   Defaults to '60' seconds
#
class ironic::drivers::solaris_ipmitool (
  $server,
  $username,
  $password             = undef,
  $port                 = '22',
  $timeout              = '10',
  $deploy_interval      = '10',
  $derived_manifest     = 'file:///usr/lib/ironic/ironic-manifest.ksh',
  $ssh_key_file         = undef,
  $ssh_key_contents     = undef,
  $imagecache_dirname   = '/var/lib/ironic/images',
  $imagecache_lock_timeout     = '60',
) {

  # Configure ironic.conf
  ironic_config {
    'ai/server': value                            => $server;
    'ai/username': value                          => $username;
    'ai/password': value                          => $password;
    'ai/port': value                              => $port;
    'ai/timeout': value                           => $timeout;
    'ai/deploy_interval': value                   => $deploy_intervael;
    'ai/derived_manifest': value                  => $derived_manifest;
    'ai/ssh_key_file': value                      => $ssh_key_file;
    'ai/ssh_key_contents': value                  => $ssh_key_contents;
    'solaris_ipmi/imagecache_dirname': value      => $imagecache_dirname;
    'solaris_ipmi/imagecache_lock_timeout': value => $imagecache_lock_timeout;
  }
}
