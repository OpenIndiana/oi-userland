# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright 2014 OpenStack Foundation
# All Rights Reserved.
#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.

import jinja2
import netaddr
from oslo.config import cfg
import six

from neutron.agent.linux import utils
from neutron.common import constants
from neutron.openstack.common import log as logging


LOG = logging.getLogger(__name__)

OPTS = [
    cfg.StrOpt('ra_confs',
               default='$state_path/ra',
               help=_('Location to store IPv6 RA config files')),
]

cfg.CONF.register_opts(OPTS)

NDP_SMF_FMRI = 'svc:/network/routing/ndp:default'

CONFIG_TEMPLATE = jinja2.Template("""if {{ interface_name }} \
   AdvSendAdvertisements on \
   MinRtrAdvInterval 3 \
   MaxRtrAdvInterval 10 \
   {% if ra_mode == constants.DHCPV6_STATELESS %}
   AdvOtherConfigFlag on \
   {% endif %}

   {% if ra_mode == constants.DHCPV6_STATEFUL %}
   AdvManagedFlag on
   {% endif %}

{% if ra_mode in (constants.IPV6_SLAAC, constants.DHCPV6_STATELESS) %}
prefix {{ prefix }} {{ interface_name }} \
        AdvOnLinkFlag on \
        AdvAutonomousFlag on
{% endif %}
""")


def _generate_ndpd_conf(router_id, router_ports, dev_name_helper):
    ndpd_conf = utils.get_conf_file_name(cfg.CONF.ra_confs, router_id,
                                         'ndpd.conf', True)
    buf = six.StringIO()
    for p in router_ports:
        prefix = p['subnet']['cidr']
        if netaddr.IPNetwork(prefix).version == 6:
            interface_name = dev_name_helper(p['id'])
            ra_mode = p['subnet']['ipv6_ra_mode']
            buf.write('%s' % CONFIG_TEMPLATE.render(
                ra_mode=ra_mode,
                interface_name=interface_name,
                prefix=prefix,
                constants=constants))

    utils.replace_file(ndpd_conf, buf.getvalue())
    return ndpd_conf


def _refresh_ndpd(ndpd_conf):
    cmd = ['/usr/sbin/svccfg', '-s', NDP_SMF_FMRI, 'setprop',
           'routing/config_file', '=', ndpd_conf]
    utils.execute(cmd)
    # ndpd SMF service doesn't support refresh method, so we
    # need to restart
    cmd = ['/usr/sbin/svcadm', 'restart', NDP_SMF_FMRI]
    utils.execute(cmd)
    LOG.debug(_("ndpd daemon has been refreshed to re-read the "
                "configuration file"))


def enable_ipv6_ra(router_id, router_ports, dev_name_helper):
    for p in router_ports:
        if netaddr.IPNetwork(p['subnet']['cidr']).version == 6:
            break
    else:
        disable_ipv6_ra(router_id)
        return
    LOG.debug("enabling ndpd for router %s", router_id)
    ndpd_conf = _generate_ndpd_conf(router_id, router_ports, dev_name_helper)
    _refresh_ndpd(ndpd_conf)


def disable_ipv6_ra(router_id):
    LOG.debug("disabling ndpd for router %s", router_id)
    utils.remove_conf_files(cfg.CONF.ra_confs, router_id)
    _refresh_ndpd("")
