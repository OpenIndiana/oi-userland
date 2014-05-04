/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. All rights reserved.
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


/*
 * tsol.h server side extension
 */

#define NEED_REPLIES
#define NEED_EVENTS
#define _XTSOL_SERVER

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include <X11/X.h>
#include <X11/Xproto.h>
#include "misc.h"
#include "os.h"
#include "windowstr.h"
#include "input.h"
#include "scrnintstr.h"
#include "pixmapstr.h"
#include "extnsionst.h"
#include "dixstruct.h"
#include "gcstruct.h"
#include "propertyst.h"
#include "validate.h"
#include <X11/extensions/Xtsol.h>
#include <X11/extensions/Xtsolproto.h>

#include "tsolinfo.h"

#ifndef CALLBACK
# define CALLBACK(name) void \
name(CallbackListPtr *pcbl, pointer nulldata, pointer calldata)
#endif

/* tsolutils.c */
extern void init_xtsol(void);
extern void InitHotKey(DeviceIntPtr keybd);
extern void HandleHotKey(DeviceIntPtr keybd);
extern void LoadTsolConfig(void);
extern void MakeTSOLAtoms(void);
extern int SpecialName(const char *string, int len);
extern TsolInfoPtr GetClientTsolInfo(ClientPtr client);
extern bslabel_t *lookupSL_low(void);
extern int PolyPropReadable(PropertyPtr pProp, ClientPtr client);
extern WindowPtr TsolPointerWindow(void);
extern int DoScreenStripeHeight(int screen_num);
extern int AddUID(int *userid);
extern WindowPtr AnyWindowOverlapsJustMe(WindowPtr pWin,
	WindowPtr pHead, BoxPtr box);

extern Bool priv_win_colormap;
extern Bool priv_win_config;
extern Bool priv_win_devices;
extern Bool priv_win_dga;
extern Bool priv_win_fontpath;

extern WindowPtr tpwin;
extern bclear_t SessionHI;        /* HI Clearance */
extern bclear_t SessionLO;        /* LO Clearance */
extern unsigned int StripeHeight;
extern bslabel_t        PublicObjSL;

extern Atom tsol_lastAtom;
extern int tsol_nodelength;
extern TsolNodePtr tsol_node;


/* tsolextension.c */
extern void TsolExtensionInit(void);
extern int tsolMultiLevel;
extern int (*TsolSavedProcVector[PROCVECTORSIZE])(ClientPtr /*client*/);
extern int (*TsolSavedSwappedProcVector[PROCVECTORSIZE])(ClientPtr /*client*/);

/* tsolprotocol.c */
extern void UpdateTsolNode(Atom thisAtom, ClientPtr client);
extern int TsolChangeWindowProperty(ClientPtr, WindowPtr, Atom, Atom, int, int,
	unsigned long, pointer, Bool);
extern int TsolDeleteProperty(ClientPtr, WindowPtr, Atom);
extern int TsolInitWindow(ClientPtr, WindowPtr);
extern int TsolInitPixmap(ClientPtr, PixmapPtr);
extern void TsolDeleteClientFromAnySelections(ClientPtr);
extern void TsolDeleteWindowFromAnySelections(WindowPtr);

extern int ProcTsolInternAtom(ClientPtr client);
extern int ProcTsolGetAtomName(ClientPtr client);
extern int ProcTsolSetSelectionOwner(ClientPtr client);
extern int ProcTsolGetSelectionOwner(ClientPtr client);
extern int ProcTsolConvertSelection(ClientPtr client);
extern int ProcTsolGetProperty(ClientPtr client);
extern int ProcTsolListProperties(ClientPtr client);
extern int ProcTsolChangeKeyboardMapping(ClientPtr client);
extern int ProcTsolSetPointerMapping(ClientPtr client);
extern int ProcTsolChangeKeyboardControl(ClientPtr client);
extern int ProcTsolBell(ClientPtr client);
extern int ProcTsolChangePointerControl(ClientPtr client);
extern int ProcTsolSetModifierMapping(ClientPtr client);

extern int ProcTsolCreateWindow(ClientPtr client);
extern int ProcTsolChangeWindowAttributes(ClientPtr client);
extern int ProcTsolConfigureWindow(ClientPtr client);
extern int ProcTsolCirculateWindow(ClientPtr client);
extern int ProcTsolReparentWindow(ClientPtr client);
extern int ProcTsolSetInputFocus(ClientPtr client);
extern int ProcTsolGetInputFocus(ClientPtr client);
extern int ProcTsolSendEvent(ClientPtr client);
extern int ProcTsolSetInputFocus(ClientPtr client);
extern int ProcTsolGetInputFocus(ClientPtr client);
extern int ProcTsolGetGeometry(ClientPtr client);
extern int ProcTsolGrabServer(ClientPtr client);
extern int ProcTsolUngrabServer(ClientPtr client);
extern int ProcTsolCreatePixmap(ClientPtr client);
extern int ProcTsolSetScreenSaver(ClientPtr client);
extern int ProcTsolChangeHosts(ClientPtr client);
extern int ProcTsolChangeAccessControl(ClientPtr client);
extern int ProcTsolKillClient(ClientPtr client);
extern int ProcTsolSetFontPath(ClientPtr client);
extern int ProcTsolChangeCloseDownMode(ClientPtr client);
extern int ProcTsolListInstalledColormaps(ClientPtr client);
extern int ProcTsolGetImage(ClientPtr client);
extern int ProcTsolQueryTree(ClientPtr client);
extern int ProcTsolQueryPointer(ClientPtr client);
extern int ProcTsolQueryExtension(ClientPtr client);
extern int ProcTsolListExtensions(ClientPtr client);
extern int ProcTsolMapWindow(ClientPtr client);
extern int ProcTsolMapSubwindows(ClientPtr client);
extern int ProcTsolCopyArea(ClientPtr client);
extern int ProcTsolCopyPlane(ClientPtr client);
extern int ProcTsolPolySegment(ClientPtr client);
extern int ProcTsolPolyRectangle(ClientPtr client);

extern int TsolPanoramiXGetGeometry(ClientPtr client);

extern CALLBACK(TsolAuditStart);
extern CALLBACK(TsolAuditEnd);
