/*
 * Copyright (c) 2004, 2010, Oracle and/or its affiliates. All rights reserved.
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


#ifdef HAVE_XORG_CONFIG_H
#include <xorg-config.h>
#endif

#include "xf86Module.h"
#include "xf86Opt.h"

#include <X11/extensions/interactive.h>
#include "interactive_srv.h"

static MODULESETUPPROTO(IASetup);

static ExtensionModule IAExt =
{
    IAExtensionInit,
    IANAME,
    NULL,
    NULL,
    NULL
};

static XF86ModuleVersionInfo VersRec =
{
    "IANAME",
    MODULEVENDORSTRING,
    MODINFOSTRING1,
    MODINFOSTRING2,
    XORG_VERSION_CURRENT,
    1, 0, 0,
    ABI_CLASS_EXTENSION,
    ABI_EXTENSION_VERSION,
    MOD_CLASS_NONE,
    {0,0,0,0}
};

_X_EXPORT XF86ModuleData iaModuleData = { &VersRec, IASetup, NULL };

static pointer
IASetup(pointer module, pointer opts, int *errmaj, int *errmin)
{
    if (opts) {
	pointer o = xf86FindOption(opts, "IADebugLevel");
	if (o) {
	    IADebugLevel = xf86SetIntOption(opts, "IADebugLevel", 0);
	}
    }
    LoadExtension(&IAExt, FALSE);

    /* Need a non-NULL return */
    return (pointer)1;
}
