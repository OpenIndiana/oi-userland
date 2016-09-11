# vim: tabstop=4 shiftwidth=4 softtabstop=4

# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
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


import locale

from lxml import etree

from solaris_install.utils import encrypt_password


DTD_URL = '/usr/share/lib/xml/dtd/service_bundle.dtd.1'
DOCTYPE_STR = '<!DOCTYPE service_bundle SYSTEM "%s">' % DTD_URL


def create_ncp_defaultfixed(addrtype, linkname, netid, ip_version, ip=None,
                            route=None, nameservers=None, host_routes=None):
    """ return an etree object representing fixed (static) networking
    """
    svcbundle = etree.Element("service_bundle", type="profile",
                              name="openstack")

    # create the network/physical service profile
    physical = etree.SubElement(svcbundle, "service", version="1",
                                type="service", name="network/physical")
    instance = etree.SubElement(physical, "instance", enabled="true",
                                name="default")
    pg = etree.SubElement(instance, "property_group", type="application",
                          name="netcfg")
    etree.SubElement(pg, "propval", type="astring", name="active_ncp",
                     value="DefaultFixed")

    # create the network/install service profile
    install = etree.SubElement(svcbundle, "service", version="1",
                               type="service", name="network/install")
    instance = etree.SubElement(install, "instance", enabled="true",
                                name="default")

    if not route:
        # network/install SMF method script checks for ::0 for IPv6
        # for no-gateway case
        route = '0.0.0.0' if ip_version == 4 else '::0'

    if ip_version == 4:
        pg4 = etree.SubElement(instance, "property_group",
                               type="ipv4_interface",
                               name="install_ipv4_interface_%d" % netid)
        etree.SubElement(pg4, "propval", type="astring", name="address_type",
                         value=addrtype)

        if addrtype == "static":
            etree.SubElement(pg4, "propval", type="net_address_v4",
                             name="static_address", value=ip)
            etree.SubElement(pg4, "propval", type="astring", name="name",
                             value="%s/v4" % linkname)
            etree.SubElement(pg4, "propval", type="net_address_v4",
                             name="default_route", value=route)
        else:
            etree.SubElement(pg4, "propval", type="astring", name="name",
                             value="%s/dhcp" % linkname)
    else:
        if addrtype == "static":
            link = etree.SubElement(instance, "property_group",
                                    type="ipv6_interface",
                                    name="install_ipv6_interface_%d" % netid)
            etree.SubElement(link, "propval", type="astring",
                             name="address_type", value="addrconf")
            etree.SubElement(link, "propval", type="astring",
                             name="name", value="%s/aconf" % linkname)
            etree.SubElement(link, "propval", type="astring",
                             name="stateless", value="no")
            etree.SubElement(link, "propval", type="astring",
                             name="stateful", value="no")

            pg6 = etree.SubElement(instance, "property_group",
                                   type="ipv6_interface",
                                   name="install_ipv6_interface_%d_1" % netid)
            etree.SubElement(pg6, "propval", type="astring",
                             name="address_type", value="static")
            etree.SubElement(pg6, "propval", type="net_address_v6",
                             name="static_address", value=ip)
            etree.SubElement(pg6, "propval", type="astring", name="name",
                             value="%s/v6" % linkname)
            etree.SubElement(pg6, "propval", type="net_address_v6",
                             name="default_route", value=route)
        else:
            pg6 = etree.SubElement(instance, "property_group",
                                   type="ipv6_interface",
                                   name="install_ipv6_interface_%d" % netid)
            etree.SubElement(pg6, "propval", type="astring",
                             name="address_type", value="addrconf")
            etree.SubElement(pg6, "propval", type="astring", name="name",
                             value="%s/dhcp" % linkname)
            etree.SubElement(pg6, "propval", type="astring",
                             name="stateless", value="yes")
            etree.SubElement(pg6, "propval", type="astring",
                             name="stateful", value="yes")

    if host_routes:
        # create the host-routes profile
        for i, host_route in enumerate(host_routes):
            hr_dest = host_route['cidr']
            hr_gw = host_route['gateway']['address']
            hr_pg_name = "route_%d_%d" % (netid, i)
            hr_ip_version = host_route['gateway']['version']
            if hr_ip_version == 4:
                hr_pg_type = "ipv4_route"
                hr_pval_type = "net_address_v4"
            else:
                hr_pg_type = "ipv6_route"
                hr_pval_type = "net_address_v6"
            pg = etree.SubElement(instance, "property_group", type=hr_pg_type,
                                  name=hr_pg_name)
            etree.SubElement(pg, "propval", type=hr_pval_type,
                             name="destination", value=hr_dest)
            etree.SubElement(pg, "propval", type=hr_pval_type,
                             name="gateway", value=hr_gw)

    # create DNS profile for static configurations
    if addrtype == "static" and nameservers:
        dns = etree.SubElement(svcbundle, "service", version="1",
                               type="service", name="network/dns/client")
        etree.SubElement(dns, "instance", enabled="true", name="default")
        pg = etree.SubElement(dns, "property_group", type="application",
                              name="config")
        prop = etree.SubElement(pg, "property", type="net_address",
                                name="nameserver")
        proplist = etree.SubElement(prop, "net_address_list")

        if isinstance(nameservers, str):
            etree.SubElement(proplist, "value_node", value=nameservers)
        elif isinstance(nameservers, list):
            for entry in nameservers:
                etree.SubElement(proplist, "value_node", value=entry)

        search = etree.SubElement(pg, "property", type="astring",
                                  name="search")
        etree.SubElement(search, "astring_list")

    return svcbundle


def create_default_root_account(expire=None, sshkey=None, password=None):
    """ return an etree object representing the root account
    """
    svcbundle = etree.Element("service_bundle", type="profile",
                              name="openstack")
    service = etree.SubElement(svcbundle, "service", version="1",
                               type="service", name="system/config-user")
    instance = etree.SubElement(service, "instance", enabled="true",
                                name="default")
    root_pg = etree.SubElement(instance, "property_group", type="application",
                               name="root_account")
    etree.SubElement(root_pg, "propval", type="astring", name="type",
                     value="normal")

    if password is not None:
        etree.SubElement(root_pg, "propval", type="astring", name="password",
                         value=password)
    else:
        etree.SubElement(root_pg, "propval", type="astring", name="password",
                         value='NP')

    if expire is not None:
        etree.SubElement(root_pg, "propval", type="astring", name="expire",
                         value=expire)

    if sshkey is not None:
        prop = etree.SubElement(root_pg, "property", type="astring",
                                name="ssh_public_keys")
        alist = etree.SubElement(prop, "astring_list")
        etree.SubElement(alist, "value_node", value=sshkey)

    return svcbundle


def create_root_ssh_keys(key):
    """ return an etree object to set a public SSH key for root
    """
    svcbundle = etree.Element("service_bundle", type="profile",
                              name="openstack")
    service = etree.SubElement(svcbundle, "service", version="1",
                               type="service", name="system/config-user")
    instance = etree.SubElement(service, "instance", enabled="true",
                                name="default")
    root_pg = etree.SubElement(instance, "property_group", type="application",
                               name="root_account")
    prop = etree.SubElement(root_pg, "property", type="astring",
                            name="ssh_public_keys")
    alist = etree.SubElement(prop, "astring_list")
    etree.SubElement(alist, "value_node", value=key)
    return svcbundle


def create_hostname(name):
    """ return an etree object representing the instance's hostname
    """

    svcbundle = etree.Element("service_bundle", type="profile",
                              name="openstack")
    service = etree.SubElement(svcbundle, "service", version="1",
                               type="service", name="system/identity")
    instance = etree.SubElement(service, "instance", enabled="true",
                                name="node")
    pg = etree.SubElement(instance, "property_group", type="application",
                          name="config")
    etree.SubElement(pg, "propval", type="astring", name="nodename",
                     value=name)
    etree.SubElement(pg, "propval", type="boolean",
                     name="ignore_dhcp_hostname", value="true")

    return svcbundle


def create_sc_profile(path, tree):
    """ create a file containing the proper XML headers and encoding for a
    given etree object
    """
    encoding = locale.getpreferredencoding()
    if encoding == "646":
        # The C locale on Solaris is returned as '646'.  Set it to 'US-ASCII'
        # instead
        encoding = 'US-ASCII'

    xml_str = etree.tostring(tree, pretty_print=True, encoding=encoding,
                             xml_declaration=True, doctype=DOCTYPE_STR)

    # insert a comment just under the doctype line
    comment = etree.Comment(" Auto-generated by OpenStack Nova ")
    xml_list = xml_str.split("\n")
    xml_list.insert(2, etree.tostring(comment))
    xml_str = "\n".join(xml_list)

    with open(path, "w+") as fh:
        fh.write(xml_str)
