#! /usr/bin/python2.7
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
provide functions for DDU modules
"""
import os
import sys
import gtk
import commands
import gettext
from xml.dom.minidom import Document
from time import gmtime, strftime
import re
from ConfigParser import ConfigParser

DDUCONFIG = ConfigParser()
DDUCONFIG.read(os.path.join(os.path.dirname(
               os.path.realpath(sys.argv[0])),"ddu.conf"))
ABSPATH = DDUCONFIG.get('general','abspath')

try:
    gettext.bindtextdomain('ddu','%s/i18n' % ABSPATH)
    gettext.textdomain('ddu')
    gtk.glade.bindtextdomain('ddu','%s/i18n' % ABSPATH)
except AttributeError:
    pass

_ = gettext.gettext

def insert_one_tag_into_buffer(textbuffer, name, *params):
    """insert tag in to text area"""
    tag = gtk.TextTag(name)
    while(params):
        tag.set_property(params[0], params[1])
        params = params[2:]
    table = textbuffer.get_tag_table()
    if table.lookup("tag") is None:
        table.add(tag)
    return

def insert_conf(ent1, ent2, ent3, ent4):
    """
    build system hardware configuration  for submission dialog.
    ent1-4 are label objects in submission dialog
    """
    status, output = commands.getstatusoutput('/sbin/uname -p')
    bindir = ABSPATH + '/bin/' + output
    status, output = commands.getstatusoutput('%s/dmi_info -S' % bindir)
    if status != 0:
        print "can not get system info!"
        return
    inpt = output.splitlines()
    ent1.set_text(str(inpt[1].split(':')[1].strip()))
    ent2.set_text(str(inpt[2].split(':')[1].strip()))

    status, output = commands.getstatusoutput('%s/dmi_info -C' % bindir)
    if status != 0:
        print "can not get processor info!"
        return

    inpt = output.splitlines()
    ent3.set_text(str(inpt[0].split(':')[1].strip()))

    status, output = commands.getstatusoutput('%s/dmi_info -B' % bindir)
    if status != 0:
        print "can not get BIOS info!"
        return

    inpt = output.splitlines()
    ent4.set_text(
                 str(inpt[1].split(':')[1].strip()) + 
                 " Version:" + str(inpt[2].split(':')[1].strip()) + 
                 " Release Date:" + str(inpt[3].split(':')[1].strip()))
    return

def insert_col_info(name_ent, email_ent, server_com, manu_text, manu_modle, 
                    cpu_type, firmware_maker, bios_set, general_ent, inform_c):
    """
    build system configuration for submission dialog information collect
    text area
    """
    del name_ent, email_ent, server_com, cpu_type, bios_set, general_ent
    status, output = commands.getstatusoutput('/sbin/uname -p')
    del status
    bindir = ABSPATH + '/bin/' + output
	
    textbuffer = inform_c.get_buffer()
    textbuffer.delete(textbuffer.get_start_iter(), textbuffer.get_end_iter())
    line_iter = textbuffer.get_iter_at_offset (0)

    line_iter = textbuffer.get_end_iter()

    textbuffer.insert_with_tags_by_name(line_iter,
                                       _("Manufacture name:"), "bold")
    textbuffer.insert(line_iter, str(manu_text.get_text().strip()))

    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, 
                                       "\nManufacture model:", "bold")
    textbuffer.insert(line_iter, str(manu_modle.get_text().strip()))

    status, output = commands.getstatusoutput('isainfo -b')

    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name (line_iter, "\n64 Bit:","bold")
    if output == '32':
        textbuffer.insert(line_iter, 'False')
    elif output == '64':
        textbuffer.insert(line_iter, 'True')

    status, output = commands.getstatusoutput('uname -a')
    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, "\nOS version:", "bold")
    textbuffer.insert(line_iter, str(output.strip()))
	
    status, output = commands.getstatusoutput('%s/dmi_info -C' % bindir)
    inpt = output.splitlines()
    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name (line_iter, "\nCPU Type:","bold")
    textbuffer.insert(line_iter, str(inpt[0].split(':')[1].strip()))
    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, "\nCPU Number:","bold")
    textbuffer.insert(line_iter, str(inpt[1].split(':')[1].strip()))
    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, 
                                       "\nNumber Of Cores Per Processor:", 
                                       "bold")
    textbuffer.insert(line_iter, str(inpt[2].split(':')[1].strip()))
    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name (line_iter, 
                                        "\nNumber Of Threads Per Processor:", 
                                        "bold")
    textbuffer.insert(line_iter, str(inpt[3].split(':')[1].strip()))

    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, 
                                       "\nBios/Firmware Maker:", "bold")
    textbuffer.insert(line_iter, str(firmware_maker.get_text().strip()))


    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name (line_iter, "\nprtconf -pv:\n", "bold")
    status, output = commands.getstatusoutput('/usr/sbin/prtconf -pv')
    textbuffer.insert(line_iter, output)

    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name(line_iter, "\nprtdiag:\n","bold")
    status, output = commands.getstatusoutput('/usr/sbin/prtdiag')
    textbuffer.insert(line_iter, output)

    line_iter = textbuffer.get_end_iter()
    textbuffer.insert_with_tags_by_name (line_iter, "\n\n","bold")
    status, output = commands.getstatusoutput('%s/dmi_info' % bindir)
    textbuffer.insert(line_iter, output)
    return

def insert_col(name_ent, email_ent, server_com, manu_text, manu_modle, \
               cpu_type, firmware_maker, bios_set, general_ent, \
               inform_c, dev_submit):
    """build system config xml file for submission"""
    del cpu_type, bios_set, inform_c
    status, output = commands.getstatusoutput('/sbin/uname -p')
    bindir = ABSPATH + '/bin/' + output
    scriptsdir = ABSPATH + '/scripts'
    model = server_com.get_model()
    active = server_com.get_active()
    server_inf = model[active][0]

    status, isa_output = commands.getstatusoutput('isainfo -b')

    status, os_output = commands.getstatusoutput('uname -a')
	
    status, dmic_output = commands.getstatusoutput('%s/dmi_info -C' % bindir)
    dmic_inpt = dmic_output.splitlines()

    textbuffer_g = general_ent.get_buffer()
    startiter = textbuffer_g.get_start_iter()
    enditer = textbuffer_g.get_end_iter()

    status, prt_output = commands.getstatusoutput('/usr/sbin/prtconf -pv')
    status, prtd_output = commands.getstatusoutput('/usr/sbin/prtdiag')
    status, dmi_output = commands.getstatusoutput('%s/dmi_info' % bindir)

    doc = Document()
	
    hclsubmittal = doc.createElement("HCLSubmittal")
    doc.appendChild(hclsubmittal)

    tierlevel = doc.createElement("tierLevel")
    hclsubmittal.appendChild(tierlevel)
	
    tierleveltext = doc.createTextNode("3")
    tierlevel.appendChild(tierleveltext)

    submittaltype = doc.createElement("submittalType")
    hclsubmittal.appendChild(submittaltype)

    submittaltypetext = doc.createTextNode("system")
    submittaltype.appendChild(submittaltypetext)

    entrytype = doc.createElement("entryType")
    hclsubmittal.appendChild(entrytype)

    entrytypetext = doc.createTextNode(server_inf)
    entrytype.appendChild(entrytypetext)

    mfg = doc.createElement("mfg")
    hclsubmittal.appendChild(mfg)

    mfgtext = doc.createTextNode(manu_text.get_text())
    mfg.appendChild(mfgtext)

    model = doc.createElement("model")
    hclsubmittal.appendChild(model)

    modeltext = doc.createTextNode(manu_modle.get_text())
    model.appendChild(modeltext)

    osrevision = doc.createElement("osRevision")
    hclsubmittal.appendChild(osrevision)

    osrevisiontext = doc.createTextNode(os_output)
    osrevision.appendChild(osrevisiontext)

    cputype = doc.createElement("cpuType")
    hclsubmittal.appendChild(cputype)

    cputypetext = doc.createTextNode(dmic_inpt[0].split(':')[1])
    cputype.appendChild(cputypetext)

    numcpu = doc.createElement("numCPU")
    hclsubmittal.appendChild(numcpu)

    numcputext = doc.createTextNode(dmic_inpt[1].split(':')[1])
    numcpu.appendChild(numcputext)

    patchestested = doc.createElement("patchesTested")
    hclsubmittal.appendChild(patchestested)

    chipset = doc.createElement("chipSet")
    hclsubmittal.appendChild(chipset)

    sixty_four_bit = doc.createElement("sixty_four_bit")
    hclsubmittal.appendChild(sixty_four_bit)

    sixty_four_bittext = doc.createTextNode(str(isa_output=='64'))
    sixty_four_bit.appendChild(sixty_four_bittext)


    firmware = doc.createElement("biosMaker")
    hclsubmittal.appendChild(firmware)

    firmwaretext = doc.createTextNode(firmware_maker.get_text())
    firmware.appendChild(firmwaretext)


    biossettings = doc.createElement("biosSettings")
    hclsubmittal.appendChild(biossettings)

    boardrevlvl = doc.createElement("boardRevLvl")
    hclsubmittal.appendChild(boardrevlvl)

    drivername = doc.createElement("driverName")
    hclsubmittal.appendChild(drivername)

    driverversion = doc.createElement("driverVersion")
    hclsubmittal.appendChild(driverversion)

    techtype = doc.createElement("techType")
    hclsubmittal.appendChild(techtype)

    cardtype = doc.createElement("cardType")
    hclsubmittal.appendChild(cardtype)


    driverinfo = doc.createElement("driverInfo")
    hclsubmittal.appendChild(driverinfo)

    testsuite = doc.createElement("testSuite")
    hclsubmittal.appendChild(testsuite)
    testsuitetext = doc.createTextNode('False')
    testsuite.appendChild(testsuitetext)

    testresults = doc.createElement("testResults")
    hclsubmittal.appendChild(testresults)

    testlevel = doc.createElement("testLevel")
    hclsubmittal.appendChild(testlevel)
    testleveltext = doc.createTextNode(str(0))
    testlevel.appendChild(testleveltext)

    gennotes = doc.createElement("genNotes")
    hclsubmittal.appendChild(gennotes)
    gennotestext = doc.createTextNode(textbuffer_g.get_text(startiter, \
                                                            enditer))
    gennotes.appendChild(gennotestext)

    numcomponents = doc.createElement("numComponents")
    hclsubmittal.appendChild(numcomponents)
    numcomponentstext = doc.createTextNode(str(0))
    numcomponents.appendChild(numcomponentstext)


    syscomponents = doc.createElement("sysComponents")
    syscomponents.setAttribute("number", "0")
    hclsubmittal.appendChild(syscomponents)

    prtconfoutput = doc.createElement("prtConfOutput")
    hclsubmittal.appendChild(prtconfoutput)
    prtconfoutputtext = doc.createTextNode(str(prt_output))
    prtconfoutput.appendChild(prtconfoutputtext)

    prtdiagoutput = doc.createElement("prtDiagOutput")
    hclsubmittal.appendChild(prtdiagoutput)
    prtdiagoutputtext = doc.createTextNode(str(prtd_output))
    prtdiagoutput.appendChild(prtdiagoutputtext)
	
    datesubmitted = doc.createElement("dateSubmitted")
    hclsubmittal.appendChild(datesubmitted)
    datesubmittedtext = doc.createTextNode(str(strftime("%Y-%m-%d", gmtime())))
    datesubmitted.appendChild(datesubmittedtext)
	
    submitter = doc.createElement("submitter")
    hclsubmittal.appendChild(submitter)

    submittername = doc.createElement("submitterName")
    submitter.appendChild(submittername)

    submitternametext = doc.createTextNode(name_ent.get_text())
    submittername.appendChild(submitternametext)

    submitteremail = doc.createElement("submitterEmail")
    submitter.appendChild(submitteremail)

    submitteremailtext = doc.createTextNode(email_ent.get_text())
    submitteremail.appendChild(submitteremailtext)

    emailprivate = doc.createElement("emailPrivate")
    submitter.appendChild(emailprivate)

    emailprivatetext = doc.createTextNode('True')
    emailprivate.appendChild(emailprivatetext)

    submittercompany = doc.createElement("submitterCompany")
    submitter.appendChild(submittercompany)

    country = doc.createElement("country")
    submitter.appendChild(country)

    auditingnotes = doc.createElement("auditingNotes")
    hclsubmittal.appendChild(auditingnotes)
    auditingnotestext = doc.createTextNode('Oracle Solaris OS DDU v1.3')
    auditingnotes.appendChild(auditingnotestext)

    systemdetails = doc.createElement("systemDetails")
    hclsubmittal.appendChild(systemdetails)

    status, dmis_output = commands.getstatusoutput('%s/dmi_info -S' % bindir)
    dmis_inpt = dmis_output.splitlines()

    system_inf = doc.createElement("system")
    systemdetails.appendChild(system_inf)

    product_inf = doc.createElement("product")
    system_inf.appendChild(product_inf)

    product_inftext = doc.createTextNode(dmis_inpt[2].split(':')[1])
    product_inf.appendChild(product_inftext)

    manufacturer_inf = doc.createElement("manufacturer")
    system_inf.appendChild(manufacturer_inf)
    manufacturer_inftext = doc.createTextNode(dmis_inpt[1].split(':')[1])
    manufacturer_inf.appendChild(manufacturer_inftext)

    boot_env = doc.createElement("BootFromHd")
    systemdetails.appendChild(boot_env)

    storage_env = doc.createElement("Storage")
    systemdetails.appendChild(storage_env)

    zpool_env = doc.createElement("ZpoolStatus")
    storage_env.appendChild(zpool_env)

    zfs_env = doc.createElement("ZfsList")
    storage_env.appendChild(zfs_env)

    disk_env = doc.createElement("DiskInfo")
    storage_env.appendChild(disk_env)

    status, boot_output = commands.getstatusoutput(
                                                  'pfexec df / | grep ramdisk')
    del boot_output
    if status == 0:
        boot_inftext = doc.createTextNode("No")
    else:
        boot_inftext = doc.createTextNode("Yes")
        status, zpool_output = commands.getstatusoutput('pfexec zpool status')
        zpool_envlist = doc.createTextNode(zpool_output)
        zpool_env.appendChild(zpool_envlist)
        status, zfs_output = commands.getstatusoutput('pfexec zfs list')
        zfs_envlist = doc.createTextNode(zfs_output)
        zfs_env.appendChild(zfs_envlist)

    boot_env.appendChild(boot_inftext)

    status, dmib_output = commands.getstatusoutput('%s/dmi_info -B' % bindir)
    dmib_inpt = dmib_output.splitlines()

    bios_inf = doc.createElement("bios")
    systemdetails.appendChild(bios_inf)

    vendor_inf = doc.createElement("vendor")
    bios_inf.appendChild(vendor_inf)
    vendor_inftext = doc.createTextNode(dmib_inpt[1].split(':')[1])
    vendor_inf.appendChild(vendor_inftext)

    version_inf = doc.createElement("version")
    bios_inf.appendChild(version_inf)
    version_inftext = doc.createTextNode(dmib_inpt[2].split(':')[1])
    version_inf.appendChild(version_inftext)

    releasedate_inf = doc.createElement("releaseDate")
    bios_inf.appendChild(releasedate_inf)
    releasedate_inftext = doc.createTextNode(dmib_inpt[3].split(':')[1])
    releasedate_inf.appendChild(releasedate_inftext)

    biosrevision_inf = doc.createElement("biosRevision")
    bios_inf.appendChild(biosrevision_inf)
    biosrevision_inftext = doc.createTextNode(dmib_inpt[4].split(':')[1])
    biosrevision_inf.appendChild(biosrevision_inftext)

    firmwarerevision_inf = doc.createElement("firmwareRevision")
    bios_inf.appendChild(firmwarerevision_inf)
    firmwarerevision_inftext = doc.createTextNode(dmib_inpt[5].split(':')[1])
    firmwarerevision_inf.appendChild(firmwarerevision_inftext)


    status, dmim_output = commands.getstatusoutput('%s/dmi_info -M' % bindir)
    dmim_inpt = dmim_output.splitlines()

    motherboard_inf = doc.createElement("motherboard")
    systemdetails.appendChild(motherboard_inf)

    product_inf = doc.createElement("product")
    motherboard_inf.appendChild(product_inf)
    try:
        product_inftext = doc.createTextNode(dmim_inpt[1].split(':')[1])
        product_inf.appendChild(product_inftext)
    except (AttributeError, IndexError):
        pass

    manufacturer_inf = doc.createElement("manufacturer")
    motherboard_inf.appendChild(manufacturer_inf)

    try:
        manufacturer_inftext = doc.createTextNode(dmim_inpt[2].split(':')[1])
        manufacturer_inf.appendChild(manufacturer_inftext)
    except (AttributeError, IndexError):
        pass

    version_inf = doc.createElement("version")
    motherboard_inf.appendChild(version_inf)
	
    try:
        version_inftext = doc.createTextNode(dmim_inpt[3].split(':')[1])
        version_inf.appendChild(version_inftext)
    except (AttributeError, IndexError):
        pass

    device_inf = doc.createElement("device")
    motherboard_inf.appendChild(device_inf)
    try:
        device_inftext = doc.createTextNode(dmim_inpt[4].split(':')[1])
        device_inf.appendChild(device_inftext)
    except (AttributeError, IndexError):
        pass

    processor_inf = doc.createElement("Processor")
    systemdetails.appendChild(processor_inf)

    status, dmic_output = commands.getstatusoutput('%s/dmi_info -C' % bindir)
    dmic_inpt = dmic_output.splitlines()

    cputype = doc.createElement("CpuType")
    processor_inf.appendChild(cputype)
    cputypetext = doc.createTextNode(dmic_inpt[0].split(':')[1])
    cputype.appendChild(cputypetext)

    cpunum = doc.createElement("CpuNumber")
    processor_inf.appendChild(cpunum)
    cpunumtext = doc.createTextNode(dmic_inpt[1].split(':')[1])
    cpunum.appendChild(cpunumtext)

    numberofcpp = doc.createElement("NumberOfCoresPerProcessor")
    processor_inf.appendChild(numberofcpp)
    numberofcpptext = doc.createTextNode(dmic_inpt[2].split(':')[1])
    numberofcpp.appendChild(numberofcpptext)

    numberoftpp = doc.createElement("NumberOfThreadsPerProcessor")
    processor_inf.appendChild(numberoftpp)
    numberoftpptext = doc.createTextNode(dmic_inpt[3].split(':')[1])
    numberoftpp.appendChild(numberoftpptext)

    try:
        for loop in range(int(dmic_inpt[1].split(':')[1])):
            status, dmi_output = commands.getstatusoutput(
                                          '%s/dmi_info' % bindir)
            status, cpun_inf = commands.getstatusoutput( 
                               '%s/dmi_info | grep -n "Processor %s"' %
                               (bindir, str(loop)))
	
            dmic_inpt = dmi_output.splitlines()
            cpu_inf = doc.createElement("cpu")
            processor_inf.appendChild(cpu_inf)
		
            sockettype_inf = doc.createElement("socketType")
            cpu_inf.appendChild(sockettype_inf)
            sockettype_inftext = doc.createTextNode( 
                                 dmic_inpt[int(
                                 cpun_inf.split(':')[0])].split(':')[1])
            sockettype_inf.appendChild(sockettype_inftext)
            manufacturer_inf = doc.createElement("manufacturer")
            cpu_inf.appendChild(manufacturer_inf)
            manufacturer_inftext = doc.createTextNode(
                                   dmic_inpt[int(
                                   cpun_inf.split(':')[0])+1].split(':')[1])
            manufacturer_inf.appendChild(manufacturer_inftext)
            voltage_inf = doc.createElement("voltage")
            cpu_inf.appendChild(voltage_inf)
            voltage_inftext = doc.createTextNode( 
                              dmic_inpt[int(
                              cpun_inf.split(':')[0])+2].split(':')[1])
            voltage_inf.appendChild(voltage_inftext)
            externalclock_inf = doc.createElement("externalClock")
            cpu_inf.appendChild(externalclock_inf)
            externalclock_inftext = doc.createTextNode( 
                                    dmic_inpt[int(
                                    cpun_inf.split(':')[0])+3].split(':')[1])
            externalclock_inf.appendChild(externalclock_inftext)

            maxspeed_inf = doc.createElement("maxSpeed")
            cpu_inf.appendChild(maxspeed_inf)
            maxspeed_inftext = doc.createTextNode( 
                               dmic_inpt[int(
                               cpun_inf.split(':')[0])+4].split(':')[1])
            maxspeed_inf.appendChild(maxspeed_inftext)

            currentspeed_inf = doc.createElement("currentSpeed")
            cpu_inf.appendChild(currentspeed_inf)
            currentspeed_inftext = doc.createTextNode( 
                                   dmic_inpt[int(
                                   cpun_inf.split(':')[0])+5].split(':')[1])
            currentspeed_inf.appendChild(currentspeed_inftext)

    except (AttributeError, ValueError):
        pass

    status, dmim_output = commands.getstatusoutput('%s/dmi_info -m' % bindir)
    dmim_inpt = dmim_output.splitlines()

    status, dmims_output = commands.getstatusoutput( 
                           '%s/dmi_info -m | grep -n "Memory Subsystem"' %
                           bindir)
    dmims_inpt = dmims_output.splitlines()

    try:
        for loop in range(len(dmims_inpt)):
            memory_inf = doc.createElement("memory")
            systemdetails.appendChild(memory_inf)
		
            usedfunction_inf = doc.createElement("usedFunction")
            memory_inf.appendChild(usedfunction_inf)
            usedfunction_inftext = doc.createTextNode( 
                                   dmim_inpt[int(dmims_inpt[int(
                                   loop)].split(':')[0])].split(':')[1])
            usedfunction_inf.appendChild(usedfunction_inftext)
	
            eccsupport_inf = doc.createElement("eccSupport")
            memory_inf.appendChild(eccsupport_inf)
            eccsupport_inftext = doc.createTextNode( 
                                 dmim_inpt[int(dmims_inpt[int(
                                 loop)].split(':')[0]) + 1].split(':')[1])
            eccsupport_inf.appendChild(eccsupport_inftext)

            maxmemorycapacity_inf = doc.createElement("maxMemoryCapacity")
            memory_inf.appendChild(maxmemorycapacity_inf)
            maxmemorycapacity_inftext = doc.createTextNode( 
                                        dmim_inpt[int(dmims_inpt[int(
                                        loop)].split(':')[0]) +
                                        2].split(':')[1])
            maxmemorycapacity_inf.appendChild(maxmemorycapacity_inftext)
	
            for subloop in range(int(dmim_inpt[int(dmims_inpt[int(
                                 loop)].split(':')[0]) + 3].split(':')[1])):
                device_inf = doc.createElement("device")
                memory_inf.appendChild(device_inf)
			
                index = 4
                while dmim_inpt[int(dmims_inpt[int(loop)].split(':')[0]) +
                      int(index)].find(str("Memory Device " +
                      str(subloop))) == -1:
                    index = index + 1
			
                devicelocator_inf = doc.createElement("deviceLocator")
                device_inf.appendChild(devicelocator_inf)

                totalwidth_inf = doc.createElement("totalWidth")
                device_inf.appendChild(totalwidth_inf)

                datawidth_inf = doc.createElement("dataWidth")
                device_inf.appendChild(datawidth_inf)

                installedsize_inf = doc.createElement("installedSize")
                device_inf.appendChild(installedsize_inf)

                devicetype_inf = doc.createElement("deviceType")
                device_inf.appendChild(devicetype_inf)

                speed_inf = doc.createElement("speed")
                device_inf.appendChild(speed_inf)

                if dmim_inpt[int(dmims_inpt[int(loop)].split(':')[0]) +
                             int(index) + 1].find('Not Installed') == -1:
                    devicelocator_inftext = doc.createTextNode(
                                            dmim_inpt[int(dmims_inpt[int(
                                            loop)].split(':')[0]) +
                                            int(index) + 1])
                    devicelocator_inf.appendChild(devicelocator_inftext)

                    totalwidth_inftext = doc.createTextNode(dmim_inpt[int(
                                         dmims_inpt[int(loop)].split(':')[0]) +
                                         int(index) + 2])
                    totalwidth_inf.appendChild(totalwidth_inftext)
	
                    datawidth_inftext = doc.createTextNode(dmim_inpt[int(
                                        dmims_inpt[int(loop)].split(':')[0]) +
                                        int(index) + 3])
                    datawidth_inf.appendChild(datawidth_inftext)
			
                    installedsize_inftext = doc.createTextNode(dmim_inpt[int(
                                            dmims_inpt[int(
                                            loop)].split(':')[0]) +
                                            int(index) + 4])
                    installedsize_inf.appendChild(installedsize_inftext)

                    devicetype_inftext = doc.createTextNode(dmim_inpt[int(
                                         dmims_inpt[int(loop)].split(':')[0]) +
                                         int(index) + 5])
                    devicetype_inf.appendChild(devicetype_inftext)

                    speed_inftext = doc.createTextNode(dmim_inpt[int(
                                    dmims_inpt[int(loop)].split(':')[0]) +
                                    int(index) + 6])
                    speed_inf.appendChild(speed_inftext)

    except AttributeError:
        pass

    pcidevices = doc.createElement("pciDevices")
    hclsubmittal.appendChild(pcidevices)
	
    for category, controllers in dev_submit.iteritems():
        del category
        if len(controllers) > 0:
            for pci_controller in controllers:
                devices = doc.createElement("devices")
                pcidevices.appendChild(devices)
                status, detail_output = commands.getstatusoutput(
                                        '%s/det_info.sh %s CLASS=%s' %
                                        (scriptsdir, pci_controller[0],
                                        pci_controller[1]))
                if status == 0:
                    detail_file = open(detail_output,"r")
                    vendor_id = ""
                    device_id = ""
                    class_code = ""
                    subvendor_id = ""
                    subdevice_id = ""
                    revision_id = ""
                    driver_name = ""
                    driver_status = ""
                    disk_status = ""
                    instance = ""
                    for line in detail_file.readlines():
                        searchp = re.compile('^vendor-id')
                        if searchp.search(line):
                            vendor_id = str(line.split(':')[1]).strip()
                        searchp = re.compile('^device-id')
                        if searchp.search(line):
                            device_id = str(line.split(':')[1]).strip()
                            class_code = str(pci_controller[1]).strip()
                        searchp = re.compile('^subsystem-vendor-id')
                        if searchp.search(line):
                            subvendor_id = str(line.split(':')[1]).strip()
                        searchp = re.compile('^subsystem-id')
                        if searchp.search(line):
                            subdevice_id = str(line.split(':')[1]).strip()
                        searchp = re.compile('^revision-id')
                        if searchp.search(line):
                            revision_id = str(line.split(':')[1]).strip()
                        searchp = re.compile('^driver\ name')
                        if searchp.search(line):
                            driver_name = str(line.split(':')[1]).strip()
                        searchp = re.compile('^driver\ state')
                        if searchp.search(line):
                            driver_status = str(line.split(':')[1]).strip()
                        searchp = re.compile('^DISK')
                        if searchp.search(line):
                            disk_status = "Yes"
                        searchp = re.compile('^instance')
                        if searchp.search(line):
                            instance = str(line.split(':')[1]).strip()
                    detail_file.close()
                    os.remove(detail_output)
                    comname = doc.createElement("comName")
                    devices.appendChild(comname)

                    comnametext = doc.createTextNode(
                                      str(pci_controller[2]).strip())
                    comname.appendChild(comnametext)

                    compath = doc.createElement("comPath")
                    devices.appendChild(compath)

                    compathtext = doc.createTextNode(
                                      str(pci_controller[0]).strip())
                    compath.appendChild(compathtext)
						
                    vendorid = doc.createElement("vendorId")
                    devices.appendChild(vendorid)

                    vendoridtext = doc.createTextNode(vendor_id)
                    vendorid.appendChild(vendoridtext)
				
                    deviceid = doc.createElement("deviceId")
                    devices.appendChild(deviceid)

                    deviceidtext = doc.createTextNode(device_id)
                    deviceid.appendChild(deviceidtext)

                    classcode = doc.createElement("classCode")
                    devices.appendChild(classcode)

                    classcodetext = doc.createTextNode(class_code)
                    classcode.appendChild(classcodetext)

                    subvendorid = doc.createElement("subVendorId")
                    devices.appendChild(subvendorid)

                    subvendoridtext = doc.createTextNode(subvendor_id)
                    subvendorid.appendChild(subvendoridtext)

                    subdeviceid = doc.createElement("subDeviceId")
                    devices.appendChild(subdeviceid)

                    subdeviceidtext = doc.createTextNode(subdevice_id)
                    subdeviceid.appendChild(subdeviceidtext)

                    revisionid = doc.createElement("revisionId")
                    devices.appendChild(revisionid)

                    revisionidtext = doc.createTextNode(revision_id)
                    revisionid.appendChild(revisionidtext)

                    drivername = doc.createElement("driverName")
                    devices.appendChild(drivername)

                    drivernametext = doc.createTextNode(driver_name)
                    drivername.appendChild(drivernametext)

                    driverstatus = doc.createElement("driverStatus")
                    devices.appendChild(driverstatus)
					
                    driverstatustext = doc.createTextNode(driver_status)
                    driverstatus.appendChild(driverstatustext)

                    driverinstance = doc.createElement("driverInstance")
                    devices.appendChild(driverinstance)
					
                    driverinstancetext = doc.createTextNode(instance)
                    driverinstance.appendChild(driverinstancetext)

                    if disk_status == "Yes":
                        disk_status, \
                        diskdetail_output = commands.getstatusoutput(
                                                     '%s/hd_detect -c %s' %
                                                     (bindir,
                                                     pci_controller[0]))
                        if disk_status == 0:
                            output_lines = diskdetail_output.splitlines()
                            for line in output_lines:
                                disks = doc.createElement("disk")
                                disk_env.appendChild(disks)

                                diskdetail = doc.createElement("diskIndex")
                                disks.appendChild(diskdetail)
                                diskditailtext = doc.createTextNode(
                                                     str(line.split(
                                                     ":")[0]).strip())
                                diskdetail.appendChild(diskditailtext)

                                diskphypath = doc.createElement("phyPath")
                                disks.appendChild(diskphypath)
                                diskphypathtext = doc.createTextNode(
                                                      str(line.split(
                                                      ":")[1]).strip())
                                diskphypath.appendChild(diskphypathtext)

                                diskdevpath = doc.createElement("devPath")
                                disks.appendChild(diskdevpath)
                                diskdevpathtext = doc.createTextNode( \
                                       str(line.split(":")[2]).strip())
                                diskdevpath.appendChild(diskdevpathtext)
							
    return doc
