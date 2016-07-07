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
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
"""
DDU functions
"""

import DDU.ddu_errors as ddu_errors
from DDU.ddu_repo import ddu_repo_object
from DDU.ddu_package import ddu_package_object
from DDU.ddu_devdata import ddu_dev_data

import commands
from xml.dom import minidom
from xml.dom import Node
import os
import sys

ABSPATH = '/usr/ddu'
DEVICE_PARENT_FIELD = 1
DEVICE_DRIVER_NAME_FIELD = 6

def ddu_build_repo_list(ips_repo_list):
    """Build a list of repository objects to be used by ddu_package_lookup()
       Arg:
       ips_repo_list:a list of tuple which represent a IPS package repository
                      each tuple has a repo name and repo url.
       Return:
       repo_obj_list: a list of ddu_repo_objects, one object per repository.

       Dependency:
       ${ddu directory}/scripts/pkg_relate.sh
    """
    if not isinstance(ips_repo_list, list) or len(ips_repo_list) == 0:
        raise ddu_errors.RepositoryNotFoundException(
                         "Arg is not a non-empty ips_repo_list")
    else:
        repo_obj_list = []
        for repo_name, repo_url in ips_repo_list:
        #If repo name is already in your system repo list,
        #Add it directly in repo_obj_list repo_obj_list
            status, output = commands.getstatusoutput(
                        "%s/scripts/pkg_relate.sh list %s 2>/dev/null" %
                        (ABSPATH,repo_name))
            repo_exist = False
            if (status == 0):
                split_lines = output.splitlines()

                for split_lineoutput in split_lines:
                    split_output = split_lineoutput.split('\t')
	            # Strip any trailing / off all repo URL entries (index 1)
                    repo_url = repo_url.rstrip("/")
                    split_output[1] = split_output[1].rstrip("/")

                    if split_output[0] == repo_name and \
                       split_output[1] == repo_url:
                        repo_exist = True

            if repo_exist == True:
                repo_obj_list.append(ddu_repo_object(repo_name, repo_url))
            else:
                status, output = commands.getstatusoutput( \
                                        '%s/scripts/pkg_relate.sh add %s %s' %
                                        (ABSPATH,repo_name,repo_url))
                if status == 0:
                    repo_obj_list.append(ddu_repo_object(repo_name, repo_url))
                else:
                    print >> sys.__stderr__, output
                    raise ddu_errors.RepositoryCreatedException(repo_url)
    if len(repo_obj_list)  == 0:
        raise ddu_errors.RepositoryNotFoundException("No repositories found")
    return repo_obj_list


def ddu_devscan(return_missing_only = True, device_type = "all"):
    """
    Do a device scan. Returns either devices missing their driver,
    or all devices
    Dependency:
    ${ddu directory}/scripts/probe.sh
    ${ddu directory}/scripts/det_info.sh
    """
    status, output = commands.getstatusoutput(
                "%s/scripts/probe.sh init" % ABSPATH)
    if status != 0:
        print >> sys.__stderr__, output
        raise ddu_errors.DevScanNotStart("Error initializing for scan")
    drv_list = []
    #find all drivers list
    if str(device_type).find("all") >= 0:
        systemxml = minidom.parse('%s/data/hdd.xml' % ABSPATH)
        category = systemxml.getElementsByTagName('category')
        for catelist in category:
            probehook = catelist.getElementsByTagName('probe')[0]
            for probedata in probehook.childNodes:
                if probedata.nodeType == Node.TEXT_NODE:
                    probecmd = ABSPATH+'/'+probedata.data
                    data_type = str(probedata.data).split(' ')[1]
                #performing scanning script by hardware category
                status, output = commands.getstatusoutput(probecmd)
                if status != 0:
                    print >> sys.__stderr__, output
                    raise ddu_errors.DevScanNotStart()

                if len(output) > 0:
                    output_lines = output.splitlines()
                    for line in output_lines:
                        component_disc = line.split(':')
                        #find missing drivers list
                        if return_missing_only == True:
                        #only handle missing driver contrller in
                        #missing driver list
                            if(component_disc[DEVICE_PARENT_FIELD] == '') and \
                  (component_disc[DEVICE_DRIVER_NAME_FIELD] == 'unknown'):
                                drv_list.append(
                                         ddu_dev_data(
                                         item_id = component_disc[0],
                                         parent_item_id = component_disc[1],
                                         description = component_disc[2],
                                         device_id = component_disc[3],
                                         class_code = component_disc[4],
                                         pci_path = component_disc[5],
                                         driver_name = "",
                                         instance_id = component_disc[7],
                                         attach_status = component_disc[8],
                                         vendor_id = component_disc[9],
                                         device_type = str(data_type))
                                         )
                        #find all drivers list
                        else:
                            if component_disc[DEVICE_PARENT_FIELD] == '':
                                if component_disc[DEVICE_DRIVER_NAME_FIELD] \
                                                              == 'unknown':
                                    drv_list.append(
                                         ddu_dev_data(
                                         item_id = component_disc[0],
                                         parent_item_id = component_disc[1],
                                         description = component_disc[2],
                                         device_id = component_disc[3],
                                         class_code = component_disc[4],
                                         pci_path = component_disc[5],
                                         driver_name = "",
                                         instance_id = component_disc[7],
                                         attach_status = component_disc[8],
                                         vendor_id=component_disc[9],
                                         device_type=str(data_type))
                                         )
                                else:
                                    drv_list.append(
                                         ddu_dev_data(
                                         item_id = component_disc[0],
                                         parent_item_id = component_disc[1],
                                         description = component_disc[2],
                                         device_id = component_disc[3],
                                         class_code = component_disc[4],
                                         pci_path = component_disc[5],
                                         driver_name = component_disc[6],
                                         instance_id = component_disc[7],
                                         attach_status = component_disc[8],
                                         vendor_id = component_disc[9],
                                         device_type = str(data_type))
                                         )
                            else:
                                drv_list.append(
                                         ddu_dev_data(
                                         item_id = component_disc[0],
                                         parent_item_id = component_disc[1],
                                         description = component_disc[2],
                                         device_id = "",
                                         class_code = "",
                                         pci_path = component_disc[4],
                                         driver_name = component_disc[5],
                                         instance_id = component_disc[6],
                                         attach_status = component_disc[7],
                                         vendor_id="",
                                         device_type=str(data_type))
                                         )

    #find specific driver list
    else:
        device_scan_cndi = device_type.split(',')
        for device_scan_index in device_scan_cndi:
            status, output = commands.getstatusoutput(
                                      "%s/scripts/probe.sh %s" %
                                      (ABSPATH,device_scan_index))
            if status != 0:
                print >> sys.__stderr__, output
                raise ddu_errors.DevScanNotStart()
            if len(output) > 0:
                output_lines = output.splitlines()
                for line in output_lines:
                    component_disc = line.split(':')
                    #find missing drivers list
                    if return_missing_only == True:
                        #only handle missing driver contrller in
                        #missing driver list
                        if(component_disc[DEVICE_PARENT_FIELD] == '') and \
                          (component_disc[DEVICE_DRIVER_NAME_FIELD] == \
                          'unknown'):
                            drv_list.append(
                                 ddu_dev_data(
                                 item_id = component_disc[0],
                                 parent_item_id = component_disc[1],
                                 description = component_disc[2],
                                 device_id = component_disc[3],
                                 class_code = component_disc[4],
                                 pci_path = component_disc[5],
                                 driver_name = "",
                                 instance_id = component_disc[7],
                                 attach_status = component_disc[8],
                                 vendor_id = component_disc[9],
                                 device_type = str(device_scan_index))
                                 )
                    #find all drivers list
                    else:
                        if component_disc[DEVICE_PARENT_FIELD] == '':
                            if component_disc[DEVICE_DRIVER_NAME_FIELD] == \
                                                                  'unknown':
                                drv_list.append(
                                     ddu_dev_data(
                                     item_id = component_disc[0],
                                     parent_item_id = component_disc[1],
                                     description = component_disc[2],
                                     device_id = component_disc[3],
                                     class_code = component_disc[4],
                                     pci_path = component_disc[5],
                                     driver_name = "",
                                     instance_id = component_disc[7],
                                     attach_status = component_disc[8],
                                     vendor_id = component_disc[9],
                                     device_type = str(device_scan_index))
                                     )
                            else:
                                drv_list.append(
                                     ddu_dev_data(
                                     item_id = component_disc[0],
                                     parent_item_id = component_disc[1],
                                     description = component_disc[2],
                                     device_id = component_disc[3],
                                     class_code = component_disc[4],
                                     pci_path = component_disc[5],
                                     driver_name = component_disc[6],
                                     instance_id = component_disc[7],
                                     attach_status = component_disc[8],
                                     vendor_id = component_disc[9],
                                     device_type=str(device_scan_index))
                                     )
                        else:
                            drv_list.append(
                               ddu_dev_data(
                                     item_id = component_disc[0],
                                     parent_item_id = component_disc[1],
                                     description = component_disc[2],
                                     device_id="",
                                     class_code="",
                                     pci_path = component_disc[4],
                                     driver_name = component_disc[5],
                                     instance_id = component_disc[6],
                                     attach_status = component_disc[7],
                                     vendor_id="",
                                     device_type=str(device_scan_index))
                                     )


    return drv_list


def ddu_package_lookup(ddu_dev_instance, repo_list):
    """
    Lookup a package containing a device driver for a device.
    Dependency:
    ${ddu directory}/scripts/probe.sh
    ${ddu directory}/scripts/comp_lookup.sh
    /usr/bin/pkg
    """
    repo_search_all = False
    if len(repo_list) == 0:
        repo_search_all = True

    status, output = commands.getstatusoutput(
                             '%s/scripts/probe.sh init' % ABSPATH)
    if status != 0:
        print >> sys.__stderr__, output
        raise ddu_errors.DevScanNotStart()
    try:
        device_descriptor = ddu_dev_instance.get_description()
        device_compatible = ddu_dev_instance.get_compatible_name_string()
        device_binding = ddu_dev_instance.get_binding_name_string()
    except AttributeError:
        raise ddu_errors.DDuDevDataNotValid(
                             "ddu_dev_data argument is invalid.")


    if repo_search_all == False:
        repo_names = ''
        for repo_index in repo_list:
            try:
                repo_names += str(repo_index.get_repo_name())
                repo_names += " "
            except AttributeError:
                raise ddu_errors.RepositorylistNotValid(
                                      "repo list argument is invalid")

        status, output = commands.getstatusoutput(
                                 '%s/scripts/comp_lookup.sh \
                                 \"%s\" \"%s\" || \
                                 %s/scripts/comp_lookup.sh \
                                 \"%s\" \"%s\"' %
                                 (ABSPATH, device_compatible, repo_names,
                                  ABSPATH, device_binding, repo_names))
    else:
        status, output = commands.getstatusoutput(
                                 '%s/scripts/comp_lookup.sh \"%s\" || \
                                  %s/scripts/comp_lookup.sh \"%s\"' %
                                  (ABSPATH, device_compatible,
                                   ABSPATH, device_binding))

    if len(output) == 0:
        return ddu_package_object(
                                pkg_type = "UNK",
                                pkg_name = "",
                                pkg_location = "",
                                inf_link = "",
                                compatible_name = device_compatible,
                                flags_64bit = "",
                                device_descriptor = device_descriptor,
                                third_party_from_search = False)

    package_type = output.split(":")[1]
    package_location = output.split(":")[0]
    if package_type in ["IPS", "SVR4", "UNK"]:
        if package_type == "IPS":
            status, driver_package = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_dlink.tmp' % package_location)
            status, driver_repo = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_info.tmp' % package_location)
            return ddu_package_object(
                                pkg_type = "PKG",
                                pkg_name = driver_package,
                                pkg_location = driver_repo,
                                inf_link = "",
                                compatible_name = package_location,
                                flags_64bit = "",
                                device_descriptor = device_descriptor,
                                third_party_from_search = False)
        elif package_type == "SVR4":
            status, driver_package = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_dlink.tmp' % package_location)
            status, driver_repo = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_info.tmp' % package_location)
            media = os.path.basename(driver_repo)
            location = os.path.dirname(driver_repo)
            return ddu_package_object(
                                pkg_type = "SVR4",
                                pkg_name = media,
                                pkg_location = location,
                                inf_link = driver_package,
                                compatible_name = package_location,
                                flags_64bit = "",
                                device_descriptor = device_descriptor,
                                third_party_from_search = True)
        elif package_type == "UNK"  and package_location != "":
            status, driver_package = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_dlink.tmp' % package_location)
            status, driver_repo = commands.getstatusoutput(
                           '/usr/bin/cat /tmp/%s_info.tmp' % package_location)
            media = os.path.basename(driver_package)
            location = os.path.dirname(driver_package)
            return ddu_package_object(
                                pkg_type = "UNK",
                                pkg_name = media,
                                pkg_location = location,
                                inf_link = driver_repo,
                                compatible_name = device_compatible,
                                flags_64bit = "",
                                device_descriptor = device_descriptor,
                                third_party_from_search = True)
        elif package_type == "UNK"  and package_location == "":
            try:
                logfile = open('/tmp/ddu_err.log', 'a')
                logfile.write("No proper package found for %s" %
                                    str(device_descriptor))
                logfile.close()
            except IOError:
                pass
            return ddu_package_object(
                                pkg_type = "UNK",
                                pkg_name = "",
                                pkg_location = "",
                                inf_link = "",
                                compatible_name = device_compatible,
                                flags_64bit = "",
                                device_descriptor = device_descriptor,
                                third_party_from_search = False)

    raise ddu_errors.PackageNoFound(device_descriptor)

def ddu_install_package(ddu_package_ob, root_install,
                        install_third_party = False):
    """
    Install the package specified by the ddu_package_object given
    Dependency:
    ${ddu directory}/scripts/pkg_relate.sh
    ${ddu directory}/scripts/file_check.sh
    """
    pkg_type = ddu_package_ob.get_pkg_type()
    if not (pkg_type in ["PKG", "SVR4", "DU", "P5I"]):
        raise ddu_errors.PackageTypeInvalid((
                                    '"Package %s invalid. Type must be' +
                                    '"PKG", "SVR4", "DU", "P5I"') % pkg_type)

    pkg_location = ddu_package_ob.get_pkg_location()
    if pkg_location == "":
        raise ddu_errors.PackageTypeInvalid(
                                    "Cannot install a package" +
                                    " with blank location")
    pkg_name = ddu_package_ob.get_pkg_name()
    if pkg_name == "":
        pkg_name = os.path.basename(pkg_location)
        pkg_location = os.path.dirname(pkg_location)

    third_party_from_search = ddu_package_ob.get_third_party_from_search()
    if third_party_from_search == True and install_third_party == False:
        raise ddu_errors.PackageInstallNotAllowed(
                                    "Installation of" +
                                    " insecure packages are not allowed")
    if pkg_type == "PKG":
        status, output = commands.getstatusoutput(
                        "%s/scripts/pkg_relate.sh list all \
                        | nawk -F\"\t\" \'{ print $1 }\' 2>/dev/null" %
                        ABSPATH)
        if status != 0:
            print >> sys.__stderr__, output
            raise ddu_errors.RepositoryNotReadyException(
                                      "Could not check repositories")
        else:
            if not (pkg_location in output.split("\n")):
                raise ddu_errors.InstallAreaUnaccessible()
        status, output = commands.getstatusoutput(
                         "%s/scripts/file_check.sh IPS %s %s %s" %
                         (ABSPATH,pkg_name,pkg_location, root_install))

        if status != 0:
            print >> sys.__stdout__, output
            try:
                logfile = open('/tmp/ddu_err.log', 'a')
                logfile.write(str(output))
                logfile.close()
            except IOError:
                pass

            raise ddu_errors.InstallPkgFail(
                         "Error installing package: name:%s, locn:%s" %
                         (pkg_name, pkg_location))
    elif pkg_type in  ["SVR4", "DU", "P5I"]:
        status, output = commands.getstatusoutput(
                       "%s/scripts/file_check.sh %s \"%s\" %s %s" %
                       (ABSPATH, pkg_type, pkg_name,pkg_location, root_install))
        if status != 0:
            print >> sys.__stdout__, output
            try:
                logfile = open('/tmp/ddu_err.log', 'a')
                logfile.write(str(output))
                logfile.close()
            except IOError:
                pass

            raise ddu_errors.InstallUnkFail(
                             "Error installing package: name:%s, locn:%s" %
                             (pkg_name, pkg_location)
                             )
