/* Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
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


#include "config.h"
#include <xorg-server.h>

#include "xf86.h"
#include "xf86Priv.h"
#include "xf86Xinput.h"
#include "xf86_OSproc.h"
#include <X11/XF86keysym.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <libsysevent.h>
#include <xkbsrv.h>

static int HkeyPreInit(InputDriverPtr drv, InputInfoPtr pInfo, int flags);
static void HkeyUnInit(InputDriverPtr drv, InputInfoPtr pInfo, int flags);

_X_EXPORT InputDriverRec HKEY = {
        1,
        "hotkey",
        NULL,
        HkeyPreInit,
        HkeyUnInit,
        NULL,
        0
};

static struct {
    const char	*sub_class;
    KeySym	keysym;
} sub_to_keysym_table [] = {
    { "ESC_acpiev_display_switch", 	XF86XK_Display },
    { "ESC_acpiev_sleep",	 	XF86XK_Sleep },	
    { "ESC_acpiev_screen_lock",		XF86XK_ScreenSaver },
    { NULL,				NoSymbol }
};


#define	EC_ACPIEV			"EC_acpiev"
#define HOTKEY_KEYSYM_ROOT		(XF86XK_Display & 0xFFFFFF00)

static sysevent_handle_t	*hotkey_event_entry;
static int 			hotkey_event_fd[2] = {-1, -1};

static void 
hotkey_event_handler(sysevent_t *ev)
{
    int		i;
    char	buf;
    char	*subclass;
    KeySym	keysym = 0;

    subclass = sysevent_get_subclass_name(ev);
    for (i = 0; sub_to_keysym_table[i].sub_class != NULL; i++)
	if (!strcmp (sub_to_keysym_table[i].sub_class, subclass)) {
	    keysym = sub_to_keysym_table[i].keysym;
	    break;
	}

    if (sub_to_keysym_table[i].sub_class == NULL)
	return;

    buf = keysym - HOTKEY_KEYSYM_ROOT;

    write(hotkey_event_fd[1], &buf, 1);
}


static  Bool 
map_init(DeviceIntPtr device) 
{

#if GET_ABI_MAJOR(ABI_XINPUT_VERSION) >= 5
    if (!InitKeyboardDeviceStruct(device, NULL, NULL, NULL)) {
	xf86Msg(X_WARNING, "hotkey map_init failed\n");
	return FALSE;
    }
#else
    KeySymsRec  keySyms;
    CARD8	*modMap;

    keySyms.minKeyCode = inputInfo.keyboard->key->curKeySyms.minKeyCode;
    keySyms.maxKeyCode = inputInfo.keyboard->key->curKeySyms.maxKeyCode;
    keySyms.mapWidth = inputInfo.keyboard->key->curKeySyms.mapWidth;

    keySyms.map = (KeySym *)xcalloc(sizeof(KeySym),
	(keySyms.maxKeyCode - keySyms.minKeyCode + 1) * keySyms.mapWidth);
    if (!keySyms.map) {
	xf86Msg (X_WARNING, "Couldn't allocate hotkey core keymap\n");
	return FALSE;
    }

    modMap = (CARD8 *)xcalloc(1, MAP_LENGTH);
    if (!modMap) {
	xf86Msg (X_WARNING, "Couldn't allocate hotkey modifier keymap\n");
	return FALSE;
    }

#ifdef XKB
    if (!noXkbExtension) {
	XkbComponentNamesRec names;

	bzero(&names, sizeof(names));
	XkbInitKeyboardDeviceStruct(device, &names, &keySyms, modMap, NULL, NULL);
    } else
#endif
	/* FIXME Our keymap here isn't exactly useful. */
    InitKeyboardDeviceStruct((DevicePtr)device, &keySyms, modMap, NULL, NULL);

    xfree(keySyms.map);
    xfree(modMap);
#endif

    return TRUE;
}

static void
hotkey_events_fini(void)
{
    sysevent_unsubscribe_event (hotkey_event_entry, EC_ACPIEV);
    sysevent_unbind_handle (hotkey_event_entry);
    hotkey_event_entry = NULL;
    xf86Msg(X_CONFIG, "hotkey_events_fini: succeeded\n");
}

static	Bool
hotkey_events_init(DeviceIntPtr device) {
    const char	*subclass_list[] = {EC_SUB_ALL};

    hotkey_event_entry = sysevent_bind_handle (hotkey_event_handler);
    if (hotkey_event_entry == NULL) {
	xf86Msg(X_WARNING, 
	    "hotkey_events_init: sysevent_bind_handle failed: with errno = %d\n" , errno);
	return FALSE;
    }
    else {
	if (sysevent_subscribe_event(hotkey_event_entry, EC_ACPIEV, subclass_list, 1)
	    != 0) {
	    sysevent_unbind_handle(hotkey_event_entry);
	    hotkey_event_entry = NULL;
	    xf86Msg(X_CONFIG, "hotkey_events_init: sysevent_subscribe_event failed\n");
	    return FALSE;
	}
    }

    return  TRUE;
}

static void
hotkey_read_input(InputInfoPtr pInfo)
{
    unsigned char	buf;
    KeySym	keysym = NoSymbol;
    KeyCode	keycode = 0;
    KeySymsPtr	curKeySyms;
    DeviceIntPtr	dev = pInfo->dev;
    int         i;

    if (read (pInfo->fd, &buf, 1 ) == 1)
	keysym = buf + HOTKEY_KEYSYM_ROOT;

#if GET_ABI_MAJOR(ABI_XINPUT_VERSION) >= 5
    if (dev->master)
	curKeySyms = XkbGetCoreMap(dev->master);
    else
	curKeySyms = XkbGetCoreMap(inputInfo.keyboard);
#else
    if (dev->master)
	curKeySyms = &dev->master->key->curKeySyms;
    else
	curKeySyms = &inputInfo.keyboard->key->curKeySyms;
#endif

    for (i = curKeySyms->minKeyCode; i <= curKeySyms->maxKeyCode; i++) {
	if (curKeySyms->map[(i - curKeySyms->minKeyCode) * curKeySyms->mapWidth] 
	    == keysym) {
	    keycode = i;
	    break;
	}
    }

    if (!keycode)
	xf86MsgVerb(X_WARNING, 0, "Hotkey keysym %x not mapped\n", (int) keysym);
    else {
	xf86MsgVerb(X_INFO, 3, "Posting keycode %d for keysym %x on device %s\n", 
		keycode, (int) keysym, pInfo->dev->name);
	xf86PostKeyboardEvent(pInfo->dev, keycode, TRUE);
	xf86PostKeyboardEvent(pInfo->dev, keycode, FALSE);
    }
}

static int
HkeyProc(DeviceIntPtr device, int what)
{
    InputInfoPtr pInfo = device->public.devicePrivate;
    char	 *s;
    DeviceIntPtr mdev;
    int		blocked;

    switch (what) {
     	case DEVICE_INIT:
	    if (!map_init(device)) {
		xf86Msg(X_WARNING, "HkeyProc: map_init failed\n");
		return (!Success);
	    }

	    /* 
	     * Block SIGIO so the new libsysevent/door threads created will
	     * mask SIGIO. See 6875743.
	     */
	    blocked = xf86BlockSIGIO();

	    if (hotkey_events_init(device)) {
		if (pipe (hotkey_event_fd) == -1) {
		    xf86Msg(X_WARNING,
		    "hotkey_events_init: pipe open failed with errno %d\n", errno);
		    hotkey_events_fini();
	    	    xf86UnblockSIGIO(blocked);
		    return (!Success);
		} else {
		    pInfo->fd = hotkey_event_fd[0];
		    xf86Msg(X_CONFIG, "hotkey_events_init and pipe open succeeded\n");
                }
            } else {
		xf86Msg(X_WARNING, "hotkey_events_init failed\n");
	    	xf86UnblockSIGIO(blocked);
		return (!Success);
	    }

	    xf86UnblockSIGIO(blocked);

    	    device->public.on = FALSE;
	    break;
	case DEVICE_ON:
    	    if (device->public.on)
	    	break;
	    xf86FlushInput(pInfo->fd);
	    AddEnabledDevice(pInfo->fd);

	    if (device->master)
		dixSetPrivate(&device->master->devPrivates, 
		    HotkeyMapDevicePrivateKey, device);

	    device->public.on = TRUE;
	    break;
	case DEVICE_CLOSE:
	    if (pInfo->fd != -1)
		RemoveEnabledDevice(pInfo->fd);
	    close(hotkey_event_fd[0]);
	    close(hotkey_event_fd[1]);
	    hotkey_events_fini();
	    break;
	case DEVICE_OFF:
	    if (!device->public.on)
		break;
	    if (pInfo->fd != -1)
		RemoveEnabledDevice(pInfo->fd);

	    if (device->master)
		dixSetPrivate(&device->master->devPrivates, 
		    HotkeyMapDevicePrivateKey, NULL);

    	    device->public.on = FALSE;
	    break;
    }

    return (Success);
}

static int
HkeyPreInit(InputDriverPtr drv, InputInfoPtr pInfo, int flags)
{
    /* Initialize the InputInfoRec. */
    pInfo->type_name = XI_KEYBOARD;
    pInfo->device_control = HkeyProc;
    pInfo->read_input = hotkey_read_input;
    pInfo->fd = -1;
    pInfo->flags = XI86_ALWAYS_CORE;

    return Success;
}

static void
HkeyUnInit(InputDriverPtr drv, InputInfoPtr pInfo, int flags)
{
    xf86DeleteInput(pInfo, 0);
}

static void
HkeyUnplug(pointer p)
{
}

static pointer
HkeyPlug(pointer module, pointer options, int *errmaj, int *errmin)
{
    static Bool Initialised = FALSE;

    if (!Initialised)
        Initialised = TRUE;

    xf86AddInputDriver(&HKEY, module, 0);

    return module;
}


static XF86ModuleVersionInfo HkeyVersionRec = {
    "hotkey",
    MODULEVENDORSTRING,
    MODINFOSTRING1,
    MODINFOSTRING2,
    XORG_VERSION_CURRENT,
    1, 0, 0,
    ABI_CLASS_XINPUT,
    ABI_XINPUT_VERSION,
    MOD_CLASS_XINPUT,
    {0, 0, 0, 0}                /* signature, to be patched into the file by */
                                /* a tool */
};

_X_EXPORT XF86ModuleData hotkeyModuleData = {
    &HkeyVersionRec,
    HkeyPlug,
    HkeyUnplug
};

