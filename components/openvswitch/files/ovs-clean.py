#!/usr/bin/python2.7
#
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

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

from rad.bindings.com.oracle.solaris.rad.dlmgr import *
import rad.client as radcli
import rad.connect as radcon

def dlvalue_to_propval(adict):
    pval = None
    for key, value in adict.iteritems():
        for k, v in vars(value).iteritems():
            if k == 'type':
                continue
            if v is not None:
                pval = v
                break
    return pval

def printError(ex):
    dlerr = ex.get_payload()
    if dlerr != None:
        print "Error: %s" % dlerr.errmsg
    else:
        print "Exception: %s" % ex

def deleteVNIC(argv, numargs, dm):
    if numargs !=  3:
        print "usage: %s delete-vnic vnicname" % (argv[0])
        return False

    try:
        dm.deleteVNIC(argv[2])
    except radcli.ObjectError as ex:
        printError(ex)
        return False

    return True

def resetOFPorts(argv, numargs, rc):
    if numargs != 2:
        print "usage: %s reset-ofports" % (argv[0])
        return False

    # Enumerate all the datalinks and reset any ofports that are set
    rval = True
    datalink_name_list = rc.list_objects(Datalink())
    for datalink_name in datalink_name_list:
        datalink = rc.get_object(datalink_name)

        try:
            props = datalink.getProperties(["ofport", "temporary"], ["current"])
        except radcli.ObjectError as ex:
            dlerr = ex.get_payload()
            # ignore if not a supported property
	    if dlerr.err == DLSTATUS.INVALID_ARGUMENT._value:
                continue
            printError(ex)
            rval = False
            continue

        prop = props[0]
        pval =  dlvalue_to_propval(prop.map)
        if pval == None or pval == 0:
            continue
        prop = props[1]
        pval =  dlvalue_to_propval(prop.map)
        try:
            datalink.setProperties({
                'temporary': DLValue(type=DLValueType.BOOLEAN, bval=pval),
                'ofport': DLValue(type=DLValueType.ULONG, ulval=None)
            })
        except radcli.ObjectError as ex:
            dlerr = ex.get_payload()
            printError(ex)
            rval = False

    return rval

def removeFlows(argv, numargs, rc):
    if numargs != 2:
        print "usage: %s remove-flows" % (argv[0])
        return False

    # Enumerate all the datalinks and look for OF links
    rval = True
    datalink_list = rc.list_objects(Datalink())
    for datalink_name in datalink_list:
        datalink = rc.get_object(datalink_name)
        linkname = datalink_name._kvpairs["name"]

	try:
            props = datalink.getProperties(["openvswitch"], ["current"])
        except radcli.ObjectError as ex:
            dlerr = ex.get_payload()
            # ignore if not a supported property
	    if dlerr.err == DLSTATUS.INVALID_ARGUMENT._value:
                continue
            printError(ex)
            rval = False
            continue

        prop = props[0]
        pval =  dlvalue_to_propval(prop.map)
        if pval == str("off"):
            continue

        # Enumerate all the flows for the datalink and remove them
        flow_list = rc.list_objects(Flow(), ADRGlobPattern({'linkname': linkname}))
        for flow_name in flow_list:
            try:
                datalink.removeFlow(flow_name._kvpairs["name"])
            except radcli.ObjectError as ex:
                dlerr = ex.get_payload()
                # ignore if the flow is no longer found or is a system
		# generated flow (e.g., vxlan system flows)
                if dlerr.err == DLSTATUS.NOT_FOUND._value or dlerr.err == DLSTATUS.SYSTEM_FLOW._value:
                    continue
                printError(ex)
                rval = False

    return rval

def deleteEtherstub(argv, numargs, rc, dm):
    if numargs != 3:
        print "usage: %s delete-etherstub etherstub-name" % (argv[0])
        return False

    name = argv[2]
    try:
        etherstub = rc.get_object(Etherstub(), ADRGlobPattern({'name': name}))
        etherstub.setProperties({
            'openvswitch': DLValue(type=DLValueType.BOOLEAN, bval=None)
            })
        dm.deleteEtherstub(name)
    except radcli.NotFoundError as ex:
        pass
    except radcli.ObjectError as ex:
        dlerr = ex.get_payload()
        printError(ex)
        return False

    return True

def main():
    numargs = len(sys.argv)
    if numargs < 2:
        print "usage: %s command [args]" % (sys.argv[0])
        print "       %s delete-vnic vnic-name" % (sys.argv[0])
        print "       %s reset-ofports" % (sys.argv[0])
        print "       %s remove-flows" % (sys.argv[0])
        print "       %s delete-etherstub etherstub-name" % (sys.argv[0])
        sys.exit(1)

    rc = radcon.connect_unix()
    dm = rc.get_object(DatalinkManager())

    if sys.argv[1] == "delete-vnic":
        rval = deleteVNIC(sys.argv, numargs, dm)
    elif sys.argv[1] == "reset-ofports":
        rval = resetOFPorts(sys.argv, numargs, rc)
    elif sys.argv[1] == "remove-flows":
        rval = removeFlows(sys.argv, numargs, rc)
    elif sys.argv[1] == "delete-etherstub":
        rval = deleteEtherstub(sys.argv, numargs, rc, dm)
    else:
        print "\nInvalid ovs shutdown function"
        rval = False;

    sys.exit(rval == False)

if __name__ == "__main__":
    main()
