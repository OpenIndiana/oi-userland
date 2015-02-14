/*
 * Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */


#include <sys/mdb_modapi.h>

#include "Xserver_mdb.h"
#include "xorg-server.h"
#include "inputstr.h"


struct inputdev_walk_data {
    InputInfo 		inputInfo;
    DeviceIntRec	dev;
};

/*
 * Initialize the inputdev walker by either using the given starting address,
 * or reading the value of the server's "inputInfo" pointer.  We also allocate
 * a struct for storage, and save this using the walk_data pointer.
 */
_X_HIDDEN int
inputdev_walk_init(mdb_walk_state_t *wsp)
{
    uintptr_t inputInfoPtr;
    struct inputdev_walk_data *iwda;

    wsp->walk_data = mdb_alloc(sizeof (struct inputdev_walk_data), UM_SLEEP);
    iwda = (struct inputdev_walk_data *) wsp->walk_data;

    if (mdb_readsym(&(iwda->inputInfo), sizeof (InputInfo), "inputInfo") == -1)
    {
	mdb_warn("failed to read inputInfo data", inputInfoPtr);
	return (WALK_ERR);
    }

    if (wsp->walk_addr == NULL) {
	wsp->walk_addr = (uintptr_t) iwda->inputInfo.devices;
    }

    return (WALK_NEXT);
}

/*
 * At each step, read a device struct into our private storage, and then invoke
 * the callback function.  We terminate when we reach the end of the inputdevs
 * array.
 */
_X_HIDDEN int
inputdev_walk_step(mdb_walk_state_t *wsp)
{
    int status;
    uintptr_t inputdevPtr;
    struct inputdev_walk_data *iwda
	= (struct inputdev_walk_data *) wsp->walk_data;

    if (wsp->walk_addr == NULL)
	return (WALK_DONE);

    if (mdb_vread(&(iwda->dev), sizeof (DeviceIntRec), wsp->walk_addr) == -1) {
	mdb_warn("failed to read DeviceIntRec at %p", wsp->walk_addr);
	return (WALK_DONE);
    }

    status = wsp->walk_callback(wsp->walk_addr, wsp->walk_data,
				wsp->walk_cbdata);

    wsp->walk_addr = (uintptr_t) iwda->dev.next;
    return (status);
}

/*
 * The walker's fini function is invoked at the end of each walk.  Since we
 * dynamically allocated data in client_walk_init, we must free it now.
 */
_X_HIDDEN void
inputdev_walk_fini(mdb_walk_state_t *wsp)
{
    mdb_free(wsp->walk_data, sizeof (struct inputdev_walk_data));
}

_X_HIDDEN void
inputdev_grabs_help(void)
{
    mdb_printf(
	"Prints information about a DeviceIntRec entry in the X server's list\n"
	"of currently connected input devices.\n"
	"\n"
	"If no %<u>addr%</u> is specified, uses ::inputdev_walk to walk the linked list\n"
	"of DeviceIntRec entries starting at the entry stored in the global\n"
	"variable \"InputInfo\" and print information about each one.\n"
	);
}

_X_HIDDEN int
inputdev_grabs(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
    uintptr_t inputdevP;
    DeviceIntPtr dev;
    DeviceIntRec devRec;
    const char *type;
    char devName[32];
    InputInfo 		inputInfo;
    GrabPtr	grabP;

    if (argc != 0)
	return (DCMD_USAGE);

    /*
     * If no inputdev address was specified on the command line, we can
     * print out all inputdevs by invoking the walker, using this
     * dcmd itself as the callback.
     */
    if (!(flags & DCMD_ADDRSPEC)) {
	if (mdb_walk_dcmd("inputdev_walk", "inputdev_grabs",
			  argc, argv) == -1) {
	    mdb_warn("failed to walk 'inputdev_walk'");
	    return (DCMD_ERR);
	}
	return (DCMD_OK);
    }

    if (mdb_vread(&devRec, sizeof (DeviceIntRec), addr) == -1) {
	mdb_warn("failed to read DeviceIntRec at %p", addr);
	return (WALK_DONE);
    }

    dev = &devRec;

    if (mdb_readsym(&inputInfo, sizeof (InputInfo), "inputInfo") == -1)
    {
	mdb_warn("failed to read inputInfo data");
	return (DCMD_ERR);
    }

    if (dev == inputInfo.keyboard) {
	type = "* core keyboard *";
    } else if (dev == inputInfo.pointer) {
	type = "* core pointer *";
    } else {
	type = "";
    }

    if (mdb_readstr(devName, sizeof(devName), (uintptr_t) dev->name) == -1) {
	mdb_warn("failed to read InputdevRec.name at %p", dev->name);
	devName[0] = '\0';
    }

    mdb_printf("Device \"%s\" id %d: %s\n", devName, dev->id, type);

    grabP = dev->deviceGrab.grab;

    if (grabP == NULL) {
	mdb_printf("  -- no active grab on device\n\n");
    } else {
	GrabRec grab;

	if (mdb_vread(&grab, sizeof (GrabRec), (uintptr_t) grabP) == -1) {
	    mdb_warn("failed to read GrabRec at %p", grabP);
	} else {
	    int clientid = CLIENT_ID(grab.resource);

	    mdb_printf("  -- active grab %p by client %d\n\n", grab.resource,
		       clientid);
	}
    }
    return (DCMD_OK);
}

