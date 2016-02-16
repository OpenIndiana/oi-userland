# == Class: neutron::plugins::evs
#
# Sets up EVS plugin for neutron server.
#
# === Parameters
#
# [*evs_controller*]
#   URI specifying an EVS controller.
#   Defaults to 'ssh://evsuser@localhost'
#
class neutron::plugins::evs (
  $evs_controller      = 'ssh://evsuser@localhost',
) {

  ini_setting { 'evs_plugin':
    ensure    => present,
    path      => '/etc/neutron/plugins/evs/evs_plugin.ini',
    section   => 'EVS',
    setting   => 'evs_controller',
    value     => $evs_controller,
  }
}
