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


#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#define NEED_EVENTS
#include <stdio.h>
#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/Xprotostr.h>
#include "auditwrite.h"
#include <bsm/audit_uevents.h>
#include <regex.h>
#include <priv.h>
#include <X11/Xproto.h>
#include "windowstr.h"
#include "scrnintstr.h"
#include "xkbstr.h"
#include "xkbsrv.h"
#include  "tsol.h"
#include  "tsolinfo.h"
#include  "tsolpolicy.h"
#include  <X11/keysym.h>
#include  "misc.h"
#include  "inputstr.h"
#include  "propertyst.h"
#include  "panoramiXsrv.h"
#include  "registry.h"

#define	MAX_SL_ENTRY	256
#define	MAX_UID_ENTRY	64
#define	ALLOCATED	1
#define	EMPTIED		0
#define	FamilyTSOL	5
#define	TSOLUIDlength	4

#define BOXES_OVERLAP(b1, b2) \
      (!( ((b1)->x2 <= (b2)->x1)  || \
	( ((b1)->x1 >= (b2)->x2)) || \
	( ((b1)->y2 <= (b2)->y1)) || \
	( ((b1)->y1 >= (b2)->y2)) ) )

Bool system_audit_on = FALSE;
Bool priv_win_colormap = FALSE;
Bool priv_win_config = FALSE;
Bool priv_win_devices = FALSE;
Bool priv_win_dga = FALSE;
Bool priv_win_fontpath = FALSE;


/*
 * The following need to be moved to tsolextension.c
 * after all references in Xsun is pulled out
 */
WindowPtr tpwin = NULL;	   /* only one trusted path window at a time */
TsolPolyInstInfoRec tsolpolyinstinfo;
#define TsolMaxPolyNameSize 80
/*
 * Use the NodeRec struct in tsolinfo.h. This is referenced
 * in policy routines. So we had to move it there
 */
static TsolPolyAtomRec tsolpolyprop = {FALSE, 0, 0, NULL};
static TsolPolyAtomRec tsolpolyseln = {TRUE, 0, 0, NULL};


/*
 * Key to lookup devPrivate data in various structures
 */
static int tsolPrivateKeyIndex;
DevPrivateKey tsolPrivateKey = &tsolPrivateKeyIndex;

bclear_t SessionHI;	   /* HI Clearance */
bclear_t SessionLO;	   /* LO Clearance */
unsigned int StripeHeight = 0;
uid_t OwnerUID = (uid_t)(-1);
bslabel_t PublicObjSL;

Atom tsol_lastAtom = None;
int tsol_nodelength  = 0;
TsolNodePtr tsol_node = NULL;

/* This structure is used for protocol request ListHosts */
struct xUIDreply
{
	unsigned char	family;
	unsigned char	pad;
	unsigned short	length;
	int		uid;		/* uid type */
};

struct slentry
{
	bslabel_t	senlabel;
	char		allocated;
};

static struct slentry sltable[MAX_SL_ENTRY];

/* This table contains list of users who can connect to the server */
struct uidentry
{
	int		userid;		/* uid type */
	char		allocated;
};

static struct uidentry uidtable[MAX_UID_ENTRY];

/* Index must match with keywords */
static char *tsolconfig_keywords[] = {"atom", "property", "selection",
	"extension", "privilege"};

#define KEYWORDCOUNT sizeof(tsolconfig_keywords)/sizeof(char *)

typedef struct _TsolConfig
{
	int count;
	char **list;
} TsolConfigRec;

static TsolConfigRec tsolconfig[KEYWORDCOUNT] = {
	{0, NULL},
	{0, NULL},
	{0, NULL},
	{0, NULL},
	{0, NULL}
};

#define TSOL_ATOMCOUNT 4
static const char *tsolatomnames[TSOL_ATOMCOUNT] = {
	"_TSOL_CMWLABEL_CHANGE",
	"_TSOL_GRABNOTIFY",
	"_TSOL_CLIENT_TERM",
	"_TSOL_SEL_AGNT"
};

static void
init_TSOL_cached_SL(void)
{
	sltable[0].allocated = ALLOCATED;
	bsllow (&(sltable[0].senlabel));

	sltable[1].allocated = ALLOCATED;
	bslhigh(&(sltable[1].senlabel));

}

/* Initialize UID table, this table should at least contains owner UID */
static void
init_TSOL_uid_table(void)
{
	uidtable[0].allocated = ALLOCATED;
	uidtable[0].userid    = 0;
}

#if UNUSED
/*  Count how many valid entried in the uid table */
int
count_uid_table(void)
{
	int i, count = 0;

	/* Search entire table */
	for (i = 0; i < MAX_UID_ENTRY; i++)
	{
		if (uidtable[i].allocated == ALLOCATED)
			count++;
	}
	return (count);
}

/* return (1); if userid is in the table */
int
lookupUID(int userid)
{
	int i;
	for (i = 0; i < MAX_UID_ENTRY; i++)
	{
		if (uidtable[i].allocated == ALLOCATED &&
			uidtable[i].userid == userid)
		{
			return (1); /* yes, found it */
		}
	}
	return (0); /* not found */
}

/* Passed into a pointer to a storage which is used to store UID */
/* and nUid represents how many UID in the table(returned by count_uid_table) */
int
ListUID(
    struct xUIDreply 	* uidaddr,
    int			nUid)
{
	int i, j = 0;

	for (i = 0; i < MAX_UID_ENTRY; i++)
	{
		if (uidtable[i].allocated == ALLOCATED)
		{
			uidaddr[j].family = FamilyTSOL;
			uidaddr[j].length = TSOLUIDlength;
			uidaddr[j].uid    = uidtable[i].userid;
			j++;
		}
	}
	if (nUid != j)
	{
		ErrorF("Invalid no. of uid entries? \n");
		return (0);
	}

	return (1);
}
#endif /* UNUSED */

/* add userid into UIDtable  */
int
AddUID(int *userid)
{

	int i = 0;

	/*
	 * Search entire uidtable, to prevent duplicate uid
	 * entry in the table
	 */
	while (i < MAX_UID_ENTRY)
	{
		if ((uidtable[i].allocated == ALLOCATED) &&
			(uidtable[i].userid == *userid))
		{
			/* this uid entry is already in the table; no-op */
			return (1); /* Success, uid in the table */
		}
		i++;
	}

	i = 0;
	/*
	 * If we can find an empty entry, then add this uid
	 * into the table
	 */
	while (i < MAX_UID_ENTRY)
	{
		if (uidtable[i].allocated != ALLOCATED)
		{
			uidtable[i].allocated = ALLOCATED;
			uidtable[i].userid = *userid;
			return (1); /* Success, uid in the table */
		}
		i++;
	}

	/* uidtable overflow */
	ErrorF("Server problem: Please enlarge the table size of uidtable \n");
	return (0);
}

#if UNUSED
/* remove userid from UIDtable */
int
RemoveUID(int *userid)
{
	int i = 0;

	if (*userid == 0)
	{
		ErrorF("\n UID 0 can not be removed from server UID list");
		return (0);
	}

	while (i < MAX_UID_ENTRY)
	{
		if ((uidtable[i].allocated == ALLOCATED) &&
			(uidtable[i].userid == *userid))
		{
			/* delete this entry in the table */
			uidtable[i].allocated = EMPTIED;
			return (1); /* Success, uid in the table */

		}
		i++;
	}

	/* no such entry in the table, why delete it? no-op */
	return (0);
}
#endif




bslabel_t *
lookupSL_low(void)
{
	return (&(sltable[0].senlabel));
}


bslabel_t *
lookupSL(bslabel_t *slptr)
{
	int i = 0;

	if (slptr == NULL)
		return (slptr);

	while ((i < MAX_SL_ENTRY) && sltable[i].allocated == ALLOCATED)
	{
		if (blequal(slptr, &(sltable[i].senlabel)))
		{
			/* found a matching sensitivity label in sltable */
			return (&(sltable[i].senlabel));
		}
		i++;
	}

	if (i < MAX_SL_ENTRY)
	{
		/*
		 * can't find a matching entry in sltable,
		 * however, we have empty entry to store this
		 * new sensitivity label; store it.
		 */
		sltable[i].allocated = ALLOCATED;
		memcpy (&(sltable[i].senlabel), slptr, sizeof (bslabel_t));
		return (&(sltable[i].senlabel));
	}

	/*
	 * no matching entry in sltable, and no room to
	 * store this new sensitivity label,
	 * the server needs to recomplie with a larger slabel
	 */

	ErrorF("Server problem: Please enlarge the table size of sltable \n");
	return (NULL);
}

static const int padlength[4] = {0, 3, 2, 1};

/* Updated version based roughly on RREditConnectionInfo in randr/rrscreen.c */
int
DoScreenStripeHeight(int screen_num)
{
	int 		i, j;
	xConnSetup      *connSetup;
	char            *vendor;
	xPixmapFormat   *formats;
	xWindowRoot     *root;
	xDepth          *depth;
	xVisualType     *visual;
	ScreenPtr	pScreen;
        int             old_height;
        float           height_mult;

	connSetup = (xConnSetup *) ConnectionInfo;
	vendor = (char *) connSetup + sizeof (xConnSetup);
	formats = (xPixmapFormat *) ((char *) vendor +
				     connSetup->nbytesVendor +
				     padlength[connSetup->nbytesVendor & 3]);
	root = (xWindowRoot *) ((char *) formats +
				sizeof (xPixmapFormat) *
				screenInfo.numPixmapFormats);
	for (i = 0; i < screen_num; i++)
	{
		depth = (xDepth *) ((char *) root + 
                            sizeof (xWindowRoot));
		for (j = 0; j < (int)root->nDepths; j++)
		{
			visual = (xVisualType *) ((char *) depth +
						  sizeof (xDepth));
			depth = (xDepth *) ((char *) visual +
					    depth->nVisuals *
					    sizeof (xVisualType));

		}
		root = (xWindowRoot *) ((char *) depth);
	}
        old_height = root->pixHeight;

        if (noPanoramiXExtension)
        {
            pScreen = screenInfo.screens[screen_num];
            root->pixHeight = pScreen->height - StripeHeight;
        } else
        {
            root->pixHeight = PanoramiXPixHeight - StripeHeight;
        }

        /* compute new millimeter height */
        height_mult = (1.0 * root->pixHeight) / old_height;
        root->mmHeight *= height_mult;

	return (0);
}

extern int cannot_audit(int);	/* bsm function */

void
init_xtsol(void)
{
	bclearhigh(&SessionHI);
	bclearlow(&SessionLO);
	bsllow(&PublicObjSL);
	init_TSOL_cached_SL();
	init_TSOL_uid_table();

	if (cannot_audit(TRUE))
		system_audit_on = FALSE;
	else
		system_audit_on = TRUE;

	auditwrite(AW_QUEUE, XAUDIT_Q_SIZE, AW_END);
}

/*
 * Converts keycode to keysym, helper function.
 * Modelled after Xlib code
 */
static KeySym
KeycodetoKeysym(KeyCode keycode, int col, KeySymsPtr curKeySyms)
{
    int per = curKeySyms->mapWidth;
    KeySym *syms = curKeySyms->map;
    KeySym lsym = 0, usym = 0;

    if ((col < 0) || ((col >= per) && (col > 3)) ||
	((int)keycode < curKeySyms->minKeyCode) ||
        ((int)keycode > curKeySyms->maxKeyCode))
      return NoSymbol;

    syms = &curKeySyms->map[(keycode - curKeySyms->minKeyCode) * per];
    if (col < 4) {
	if (col > 1) {
	    while ((per > 2) && (syms[per - 1] == NoSymbol))
		per--;
	    if (per < 3)
		col -= 2;
	}
	if ((per <= (col|1)) || (syms[col|1] == NoSymbol)) {
	    if (!(col & 1))
		return lsym;
	    else if (usym == lsym)
		return NoSymbol;
	    else
		return usym;
	}
    }
    return syms[col];
}

/*
 * Converts keysym to a keycode
 * Modelled after Xlib code
 */
static KeyCode
KeysymToKeycode(KeySym ks, KeySymsPtr curKeySyms)
{
    int i, j;

    for (j = 0; j < curKeySyms->mapWidth; j++) {
	for (i = curKeySyms->minKeyCode; i <= curKeySyms->maxKeyCode; i++) {
	    if (KeycodetoKeysym((KeyCode) i, j, curKeySyms) == ks)
		return i;
	}
    }
    return 0;
}

/*
 * converts a keysym to modifier equivalent mask
 * Modelled after Xlib
 */
static unsigned
KeysymToModifier(KeySym ks, KeySymsPtr keysyms,
		 KeyCode *modifierKeyMap, int maxKeysPerModifier) 
{
    CARD8 code, mods;
    KeySym *kmax;
    KeySym *k;

    kmax = keysyms->map + (keysyms->maxKeyCode - keysyms->minKeyCode + 1) *
	keysyms->mapWidth;
    k = keysyms->map;
    mods = 0;
    while (k < kmax) {
        if (*k == ks ) {
            int j = maxKeysPerModifier << 3;

            code = (((k - keysyms->map) / keysyms->mapWidth) + keysyms->minKeyCode);

            while (--j >= 0) {
                if (code == modifierKeyMap[j])
                    mods |= (1 << (j / maxKeysPerModifier));
            }
        }
        k++;
    }
    return mods;
}

/*
 * Initialize Hot Key keys. On A Sun type 5/6 keyboard
 * It's Meta(Diamond) + Stop. On a non-Sun keyboard, it's
 * Alt + Break(Pause) key. Hold down the meta or alt key
 * press stop or break key.
 *
 * NOTE:
 * Both Left & Right keys for (Meta or Alt) return the
 * same modifier mask
 */
void
InitHotKey(DeviceIntPtr keybd)
{
	HotKeyPtr hk = TsolKeyboardPrivate(keybd);
	KeySymsPtr curKeySyms = XkbGetCoreMap(keybd);
	int rc;
	int max_keys_per_mod = 0;
	KeyCode *modkeymap = NULL;

	rc = generate_modkeymap(serverClient, keybd,
				&modkeymap, &max_keys_per_mod);

	/* Meta + Stop */
	hk->shift = KeysymToModifier(XK_Meta_L, curKeySyms,
				     modkeymap, max_keys_per_mod);
	hk->key = KeysymToKeycode(XK_L1, curKeySyms);

	/* Alt + Break/Pause */
	hk->altshift = KeysymToModifier(XK_Alt_L, curKeySyms,
					modkeymap, max_keys_per_mod);
	hk->altkey = KeysymToKeycode(XK_Pause, curKeySyms);

	hk->initialized = TRUE;
}

static void
UpdateTsolConfig(char *keyword, char *value)
{
	int i;
	int count;
	char **newlist;

	if (keyword == NULL || value == NULL)
		return; /* ignore incomplete entries */

	/* find a matching keyword */
	for (i = 0; i < KEYWORDCOUNT; i++) {
		if (strcmp(keyword, tsolconfig_keywords[i]) == 0) {
			break;
		}
	}

	/* Invalid keyword */
	if (i >= KEYWORDCOUNT) {
		ErrorF("Invalid keyword : %s\n", keyword);
		return;
	}

	count = tsolconfig[i].count;
	newlist = (char **)Xrealloc(tsolconfig[i].list, (count + 1) * sizeof(char **));
	if (newlist == NULL) {
		ErrorF("Not enough memory for %s %s\n", keyword, value);
		return;
	}

	newlist[count] = strdup(value);
	tsolconfig[i].list = newlist;
	tsolconfig[i].count++;
}

static void
InitPrivileges(void)
{
	int i;
	int count;
	char **list;

	count = tsolconfig[TSOL_PRIVILEGE].count;
	list = tsolconfig[TSOL_PRIVILEGE].list;

	for (i = 0; i < count; i++) {
		if (strcmp(list[i], PRIV_WIN_COLORMAP) == 0)
			priv_win_colormap = TRUE;
		else if (strcmp(list[i], PRIV_WIN_CONFIG) == 0)
			priv_win_config = TRUE;
		else if (strcmp(list[i], PRIV_WIN_DEVICES) == 0)
			priv_win_devices = TRUE;
		else if (strcmp(list[i], PRIV_WIN_FONTPATH) == 0)
			priv_win_fontpath = TRUE;
		else if (strcmp(list[i], PRIV_WIN_DGA) == 0)
			priv_win_dga = TRUE;
	}
}

/*
 * Load Trusted Solaris configuration file
 */
void
LoadTsolConfig(void)
{
	FILE *fp;
	char buf[BUFSIZ];
	char *keyword;
	char *value;

	/* open the file from /etc first followed by /usr */
	if ((fp = fopen(TSOLPOLICYFILE, "r")) == NULL) {
		ErrorF("Cannot load %s. Some desktop applications may not\n"
			"work correctly\n", TSOLPOLICYFILE);
			return;
	}

	/* Read and parse the config file */
	while (fgets(buf, sizeof (buf), fp) != NULL) {

		/* ignore all comments, lines starting with white space */
		if (buf[0] == '#' || isspace((int)buf[0]))
			continue;

		keyword = strtok(buf, " \t");
		value = strtok(NULL, " \t\n");
		UpdateTsolConfig(keyword, value);
	}

	InitPrivileges();
}


/*
 *	It does not really tell if this atom is to be polyinstantiated
 *	or not. Further check should be done to determine this.
 */
int
SpecialName(const char *string, int len)
{

	return (MatchTsolConfig(string, len));
}


void
MakeTSOLAtoms(void)
{
	int i;
	char *atomname;

	/* Create new TSOL atoms */
	for (i = 0; i < TSOL_ATOMCOUNT; i++) {
		if (MakeAtom(tsolatomnames[i], strlen(tsolatomnames[i]), TRUE) == None)
			AtomError();
	}

	/* Create atoms defined in config file */
	for (i = 0; i < tsolconfig[TSOL_ATOM].count; i++) {
		atomname = tsolconfig[TSOL_ATOM].list[i];
		if (MakeAtom(atomname, strlen(atomname), TRUE) == None) {
			AtomError();
		}
	}
}

/*
 *	Names starting with a slash in selection.atoms and property.atoms
 *	are treated as regular expressions to be matched against the
 *	selection and property names.  They may optionally end with a slash.
 */
static int
regexcompare(const char *string, int len, char *regexp)
{
	int	status;
	regex_t	compiledregexp;
	char	*regexpstrp;
	int	regexpstrlen;
	char	buffer[BUFSIZ];

	if (regexp[0] == '/' && len < BUFSIZ) {
		/* Extract regular expression from between slashes */
		regexpstrp = regexp + 1;
		regexpstrlen = strlen(regexpstrp);
		if (regexpstrp[regexpstrlen - 1] == '/')
			regexpstrp[regexpstrlen - 1] = '\0';
		/* Compile the regular expression */
		status = regcomp(&compiledregexp, regexpstrp,
		    REG_EXTENDED | REG_NOSUB);
		if (status == 0) {
			/* Make null-terminated copy of string */
			memcpy(buffer, string, len);
			buffer[len] = '\0';
			/* Compare string to regular expression */
			status = regexec(&compiledregexp,
			    buffer, (size_t) 0, NULL, 0);
			regfree(&compiledregexp);

			if (status == 0)
				return (TRUE);
			else
				return (FALSE);
		}
	} else if (strncmp(string, regexp, len) == 0) {
		return (TRUE);
	}

	return (FALSE);
}

int
MatchTsolConfig(const char *name, int len)
{
	int i;
	int count;
	char **list;
	unsigned int flags = 0;

	count = tsolconfig[TSOL_PROPERTY].count;
	list = tsolconfig[TSOL_PROPERTY].list;
	for (i = 0; i < count; i++) {
		if (regexcompare(name, len, list[i])) {
			flags |= TSOLM_PROPERTY;
			break;
		}
	}

	count = tsolconfig[TSOL_SELECTION].count;
	list = tsolconfig[TSOL_SELECTION].list;
	for (i = 0; i < count; i++) {
		if (regexcompare(name, len, list[i])) {
			flags |= TSOLM_SELECTION;
			break;
		}
	}

	return (flags);
}

TsolInfoPtr
GetClientTsolInfo(ClientPtr client)
{
    return TsolClientPrivate(client);
}

/* Property is polyinstantiated only on root window */
int
PolyProperty(Atom atom, WindowPtr pWin)
{
	if (WindowIsRoot(pWin) &&
		((!tsolpolyprop.polyinst && !(tsol_node[atom].IsSpecial & TSOLM_PROPERTY)) ||
		(tsolpolyprop.polyinst && (tsol_node[atom].IsSpecial & TSOLM_PROPERTY))))
		return TRUE;
	return FALSE;
}

int
PolySelection(Atom atom)
{
	if ((tsolpolyseln.polyinst && (tsol_node[atom].IsSpecial & TSOLM_SELECTION)) ||
		(!tsolpolyseln.polyinst && !(tsol_node[atom].IsSpecial & TSOLM_SELECTION)))
		return TRUE;
	return FALSE;
}

/*
 * client_private returns true if xid is owned/created by
 * client or is a default server xid
 */
int
client_private (ClientPtr client, XID xid)
{
	if (same_client(client, xid) || (xid & SERVER_BIT))
		return TRUE;
	else
		return FALSE;
}
/*
 * Same as TopClientWin()
 * except that it returns a Window ID
 * and not a ptr
 */
Window
RootOfClient(WindowPtr pWin)
{
    if (pWin)
    {
	return (TopClientWin(pWin)->drawable.id);
    }
    return (NULL);
}

#ifdef UNUSED
/*
 * Return root window of pWin
 */
WindowPtr
RootWin(WindowPtr pWin)
{
    if (pWin)
    {
        while (pWin->parent)
            pWin = pWin->parent;
    }
    return (pWin);
}
#endif

Window
RootOf(WindowPtr pWin)
{
    if (pWin)
    {
        while (pWin->parent)
            pWin = pWin->parent;
        return (pWin->drawable.id);
    }
    return (NULL);
}


/*
 * same_client returns true if xid is owned/created by
 * client
 */
int
same_client (ClientPtr client, XID xid)
{
	TsolInfoPtr tsolinfo_client;
	TsolInfoPtr tsolinfo_xid;
	ClientPtr   xid_client;

	if (CLIENT_ID(xid) == 0 || (clients[CLIENT_ID(xid)] == NULL))
		return FALSE;

	if((SERVER_BIT & xid) == 0)
	{
		if (client->index == CLIENT_ID(xid))
			return TRUE;
		xid_client = clients[CLIENT_ID(xid)];
		tsolinfo_client = GetClientTsolInfo(client);
		tsolinfo_xid = GetClientTsolInfo(xid_client);
		if (tsolinfo_client && tsolinfo_xid && tsolinfo_client->pid > 0)
		{
			if (tsolinfo_client->pid == tsolinfo_xid->pid)
				return TRUE;
		}
	}
        return FALSE;
}

WindowPtr
AnyWindowOverlapsJustMe(
    WindowPtr pWin,
    WindowPtr pHead,
    register BoxPtr box)
{
    register WindowPtr pSib;
    BoxRec sboxrec;
    register BoxPtr sbox;
    TsolResPtr win_res = TsolResourcePrivate(pWin);

    for (pSib = pWin->prevSib; (pSib != NULL && pSib != pHead); pSib = pSib->prevSib)
    {
        TsolResPtr sib_res = TsolResourcePrivate(pSib);

        if (pSib->mapped && !bldominates(win_res->sl, sib_res->sl))
        {
            sbox = WindowExtents(pSib, &sboxrec);
            if (BOXES_OVERLAP(sbox, box)
#ifdef SHAPE
                && ShapeOverlap (pWin, box, pSib, sbox)
#endif
                )
                return(pSib);
        }
    }
    return((WindowPtr)NULL);
}
/*
 * Return Top level client window of pWin
 */
WindowPtr
TopClientWin(WindowPtr pWin)
{
    ClientPtr client;

    if (pWin)
    {
	client = wClient(pWin);
        while (pWin->parent)
	{
	    if (client != wClient(pWin->parent))
		break;
            pWin = pWin->parent;
        }
    }
    return (pWin);
}

/*
 * Matches in the list of disabled extensions via
 * the policy file (TrustedExtensionsPolicy)
 * Returns
 *  TRUE  - if a match is found
 *  FALSE - otherwise
 */
int
TsolDisabledExtension(const char *extname)
{
	int i;

	for (i = 0; i < tsolconfig[TSOL_EXTENSION].count; i++) {
	    if (strcmp(extname, tsolconfig[TSOL_EXTENSION].list[i]) == 0) {
		return TRUE;
	    }
	}

	return FALSE;
}

/*****************************************************************************/
/* Debug/error message utility functions */

/* Returns a string representation of the access mode for debugging messages */
_X_HIDDEN const char *
TsolDixAccessModeNameString(Mask access_mode) {
    static char access_mode_str[1024];
    int l = 0;

    access_mode_str[0] = '\0';

#define APPEND_MODENAME_IF_SET(mode) \
    if (access_mode & (mode)) \
	l = strlcat(access_mode_str, #mode " | ", sizeof(access_mode_str))
	
    APPEND_MODENAME_IF_SET(DixUnknownAccess);
    APPEND_MODENAME_IF_SET(DixReadAccess);
    APPEND_MODENAME_IF_SET(DixWriteAccess);
    APPEND_MODENAME_IF_SET(DixDestroyAccess);
    APPEND_MODENAME_IF_SET(DixCreateAccess);
    APPEND_MODENAME_IF_SET(DixGetAttrAccess);
    APPEND_MODENAME_IF_SET(DixSetAttrAccess);
    APPEND_MODENAME_IF_SET(DixListPropAccess);
    APPEND_MODENAME_IF_SET(DixGetPropAccess);
    APPEND_MODENAME_IF_SET(DixSetPropAccess);
    APPEND_MODENAME_IF_SET(DixGetFocusAccess);
    APPEND_MODENAME_IF_SET(DixSetFocusAccess);
    APPEND_MODENAME_IF_SET(DixListAccess);
    APPEND_MODENAME_IF_SET(DixAddAccess);
    APPEND_MODENAME_IF_SET(DixRemoveAccess);
    APPEND_MODENAME_IF_SET(DixHideAccess);
    APPEND_MODENAME_IF_SET(DixShowAccess);
    APPEND_MODENAME_IF_SET(DixBlendAccess);
    APPEND_MODENAME_IF_SET(DixGrabAccess);
    APPEND_MODENAME_IF_SET(DixFreezeAccess);
    APPEND_MODENAME_IF_SET(DixForceAccess);
    APPEND_MODENAME_IF_SET(DixInstallAccess);
    APPEND_MODENAME_IF_SET(DixUninstallAccess);
    APPEND_MODENAME_IF_SET(DixSendAccess);
    APPEND_MODENAME_IF_SET(DixReceiveAccess);
    APPEND_MODENAME_IF_SET(DixUseAccess);
    APPEND_MODENAME_IF_SET(DixManageAccess);
    APPEND_MODENAME_IF_SET(DixDebugAccess);
    APPEND_MODENAME_IF_SET(DixBellAccess);
  
    if ( (l > 3) && (l < sizeof(access_mode_str)) ) {
	/* strip off trailing " | " */
	access_mode_str[l - 3] = '\0';
    }

    return access_mode_str;
}

/* Returns a string representation of the tsol policy for debugging messages */
_X_HIDDEN const char *
TsolPolicyReturnString(int pr)
{
    if (pr == XTSOL_FAIL) {
	return "FAIL";
    } else if (pr == XTSOL_ALLOW) {
	return "ALLOW";
    } else if (pr == XTSOL_IGNORE) {
	return "IGNORE";
    } else {
	static char str[32];
	snprintf(str, sizeof(str), "<unknown value %d>", pr);
	return str;
    }
}

_X_HIDDEN const char *
TsolErrorNameString(int errcode)
{
    const char *regentry = LookupErrorName(errcode);

    if (strcmp(regentry, XREGISTRY_UNKNOWN) == 0) {
	static char unknown_string[32];

	snprintf(unknown_string, sizeof(unknown_string),
		 "error code #%d", errcode);

	return unknown_string;
    }

    return regentry;
}

_X_HIDDEN const char *
TsolResourceTypeString(RESTYPE resource)
{
    const char *regentry = LookupResourceName(resource);

    if (strcmp(regentry, XREGISTRY_UNKNOWN) == 0) {
	static char unknown_string[32];

	snprintf(unknown_string, sizeof(unknown_string),
		 "resource type #%d", (uint_t) resource);

	return unknown_string;
    }

    return regentry;
}

_X_HIDDEN const char *
TsolRequestNameString(int req)
{
    const char *regentry;

    if (req < 0) {
	return "<no request>";
    }

    regentry = LookupMajorName(req);

    if (strcmp(regentry, XREGISTRY_UNKNOWN) == 0) {
	static char unknown_string[32];

	snprintf(unknown_string, sizeof(unknown_string),
		 "request type #%d", req);

	return unknown_string;
    }

    return regentry;
}
