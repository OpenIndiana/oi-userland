#!/usr/bin/python2.7
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#

'''
Utility program for helping with the upgrade of puppet to a newer
version.  This program will take a puppet configuration file that
has been generated via the command sequence

puppet agent --genconfig > puppet.conf

and use the data in that configuration file to replace the
associated Puppet SMF user configuratable properties with the
properties that are allowed in the new version of puppet

NOTE: This file should not be included with the puppet release
'''

import os
import re
import sys
import textwrap

from lxml import etree
from optparse import OptionParser


COMMENT_PATTERN = re.compile(".*# ?(.*)")
CONFIG_VALUE_PATTERN = re.compile("([\S]+)\s*=\s*(\S*)")

DEFAULT_VALUE_STR = "The default value is "

# SMF defined property types.  For a list of
# all available types see
# /usr/share/lib/xml/dtd/service_bundle.dtd.1
TYPE_ASTRING = "astring"
TYPE_BOOLEAN = "boolean"
TYPE_INTEGER = "integer"
TYPE_HOST = "host"
TYPE_HOSTNAME = "hostname"
TYPE_NETADDRESS = "net_address"
TYPE_URI = "uri"


# Dictionary of currently defined property types to associate
# with a specified property.  Any property not defined here
# is assumed to have a property type of astring, integer,
# or boolean
PROP_TYPE = {
    'server': TYPE_HOST,
    'archive_file_server': TYPE_HOST,
    'bindaddress': TYPE_NETADDRESS,
    'ca_server': TYPE_HOST,
    'certname': TYPE_HOSTNAME,
    'couchdb_url': TYPE_URI,
    'dbserver': TYPE_HOST,
    'dns_alt_names': TYPE_HOST,
    'http_proxy_host': TYPE_HOST,
    'inventory_server': TYPE_HOST,
    'ldapserver': TYPE_HOST,
    'ldapuser': TYPE_HOSTNAME,
    'module_repository': TYPE_URI,
    'queue_source': TYPE_URI,
    'report_server': TYPE_HOST,
    'reporturl': TYPE_URI,
    'smtpserver': TYPE_HOST,
    'srv_domain': TYPE_HOST,
}

# Dictionary used to hold properites and the resulting xml code
PUPPET_CONFIG_DICT = dict()


def err(msg):
    '''Output standard error message'''
    # Duplicate the syntax of the parser.error
    sys.stderr.write("%(prog)s: error: %(msg)s\n" %
                     {"prog": os.path.basename(sys.argv[0]), "msg": msg})


def create_config_element(key, key_type, desc_text):
    '''Create a basic xml entry following the basic pattern of

        <prop_pattern name='${key}' type='${key_type}'
                required='false'>
                    <description> <loctext xml:lang='C'>
                         ${desc_text}
                    </loctext> </description>
        </prop_pattern>
    '''
    prop_pattern = etree.Element(
        "prop_pattern",
        name=key,
        type=key_type,
        required="false")
    desc = etree.SubElement(prop_pattern, "description")
    loctext = etree.SubElement(desc, "loctext")
    loctext.text = "\n%s\n\t    " % desc_text
    loctext.set('{http://www.w3.org/XML/1998/namespace}lang', 'C')
    return prop_pattern


def determine_type(key, value):
    '''Determine the xml property type to associate with the
       specified key
    '''

    # Does the key have a specified xml property type
    # already defined?
    try:
        return PROP_TYPE[key]
    except KeyError:
        pass

    # Use the value to determine the xml property type
    if value.isdigit():
        return TYPE_INTEGER
    if value.lower() in ['false', 'true']:
        return TYPE_BOOLEAN
    return TYPE_ASTRING


def process_grouping(lines):
    '''Process the lines in the list.  The last entry should be
       a 'key=value' entry
    '''

    # The last field should be a key = value pair
    # If it's not then the format of the file is not matching
    # the expected format of
    #
    # Description
    # The default value is "xxxx"
    # key = value
    #
    key_value = lines.pop()
    match = CONFIG_VALUE_PATTERN.match(key_value)
    if not match:
        raise TypeError("Last line in grouping is not in expected "
                        "format of 'key = value'\n%s" %
                        "\n".join(lines))
    key = match.group(1)
    value = match.group(2)

    default_value_line = lines.pop()
    if not default_value_line.startswith(DEFAULT_VALUE_STR):
        # Not a match.  Last line was still part of the description
        lines.append(default_value_line)

    key_type = determine_type(key, value)

    # remaining lines are the descriptor field
    desc = textwrap.fill("\n".join(lines),79)
    PUPPET_CONFIG_DICT[key] = (key, key_type, desc)


def parse_puppet_config(filename):
    '''Parse the puppet configuration file that is generated by
       puppet agent --genconfig
    '''
    parameter_list = []
    agent_check = True
    with open(filename, 'r') as f_handle:
        for line in f_handle:
            if agent_check:
                if line.startswith("[agent]"):
                    # Throw away the initial starting block code in the
                    del parameter_list[:]
                    agent_check = False
                    continue
            line = line.strip().replace("\n", "")
            if not line:
                # If parameter_list is not empty, process the data and
                # generate an xml structure
                process_grouping(parameter_list)
                # Done processing, delete all the saved entries
                del parameter_list[:]
                continue

            match = COMMENT_PATTERN.match(line)
            if match:
                line = match.group(1)
            parameter_list.append(line)
    f_handle.close()


def update_smf_file(smf_xml_file, output_file):
    '''Replace the puppet property definitions in the specified SMF
       file with those that are stored in PUPPET_CONFIG_DICT
    '''

    try:
        parser = etree.XMLParser(remove_blank_text=True)
        tree = etree.parse(smf_xml_file, parser)
        root = tree.getroot()
        template = root.find("service/template")
        puppet_desc = template.find("common_name/loctext")
        puppet_desc.text = "Puppet"

        pg_pattern = template.find("pg_pattern")
    except IOError as msg:
        err(msg)
        return -1
    except etree.XMLSyntaxError as msg:
        err(msg)
        return -1
    except NameError as msg:
        err("XML file %s does not match expected formated" % smf_xml_file)

    # Delete the pg_pattern nodes and it's children
    # This is the structure that will be rebuilt based
    # on the genconfig information that was read in
    if pg_pattern is not None:
        template.remove(pg_pattern)

    # <pg_pattern name='config' type='application' required='false'>
    pg_pattern = etree.SubElement(
        template,
        "pg_pattern",
        name="config",
        type="application",
        required="false")
    for key in sorted(PUPPET_CONFIG_DICT.iterkeys()):
        values = PUPPET_CONFIG_DICT[key]
        element = create_config_element(values[0], values[1], values[2])
        pg_pattern.append(element)

    # Write out the contents of the updated puppet SMF config file
    print "Writting out contents of new SMF configuration file to: %s" % \
        output_file
    with open(output_file, "w") as f_handle:
        f_handle.write(etree.tostring(tree, pretty_print=True))
    f_handle.close()


def option_list():
    '''Build the option list for this utility'''
    desc = "Utility for assisting in the upgrading of Solaris Puppet SMF file"
    usage = "usage: %prog -c <puppet_config_file> -s <smf_confilg_file> " \
            "[-o <output_file>]\n"
    opt_list = OptionParser(description=desc, usage=usage)

    opt_list.add_option("-c", "--config", dest="config", default=None,
                        action="store", type="string", nargs=1,
                        metavar="<puppet_config_file>",
                        help="Puppet configuration file generated via"
                             "genconfig option to puppet. i.e. "
                             "puppet agent --genconfig > puppet.conf")
    opt_list.add_option("-s", "--smf", dest="smf_xml", default=None,
                        action="store", type="string", nargs=1,
                        metavar="<smf_config_file>",
                        help="Current solaris Puppet SMF XML configuration"
                             " file. This file is located in <userland_tree>"
                             "/components/puppet/files/puppet.xml")
    opt_list.add_option("-o", "--output", dest="output", default=None,
                        action="store", type="string", nargs=1,
                        metavar="<output_file>",
                        help="The name of the new puppet.xml file ")
    return opt_list


def main():
    '''Execute this utility based on the options supplied by the user'''
    parser = option_list()

    (options, _args) = parser.parse_args()

    if not options.config or not options.smf_xml or \
            not options.output:
        err("Required options not specified")
        parser.print_help()
        sys.exit(-1)

    if not os.path.isfile(options.config):
        err("%s does not exist or is not a regular file\n"
            % options.config)
        sys.exit(-1)
    if not os.path.isfile(options.smf_xml):
        err("%s does not exist or is not a regular file\n"
            % options.smf_xml)
        sys.exit(-1)
    if os.path.exists(options.output):
        err("specified file %s already exist\n"
            % options.output)
        sys.exit(-1)

    parse_puppet_config(options.config)
    update_smf_file(options.smf_xml, options.output)

if __name__ == '__main__':
    main()
