/* 
 * Copyright © 2001 Keith Packard, member of The XFree86 Project, Inc.
 * Copyright © 2002 Hewlett Packard Company, Inc.
 * Copyright © 2006 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 */

/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
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


#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/extensions/Xrandr.h>
#include <X11/Xos.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/proc.h>
#include <unistd.h>


static char	*program_name;
static Display	*dpy = NULL;
static Window	root, win;
static int	screen;
static Bool	nosideview = False;
static Bool	verbose = False;
static Bool	testrun = False;
static int	had_error = 0;
static XErrorHandler	prev_handler;
static int	cur_keycode;
static struct timeval	time_val;
static Rotation	init_rotation;
static int 	init_x;
static int 	init_y;
static Bool	use_init_pos = False;
static Bool	need_off_deferred = False;

static void
usage(void)
{
    fprintf(stderr, "usage: %s [options]\n", program_name);
    fprintf(stderr, "  where options are:\n");
    fprintf(stderr, "  -toggle or -t\n");
    fprintf(stderr, "  -listen or -l\n");
    fprintf(stderr, "  -display <display> or -d <display>\n");
    fprintf(stderr, "  -key <key> or -k <key>\n");
    fprintf(stderr, "  -mod <modifier> or -m <modifier>\n");
    fprintf(stderr, "  -help\n");
    fprintf(stderr, "  -nosideview\n");
    fprintf(stderr, "  -verbose or -v\n");
    fprintf(stderr, "  -testrun\n");
    exit(1);
    /*NOTREACHED*/
}

static void
fatal (const char *format, ...)
{
    va_list ap;
    
    va_start (ap, format);
    fprintf (stderr, "%s exiting: ", program_name);
    vfprintf (stderr, format, ap);
    va_end (ap);
    exit (1);
    /*NOTREACHED*/
}

static int
cur_handler (
    Display *const err_display,
    XErrorEvent *const err_event)
{
    had_error = err_event -> error_code;
    return (0);
}

typedef enum _relation {
    left_of, right_of, above, below, same_as,
} relation_t;

typedef enum _changes {
    changes_none = 0,
    changes_crtc = (1 << 0),
    changes_mode = (1 << 1),
    changes_relation = (1 << 2),
    changes_position = (1 << 3),
} changes_t;

typedef enum _name_kind {
    name_none = 0,
    name_string = (1 << 0),
    name_xid = (1 << 1),
    name_index = (1 << 2),
} name_kind_t;

typedef struct {
    name_kind_t	    kind;
    char    	    *string;
    XID	    	    xid;
    int		    index;
} name_t;

typedef struct _crtc crtc_t;
typedef struct _output	output_t;

struct _crtc {
    name_t	    crtc;
    XRRCrtcInfo	    *crtc_info;

    XRRModeInfo	    *mode_info;
    int		    x;
    int		    y;
    Rotation	    rotation;
    output_t	    **outputs;
    int		    noutput;
};

struct _output {
    struct _output  *next;
    
    changes_t	    changes;
    
    name_t	    output;
    XRROutputInfo   *output_info;
    
    name_t	    crtc;
    crtc_t	    *crtc_info;
    crtc_t	    *current_crtc_info;
    
    name_t	    mode;
    float	    refresh;
    XRRModeInfo	    *mode_info;
    
    name_t	    addmode;

    relation_t	    relation;
    struct _output  *relative_to;

    int		    x, y;
    Rotation	    rotation;
};

static output_t	*outputs = NULL;
static output_t	**outputs_tail = &outputs;
static crtc_t	*crtcs = NULL;
static int	num_crtcs;
static XRRScreenResources  *res = NULL;
static int	fb_width = 0, fb_height = 0;
static int	fb_width_mm = 0, fb_height_mm = 0;
static float	dpi = 0.0;
static Bool	dryrun = False;
static int	minWidth, maxWidth, minHeight, maxHeight;

#define 	MAX_OUTPUT	3
#define 	MAX_MODIFIERS	10

typedef struct _con_output  con_output_t;

struct _con_output {
    output_t		*output;
    XRRModeInfo		**smodes;
    int			nsmodes;
    Bool		on;
};

typedef struct _mod_key_table  mod_key_table_t;

struct _mod_key_table {
    char		*modname;
    unsigned int	mod;
};

static	con_output_t	con_outputs[MAX_OUTPUT];
static	con_output_t	dis_con_outputs[MAX_OUTPUT];
static	XRRModeInfo	*start_mode[MAX_OUTPUT];
static  XRRModeInfo	*new_mode[MAX_OUTPUT];
static	int 	start = 0;
static	int	ncon;
static	int	dis_ncon;
static  Bool	do_not_switch = False;
static  Bool	did_init = False;

static mod_key_table_t	mod_key_table [MAX_MODIFIERS] = {
	{"none",	0},
	{"shift", 	ShiftMask},
	{"lock", 	LockMask},
	{"control",	ControlMask},
	{"mod1", 	Mod1Mask},
	{"mod2", 	Mod2Mask},
	{"mod3", 	Mod3Mask},
	{"mod4", 	Mod4Mask},
	{"mod5", 	Mod5Mask},
	{"any", 	AnyModifier}
};

static int
mode_height (XRRModeInfo *mode_info, Rotation rotation)
{
    switch (rotation & 0xf) {
    case RR_Rotate_0:
    case RR_Rotate_180:
	return mode_info->height;
    case RR_Rotate_90:
    case RR_Rotate_270:
	return mode_info->width;
    default:
	return 0;
    }
}

static int
mode_width (XRRModeInfo *mode_info, Rotation rotation)
{
    switch (rotation & 0xf) {
    case RR_Rotate_0:
    case RR_Rotate_180:
	return mode_info->width;
    case RR_Rotate_90:
    case RR_Rotate_270:
	return mode_info->height;
    default:
	return 0;
    }
}

/* v refresh frequency in Hz */
static float
mode_refresh (XRRModeInfo *mode_info)
{
    float rate;
    
    if (mode_info->hTotal && mode_info->vTotal)
	rate = ((float) mode_info->dotClock / 
		((float) mode_info->hTotal * (float) mode_info->vTotal));
    else
    	rate = 0;
    return rate;
}


static void
init_name (name_t *name)
{
    name->kind = name_none;
}

static void
set_name_string (name_t *name, char *string)
{
    name->kind |= name_string;
    name->string = string;
}

static void
set_name_xid (name_t *name, XID xid)
{
    name->kind |= name_xid;
    name->xid = xid;
}

static void
set_name_index (name_t *name, int index)
{
    name->kind |= name_index;
    name->index = index;
}

static void
set_name_all (name_t *name, name_t *old)
{
    if (old->kind & name_xid)
	name->xid = old->xid;
    if (old->kind & name_string)
	name->string = old->string;
    if (old->kind & name_index)
	name->index = old->index;
    name->kind |= old->kind;
}

static output_t *
add_output (void)
{
    output_t *output = calloc (1, sizeof (output_t));

    if (!output)
	fatal ("out of memory");
    output->next = NULL;
    *outputs_tail = output;
    outputs_tail = &output->next;
    return output;
}

static output_t *
find_output (name_t *name)
{
    output_t *output;

    for (output = outputs; output; output = output->next)
    {
	name_kind_t common = name->kind & output->output.kind;
	
	if ((common & name_xid) && name->xid == output->output.xid)
	    break;
	if ((common & name_string) && !strcmp (name->string, output->output.string))
	    break;
	if ((common & name_index) && name->index == output->output.index)
	    break;
    }
    return output;
}

static output_t *
find_output_by_xid (RROutput output)
{
    name_t  output_name;

    init_name (&output_name);
    set_name_xid (&output_name, output);
    return find_output (&output_name);
}

static crtc_t *
find_crtc (name_t *name)
{
    int	    c;
    crtc_t  *crtc = NULL;

    for (c = 0; c < num_crtcs; c++)
    {
	name_kind_t common;
	
	crtc = &crtcs[c];
	common = name->kind & crtc->crtc.kind;
	
	if ((common & name_xid) && name->xid == crtc->crtc.xid)
	    break;
	if ((common & name_string) && !strcmp (name->string, crtc->crtc.string))
	    break;
	if ((common & name_index) && name->index == crtc->crtc.index)
	    break;
	crtc = NULL;
    }
    return crtc;
}

static crtc_t *
find_crtc_by_xid (RRCrtc crtc)
{
    name_t  crtc_name;

    init_name (&crtc_name);
    set_name_xid (&crtc_name, crtc);
    return find_crtc (&crtc_name);
}

static XRRModeInfo *
find_mode (name_t *name)
{
    int		m;
    XRRModeInfo	*best = NULL;

    for (m = 0; m < res->nmode; m++)
    {
	XRRModeInfo *mode = &res->modes[m];
	if ((name->kind & name_xid) && name->xid == mode->id)
	{
	    best = mode;
	    break;
	}
    }
    return best;
}

static XRRModeInfo *
find_mode_by_xid (RRMode mode)
{
    name_t  mode_name;

    init_name (&mode_name);
    set_name_xid (&mode_name, mode);
    return find_mode (&mode_name);
}

static void
set_output_info (output_t *output, RROutput xid, XRROutputInfo *output_info)
{
    crtc_t  *crtc;

    /* sanity check output info */
    if (output_info->connection != RR_Disconnected && !output_info->nmode)
	fatal ("Output %s is not disconnected but has no modes\n",
	       output_info->name);
    
    /* set output name and info */
    if (!(output->output.kind & name_xid))
	set_name_xid (&output->output, xid);
    if (!(output->output.kind & name_string))
	set_name_string (&output->output, output_info->name);
    output->output_info = output_info;

    crtc = find_crtc_by_xid (output->output_info->crtc);    
    /* set position */
    if (crtc && crtc->crtc_info) {
	output->x = crtc->crtc_info->x;
	output->y = crtc->crtc_info->y;
    } 

    /* set rotation */
    output->rotation &= ~0xf;
    if (crtc && crtc->crtc_info)
	output->rotation |= (crtc->crtc_info->rotation & 0xf);
    else
	output->rotation = RR_Rotate_0;

}
    
static void
get_crtcs (void)
{
    int		c;

    num_crtcs = res->ncrtc;
    if (crtcs)
    {
	for (c = 0; c < res->ncrtc; c++)
	{
	    if (crtcs[c].crtc_info)
		XRRFreeCrtcInfo (crtcs[c].crtc_info);
	}
	free (crtcs);
	crtcs = NULL;
    }

    crtcs = calloc (num_crtcs, sizeof (crtc_t));
    if (!crtcs) fatal ("out of memory");
    
    for (c = 0; c < res->ncrtc; c++)
    {
	XRRCrtcInfo *crtc_info = XRRGetCrtcInfo (dpy, res, res->crtcs[c]);
	set_name_xid (&crtcs[c].crtc, res->crtcs[c]);
	set_name_index (&crtcs[c].crtc, c);
	if (!crtc_info) fatal ("could not get crtc 0x%x information", res->crtcs[c]);
	crtcs[c].crtc_info = crtc_info;
	if (crtc_info->mode == None)
	{
	    crtcs[c].mode_info = NULL;
	    crtcs[c].x = 0;
	    crtcs[c].y = 0;
	    crtcs[c].rotation = RR_Rotate_0;
	}
    }
}

static void
crtc_add_output (crtc_t *crtc, output_t *output)
{
    if (crtc->outputs)
	crtc->outputs = realloc (crtc->outputs, (crtc->noutput + 1) * sizeof (output_t *));
    else
    {
	crtc->outputs = calloc (1, sizeof (output_t *));
	crtc->x = output->x;
	crtc->y = output->y;
	crtc->rotation = output->rotation;
	crtc->mode_info = output->mode_info;
    }
    if (!crtc->outputs) fatal ("out of memory");
    crtc->outputs[crtc->noutput++] = output;
}

static void
set_crtcs (void)
{
    output_t	*output;
    int		i;

    for (i = 0; i < ncon; i++) {
	output = con_outputs[i].output;
	if (!output->mode_info) continue;
	    if (output->crtc_info)
		crtc_add_output (output->crtc_info, output);
    }
}

static void
reset_crtcs_for_outputs (void)
{
    output_t    *output;

    for (output = outputs; output; output = output->next)
    {
        if ((output->crtc_info) && (output->crtc_info->outputs)) {
            free (output->crtc_info->outputs);
            output->crtc_info = NULL;
        }
    }
}

static Status
crtc_disable (crtc_t *crtc)
{
    if (verbose)
    	fprintf (stderr, "crtc %d (0x%lx) : disable\n", crtc->crtc.index, crtc->crtc.xid);
	
    if (dryrun)
	return RRSetConfigSuccess;

    return XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			     0, 0, None, RR_Rotate_0, NULL, 0);
}

static Status
crtc_revert (crtc_t *crtc)
{
    XRRCrtcInfo	*crtc_info = crtc->crtc_info;
    
    if (verbose)
    	fprintf (stderr, "crtc %d: revert\n", crtc->crtc.index);
	
    if (dryrun)
	return RRSetConfigSuccess;
    return XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			    crtc_info->x, crtc_info->y,
			    crtc_info->mode, crtc_info->rotation,
			    crtc_info->outputs, crtc_info->noutput);
}

static Status
crtc_apply (crtc_t *crtc)
{
    RROutput	*rr_outputs;
    int		o;
    Status	s;
    RRMode	mode = None;

    if (!crtc->mode_info)
	return RRSetConfigSuccess;

    rr_outputs = calloc (crtc->noutput, sizeof (RROutput));
    if (!rr_outputs)
	return BadAlloc;
    for (o = 0; o < crtc->noutput; o++)
	rr_outputs[o] = crtc->outputs[o]->output.xid;
    mode = crtc->mode_info->id;
    if (verbose) {
	fprintf (stderr, "crtc %d (0x%lx) : %12s %6.1f +%d+%d", crtc->crtc.index,
		crtc->crtc.xid,
		crtc->mode_info->name, mode_refresh (crtc->mode_info),
		crtc->x, crtc->y);
	for (o = 0; o < crtc->noutput; o++)
	    fprintf (stderr, " \"%s\"", crtc->outputs[o]->output.string);
	    fprintf (stderr, "\n");
    }
    if (dryrun)
	s = RRSetConfigSuccess;
    else
	s = XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			      crtc->x, crtc->y, mode, crtc->rotation,
			      rr_outputs, crtc->noutput);
    free (rr_outputs);
    return s;
}

static void
screen_revert (void)
{
    if (verbose)
	fprintf (stderr, "screen %d: revert\n", screen);

    if (dryrun)
	return;
    XRRSetScreenSize (dpy, root,
		      DisplayWidth (dpy, screen),
		      DisplayHeight (dpy, screen),
		      DisplayWidthMM (dpy, screen),
		      DisplayHeightMM (dpy, screen));
}

static void
screen_apply (void)
{
    /* comment it out because DisplayWidth() does not reflect the
       change of fb_width and fb_height previously set by
       XRRSetScreenSize()
    */
    /*
    if (fb_width == DisplayWidth (dpy, screen) &&
	fb_height == DisplayHeight (dpy, screen) &&
	fb_width_mm == DisplayWidthMM (dpy, screen) &&
	fb_height_mm == DisplayHeightMM (dpy, screen))
    {
	return;
    }
    */

    if (verbose)
	fprintf (stderr, "screen %d: %dx%d %dx%d mm %6.2fdpi\n", screen,
		fb_width, fb_height, fb_width_mm, fb_height_mm, dpi);
    if (dryrun)
	return;
    XRRSetScreenSize (dpy, root, fb_width, fb_height,
		      fb_width_mm, fb_height_mm);

}

static void
revert (void)
{
    int	c;

    /* first disable all crtcs */
    for (c = 0; c < res->ncrtc; c++)
	crtc_disable (&crtcs[c]);
    /* next reset screen size */
    screen_revert ();
    /* now restore all crtcs */
    for (c = 0; c < res->ncrtc; c++)
	crtc_revert (&crtcs[c]);
}

/*
 * uh-oh, something bad happened in the middle of changing
 * the configuration. Revert to the previous configuration
 * and bail
 */
static void
panic (Status s, crtc_t *crtc)
{
    int	    c = crtc->crtc.index;
    char    *message;
    
    switch (s) {
    case RRSetConfigSuccess:		message = "succeeded";		    break;
    case BadAlloc:			message = "out of memory";	    break;
    case RRSetConfigFailed:		message = "failed";		    break;
    case RRSetConfigInvalidConfigTime:	message = "invalid config time";    break;
    case RRSetConfigInvalidTime:	message = "invalid time";	    break;
    default:				message = "unknown failure";	    break;
    }
    
    fprintf (stderr, "%s: Configure crtc %d %s\n", program_name, c, message);
    revert ();
    exit (1);
}

static void
apply (void)
{
    Status  s;
    int	    c;
    
    /*
     * Turn off any crtcs which are to be disabled or which are
     * larger than the target size
     */
    for (c = 0; c < res->ncrtc; c++)
    {
	crtc_t	    *crtc = &crtcs[c];
	XRRCrtcInfo *crtc_info = crtc->crtc_info;

	/*
	 * if this crtc is already disabled, skip it 
	 * Note server sets crtc_info->mode (before change)
	 */
	if (crtc_info->mode == None) 
	    continue;
	
	/* 
	 * If this crtc is to be left enabled, make
	 * sure the old size fits then new screen
	 * When crtc->mode_info is null, the crtc is to be
	 * disabled. Note set_crtcs () sets crtc->mode_info for
	 * new mode (to be changed to).
	 */
	if (crtc->mode_info) 
	{
	    XRRModeInfo	*old_mode = find_mode_by_xid (crtc_info->mode);
	    int x, y, w, h;

	    if (!old_mode) 
		panic (RRSetConfigFailed, crtc);
	    
	    /* old position and size information */
	    x = crtc_info->x;
	    y = crtc_info->y;
	    w = mode_width (old_mode, crtc_info->rotation);
	    h = mode_height (old_mode, crtc_info->rotation);
	    
	    /* if it fits, skip it */
	    if (x + w <= fb_width && y + h <= fb_height) 
		continue;
	}

	if (need_off_deferred)
	    /* Defer taking off */
	    continue;

	s = crtc_disable (crtc);
	if (s != RRSetConfigSuccess)
	    panic (s, crtc);
    }

    /*
     * Hold the server grabbed while messing with
     * the screen so that apps which notice the resize
     * event and ask for xinerama information from the server
     * receive up-to-date information
     */
    XGrabServer (dpy);
    
    /*
     * Set the screen size
     */
    screen_apply ();
    
    /*
     * Set crtcs
     */

    for (c = 0; c < res->ncrtc; c++)
    {
	crtc_t	*crtc = &crtcs[c];
	
	s = crtc_apply (crtc);
	if (s != RRSetConfigSuccess)
	    panic (s, crtc);
    }
    /*
     * Release the server grab and let all clients
     * respond to the updated state
     */
    XUngrabServer (dpy);
}

/*
 * Use current output state to complete the output list
 */
static void
get_outputs (void)
{
    int		o;
    
    for (o = 0; o < res->noutput; o++)
    {
	XRROutputInfo	*output_info = XRRGetOutputInfo (dpy, res, res->outputs[o]);
	output_t	*output;
	name_t		output_name;

	if (!output_info) fatal ("could not get output 0x%x information", res->outputs[o]);
	set_name_xid (&output_name, res->outputs[o]);
	set_name_index (&output_name, o);
	set_name_string (&output_name, output_info->name);
	output = find_output (&output_name);
	if (!output)
	{
	    output = add_output ();
	    set_name_all (&output->output, &output_name);
	}

	set_output_info (output, res->outputs[o], output_info);
    }
}


/*
 * Test whether 'crtc' can be used for 'output'
 */
static Bool
check_crtc_for_output (crtc_t *crtc, output_t *output)
{
    int		i;
    int		l;
    output_t    *other;

    for (i = 0; i < ncon; i++)
    {
	other = con_outputs[i].output;

	if (other == output)
	    continue;

	if (other->mode_info == NULL)
	    continue;

	if (other->crtc_info != crtc)
	    continue;

	/* see if the output connected to the crtc can clone to this output */
	for (l = 0; l < output->output_info->nclone; l++)
	    if (output->output_info->clones[l] == other->output.xid)
		break;
	/* not on the list, can't clone */
	if (l == output->output_info->nclone) 
	    return False;
    }

    if (crtc->noutput)
    {
	for (i = 0; i < crtc->noutput; i++)
	    /* Check if the output is to be turned on */
	    if (crtc->outputs[i]->mode_info) {
		/* make sure the state matches */
		if (crtc->mode_info != output->mode_info)
	    	    return False;
		if (crtc->x != output->x)
	    	    return False;
		if (crtc->y != output->y)
	    	    return False;
		if (crtc->rotation != output->rotation)
	    	    return False;
	    }
    }
    return True;
}

static crtc_t *
find_crtc_for_output (output_t *output)
{
    int	    c;

    for (c = 0; c < output->output_info->ncrtc; c++)
    {
	crtc_t	    *crtc;

	crtc = find_crtc_by_xid (output->output_info->crtcs[c]);
	if (!crtc) fatal ("cannot find crtc 0x%x\n", output->output_info->crtcs[c]);

	if (check_crtc_for_output (crtc, output))
	    return crtc;
    }
    return NULL;
}

static void
set_positions (void)
{
    Bool	keep_going;
    Bool	any_set;
    int		min_x, min_y;
    int		i;

    for (;;)
    {
	any_set = False;
	keep_going = False;
	for (i = 0; i < ncon; i++)
	{
	    output_t    *output = con_outputs[i].output;
	    output_t    *relation;

	    if (!(output->changes & changes_relation)) continue;
	    
	    if (output->mode_info == NULL) continue;

	    relation = output->relative_to;

	    if (relation->mode_info == NULL) 
	    {
		output->x = 0;
		output->y = 0;
		output->changes |= changes_position;
		any_set = True;
		continue;
	    }
	    /*
	     * Make sure the dependent object has been set in place
	     */
	    if ((relation->changes & changes_relation) && 
		!(relation->changes & changes_position))
	    {
		keep_going = True;
		continue;
	    }
	   
	    switch (output->relation) {
	    case left_of:
		output->y = relation->y;
		output->x = relation->x - mode_width (output->mode_info, output->rotation);
		break;
	    case right_of:
		output->y = relation->y;
		output->x = relation->x + mode_width (relation->mode_info, relation->rotation);
		break;
	    case above:
		output->x = relation->x;
		output->y = relation->y - mode_height (output->mode_info, output->rotation);
		break;
	    case below:
		output->x = relation->x;
		output->y = relation->y + mode_height (relation->mode_info, relation->rotation);
		break;
	    case same_as:
		output->x = relation->x;
		output->y = relation->y;
	    }
	    output->changes |= changes_position;
	    relation->changes |= changes_position;
	    any_set = True;
	}
	if (!keep_going)
	    break;
	if (!any_set)
	    fatal ("loop in relative position specifications\n");
    }

    /*
     * Now normalize positions so the upper left corner of all outputs is at 0,0
     */
    min_x = 32768;
    min_y = 32768;
    for (i = 0; i < ncon; i++)
    {
	output_t    *output = con_outputs[i].output;

	if (output->mode_info == NULL) continue;
	
	if (output->x < min_x) min_x = output->x;
	if (output->y < min_y) min_y = output->y;
    }
    if (min_x || min_y)
    {
	/* move all outputs */
	for (i = 0; i < ncon; i++)
	{
	    output_t    *output = con_outputs[i].output;

	    if (output->mode_info == NULL) continue;

	    output->x -= min_x;
	    output->y -= min_y;
	    output->changes |= changes_position;
	}
    }
}

static Bool
set_screen_size (void)
{
    int	i;

    fb_width = fb_height = 0;
    
    for (i = 0; i < ncon; i++)
    {
    	output_t	*output = con_outputs[i].output;
	XRRModeInfo *mode_info = output->mode_info;
	int	    x, y, w, h;
	
	if (!mode_info) continue;

	x = output->x;
	y = output->y;
	w = mode_width (mode_info, output->rotation);
	h = mode_height (mode_info, output->rotation);
	if (x + w > fb_width) fb_width = x + w;
	if (y + h > fb_height) fb_height = y + h;
    }

    if (fb_width > maxWidth || fb_height > maxHeight) {
	if (verbose)
            fprintf (stderr, "screen cannot be larger than %dx%d (desired size %dx%d)\n",
	       maxWidth, maxHeight, fb_width, fb_height);
	return False;
    }

    if (fb_width < minWidth) fb_width = minWidth;
    if (fb_height < minHeight) fb_height = minHeight;

    return True;
}
    
static void
disable_outputs (output_t *outputs)
{
    while (outputs)
    {
	outputs->crtc_info = NULL;
	outputs = outputs->next;
    }
}

/*
 * find the best mapping from output to crtc available
 */
static int
pick_crtcs_score (output_t *outputs)
{
    output_t	*output;
    int		best_score;
    int		my_score;
    int		score;
    crtc_t	*best_crtc;
    int		c;
    
    if (!outputs)
	return 0;
    
    output = outputs;
    outputs = outputs->next;
    /*
     * Score with this output disabled
     */
    output->crtc_info = NULL;
    best_score = pick_crtcs_score (outputs);
    if (output->mode_info == NULL)
	return best_score;

    best_crtc = NULL;
    /* 
     * Now score with this output any valid crtc
     */
    for (c = 0; c < output->output_info->ncrtc; c++)
    {
	crtc_t	    *crtc;

	crtc = find_crtc_by_xid (output->output_info->crtcs[c]);
	if (!crtc)
	    fatal ("cannot find crtc 0x%x\n", output->output_info->crtcs[c]);
	
	/* reset crtc allocation for following outputs */
	disable_outputs (outputs);
	if (!check_crtc_for_output (crtc, output))
	    continue;
	
	my_score = 1000;
	/* slight preference for existing connections */
	if (crtc == output->current_crtc_info)
	    my_score++;

	output->crtc_info = crtc;
	score = my_score + pick_crtcs_score (outputs);
	if (score > best_score)
	{
	    best_crtc = crtc;
	    best_score = score;
	}
    }
    if (output->crtc_info != best_crtc)
	output->crtc_info = best_crtc;
    /*
     * Reset other outputs based on this one using the best crtc
     */
    (void) pick_crtcs_score (outputs);

    return best_score;
}

/*
 * Pick crtcs for any changing outputs that don't have one
 */
static Bool
pick_crtcs (void)
{
    output_t	*output;
    int i;

    /*
     * First try to match up newly enabled outputs with spare crtcs
     */
    for (i = 0; i < ncon; i++)
    {
	output = con_outputs[i].output;

	if (output->mode_info)
	{
	    if (output->crtc_info)  {
		if (output->crtc_info->crtc_info->noutput > 0 &&
		    (output->crtc_info->crtc_info->noutput > 1 ||
		     output != find_output_by_xid (output->crtc_info->crtc_info->outputs[0])))
		    break;
	    } else {
		output->crtc_info = find_crtc_for_output (output);
		if (!output->crtc_info)
		    break;
		else {
		    if (verbose)
			fprintf(stderr, "picked crtc 0x%lx for output %d (%s)\n",
			    output->crtc_info->crtc.xid, i, output->output_info->name);
		}
	    }
	}
    }

    /*
     * Everyone is happy
     */
    if (i == ncon)
	return True;
    /*
     * When the simple way fails, see if there is a way
     * to swap crtcs around and make things work
     */
    for (output = outputs; output; output = output->next)
	output->current_crtc_info = output->crtc_info;
    pick_crtcs_score (outputs);
    for (output = outputs; output; output = output->next)
    {
	if (output->mode_info && !output->crtc_info) {
	    if (verbose)
		fprintf (stderr, "cannot find crtc for output %s\n", 
		    output->output.string);
	    return False;
	}
    }

    return True;
}

static Bool 
probe_and_check_output_changes (void) {
    XRRScreenResources  *new_res = NULL;
    int	 changed = False;
    int  i;

    new_res = XRRGetScreenResources (dpy, root);
    if (!new_res)
        fatal ("could not get screen resources");

    if ((new_res->noutput != res->noutput) || (new_res->nmode != res->nmode) ||
	(new_res->ncrtc != res->ncrtc))
	changed = True;
    else {
	for (i = 0; i < new_res->noutput; i++)
	    if (new_res->outputs[i] != res->outputs[i]) {
		changed = True;
		break;
	    }
	for (i = 0; i < new_res->nmode; i++)
	    if (new_res->modes[i].id != res->modes[i].id) {
		changed = True;
		break;
	    }
	for (i = 0; i < new_res->ncrtc; i++) {
	    crtc_t  *crtc = NULL;		/* old */
	    XRRCrtcInfo *crtc_info = NULL;	/* new */

	    crtc = find_crtc_by_xid (res->crtcs[i]);
	    crtc_info = XRRGetCrtcInfo (dpy, new_res, 
		new_res->crtcs[i]);

	    if (!crtc || !crtc_info) {
	    	changed = True;
	    	break;
	    }
	    if (!crtc->mode_info && !find_mode_by_xid (crtc_info->mode))
		continue;
    	    if ((crtc_info->x != crtc->x) || 
	    	(crtc_info->y != crtc->y) ||
 	    	(find_mode_by_xid (crtc_info->mode) != crtc->mode_info) ||
	    	(crtc_info->rotation != crtc->rotation)) {
	    	changed = True;
	    	break;
	    }
	}
    }

    if (changed) {
	if (res)
	    XRRFreeScreenResources(res);
	res = new_res;

	if (verbose)
	    fprintf(stderr, "probed: output status changed\n");
	return True;
    }

    if (verbose)
	fprintf(stderr, "probed: no output status change\n");
    return False;
}

static Bool 
need_probe (void) {
    struct timeval	cur_time_val;
    long long	cur, prev;

    X_GETTIMEOFDAY(&cur_time_val);
    cur = (long long) cur_time_val.tv_sec * 1000000 + cur_time_val.tv_usec;
    prev =(long long) time_val.tv_sec * 1000000 + time_val.tv_usec;
    if (((cur - prev) < 0) || ((cur - prev) > 5000000))
	return True;
    else
	return False;
}

static int
mode_sort (const void *p1, void *p2)
{
    XRRModeInfo *mi1 = * (XRRModeInfo **) p1;
    XRRModeInfo *mi2 = * (XRRModeInfo **) p2;

    if ((mi1->width == mi2->width) && (mi1->height == mi2->height)) {
	if (mode_refresh(mi1) && mode_refresh(mi2)) {
	    if (mode_refresh(mi1) < mode_refresh(mi2))
		return 1;
	    if (mode_refresh(mi1) > mode_refresh(mi2))
		return -1;
	} else
            return 0;
    }

    if ((mi1->width == mi2->width) && (mi1->height < mi2->height))
        return 1;
    if ((mi1->width == mi2->width) && (mi1->height > mi2->height))
        return -1;
    if (mi1->width < mi2->width)
        return 1;
    if (mi1->width > mi2->width)
        return -1;

    return 0;
}

static int
output_sort (const void *p1, const void *p2) {
    con_output_t co1 = * (con_output_t *) p1;
    con_output_t co2 = * (con_output_t *) p2;
    int ncrtc1 = co1.output->output_info->ncrtc;
    int ncrtc2 = co2.output->output_info->ncrtc;
    char *name1 = co1.output->output_info->name;
    char *name2 = co2.output->output_info->name;

    if (ncrtc1 == ncrtc2)
	return (strcmp(name1, name2));
    if (ncrtc1 <  ncrtc2)
	return -1;

    return 1;
}

static Bool 
get_common_mode(con_output_t *c0, con_output_t *c1, int *m0, int *m1) {
    int		i, j;
    int		i1 = -1, j1 = -1, i2 = -1, j2 = -1;
    int		x, y, w, h;
    output_t    *output = c0->output;

    *m0 = -1;
    *m0 = -1;
    if (!c0 ||!c1 || !c0->smodes || !c1->smodes)
	return False;

    /* first try to find mode with common same size */
    for (i = 0; i < c0->nsmodes; i ++) {
	for (j = 0; j < c1->nsmodes; j ++) 
	    if ((c0->smodes[i]->width == c1->smodes[j]->width) && 
		(c0->smodes[i]->height == c1->smodes[j]->height)) {
		x = output->x;
		y = output->y;
		w = mode_width (c0->smodes[i], output->rotation);
		h = mode_height (c0->smodes[i], output->rotation);
		if ((x + w <=  maxWidth) && (y + h <= maxHeight)) {
		    i1 = i; j1 = j;
		    break;
		}
	    }
	if ((i1 != -1) && (j1 != -1))
	    break;
    }

    if ((i1 == -1) && (j1 == -1))
	return False;

    /* then try to find mode with common id for possible cloning */
    for (i = 0; i < c0->nsmodes; i ++) {
	for (j = 0; j < c1->nsmodes; j ++) 
	    if (c0->smodes[i] == c1->smodes[j]) {
		x = output->x;
		y = output->y;
		w = mode_width (c0->smodes[i], output->rotation);
		h = mode_height (c0->smodes[i], output->rotation);
		if ((x + w <=  maxWidth) && (y + h <= maxHeight)) {
		    i2 = i; j2 = j;
		    break;
		}
	    }
	if ((i2 != -1) && (j2 != -1))
	    break;
    }

    if ((i2 == -1) && (j2 == -1)) {
	*m0 = i1;
	*m1 = j1;
    } else {
	/* use common id if it is not smaller */
	if ((mode_width (c0->smodes[i1], output->rotation) >
	    mode_width (c0->smodes[i2], output->rotation)) &&
	    (mode_height (c0->smodes[i1], output->rotation) >
	    mode_height (c0->smodes[i2], output->rotation))) {
	    *m0 = i1;
	    *m1 = j1;
	} else {
	    *m0 = i2;
	    *m1 = j2;
	}
    }

    return True;
}

static XRRModeInfo *
get_largest_mode (con_output_t *c, XRRModeInfo *start_mode) {
    int		i, found = False;
    output_t	*output = c->output;

    for (i = 0; i < c->nsmodes; i++) {
	XRRModeInfo *mode_info = c->smodes[i];
	int 	x, y, w, h;

	if (!found && (start_mode != mode_info)) 
	    continue;
	else 
	    found = True;

	if (mode_info) {
	    x = output->x;
            y = output->y;
            w = mode_width (mode_info, output->rotation);
            h = mode_height (mode_info, output->rotation);
	    if ((x + w <=  maxWidth) && (y + h <= maxHeight))
		break;
	}
    }

    if (i < c->nsmodes)
	return c->smodes[i];
    else
	fatal("cannot find mode");

}

static Bool
valid_mode(con_output_t *con, XRRModeInfo *mode) {
    int i;

    for (i = 0; i < con->nsmodes; i++)
	if (con->smodes[i] == mode)
	    return True;

    return False;
}

static void
do_init (void) 
{
    int     	i, j;
    output_t    *output;

    /* Initialize con_outputs array */
    for (i = 0; i < MAX_OUTPUT; i++) {
	con_outputs[i].output = NULL;
	con_outputs[i].on = False;
	start_mode[i] = NULL;
	new_mode[i] = NULL;
    }

    ncon = 0;
    dis_ncon = 0;
    init_rotation = RR_Rotate_0;
    init_x = 0;
    init_y = 0;
    get_crtcs ();
    get_outputs ();

    for (output = outputs; output; output = output->next) {
	XRROutputInfo   *output_info = output->output_info;

	if (output_info->connection == RR_Connected) {
	    con_outputs[ncon].output = output;
	    con_outputs[ncon].nsmodes = 0;
	    for (j = 0; j < output_info->nmode; j++) {
		XRRModeInfo *rmode = find_mode_by_xid (output_info->modes[j]);

	 	con_outputs[ncon].smodes =
		    realloc(con_outputs[ncon].smodes, 
		    (con_outputs[ncon].nsmodes + 1) * sizeof (XRRModeInfo *));
		con_outputs[ncon].smodes[j] = rmode;
		con_outputs[ncon].nsmodes ++;
	    }

	    /* Sort the modes */
            qsort((void *) con_outputs[ncon].smodes, 
		con_outputs[ncon].nsmodes, sizeof(XRRModeInfo *),
		(int (*) (const void *, const void *)) mode_sort);

	    if (output_info->crtc) {
		crtc_t      *crtc;

		con_outputs[ncon].on = True;
		for (j = 0; j < output_info->ncrtc; j++) {
		    if (output_info->crtcs[j] == output_info->crtc)
                            break;
                    if (j == output_info->ncrtc) {
			if (verbose)
                            fatal ("crtc does not match for output\n");
                    }
		}
		/* set initial mode_info */
		crtc = find_crtc_by_xid (output_info->crtc);
		if (crtc)
		    con_outputs[ncon].output->mode_info = 
			find_mode_by_xid (crtc->crtc_info->mode);
	    }
	    else 
		con_outputs[ncon].on = False;
	    ncon ++;
	} else if (output_info->connection == RR_Disconnected) {
	    dis_con_outputs[dis_ncon].output = output;
	    dis_ncon ++;
	}
    }

    qsort((void **) con_outputs, ncon,
	sizeof(con_output_t), (int (*) (const void *, const void *)) output_sort);

    if (verbose) {
	fprintf(stderr, "Total connected outputs = %d :\n", ncon);
	for (j = 0; j < ncon; j++) {
	    fprintf(stderr, "%d (%s): top mode = %s, rotation = %d, crtcs =", j,
		con_outputs[j].output->output_info->name, 
		con_outputs[j].smodes[0]->name,
		con_outputs[j].output->rotation); 
	    for (i = 0; i < con_outputs[j].output->output_info->ncrtc; i++)
		fprintf(stderr, " 0x%lx", con_outputs[j].output->output_info->crtcs[i]);
	    fprintf(stderr, ", using 0x%lx", con_outputs[j].output->output_info->crtc);
	    fprintf(stderr, "\n");
	}
	fprintf(stderr, "Total disconnected outputs = %d :\n", dis_ncon);
	for (j = 0; j < dis_ncon; j++) {
	    fprintf(stderr, "%d (%s) : number of crtcs %d =", j, 
		dis_con_outputs[j].output->output_info->name, 
		dis_con_outputs[j].output->output_info->ncrtc);
	    for (i = 0; i < dis_con_outputs[j].output->output_info->ncrtc; i++)
		fprintf(stderr, " 0x%lx", dis_con_outputs[j].output->output_info->crtcs[i]);
	    fprintf(stderr, ", using 0x%lx", dis_con_outputs[j].output->output_info->crtc);
	    fprintf(stderr, "\n");
	}
    }

    i = con_outputs[2].on * 4 + con_outputs[1].on * 2 + con_outputs[0].on;

    if ((i == 1) || (i == 2) || (i == 4)) {
	use_init_pos = True;
	j = i >> 1;

	/* remember position and mode info in single state */
    	start_mode[j] = con_outputs[j].output->mode_info;
	init_rotation = con_outputs[j].output->rotation;
	init_x = con_outputs[j].output->x;
	init_y = con_outputs[j].output->y;
    } else
	use_init_pos = False;

    if ((ncon != 2) || (start < 3))
	start = i;

    if ((ncon < 1) || (ncon > 3)) {
	if ((ncon < 1) && verbose)
	    fprintf (stderr, "warn: no connection\n");
	else if ((ncon > 3) && verbose)
	    fprintf (stderr, "warn: too many (more than 3) connections: %d: can't switch\n", ncon);
	do_not_switch = True;
    }

    did_init = True;

    return;
}

static int 
grab_key (Display *dpy, int keysym, unsigned int modifier, 
    Window grab_window)
{
    char    msg[256];
    int keycode = XKeysymToKeycode(dpy, keysym);

    if (keycode ==  NoSymbol)
	fatal ("grab_key: keycode not defined for keysym 0x%x\n", keysym);

    had_error = 0;
    prev_handler = XSetErrorHandler (cur_handler);

    if (!testrun) {
    	XGrabKey(dpy, 
	    keycode,
	    modifier,
	    root, True, GrabModeAsync, GrabModeAsync);
    	XSync (dpy, False);
    }

    XSetErrorHandler (prev_handler);
    if (had_error) {
	XGetErrorText (dpy, had_error, msg, sizeof (msg));
	fatal ("XGrabKey: %s\n", msg);
    }

    if (verbose)
	fprintf(stderr, "keycode to grab: %d\n", keycode);

    return keycode;
}

static Bool
do_switch (void)
{
    int 	i, j;
    int		single;
    int		save = -1;

    if (ncon <= 0)
	return True; 

    for (i = 0; i < ncon; i++) {
	output_t	*output = con_outputs[i].output;

	new_mode[i] = NULL;
	output->relation = same_as;
	output->relative_to = NULL;
	if (use_init_pos) {
	    output->x = init_x;
	    output->y = init_y;
	    output->rotation = init_rotation;
	} else { 
	    output->x = 0;
	    output->y = 0;
	}
    }

    if (ncon == 2) {
	if (!nosideview) {
	    if (++start > 5)    start = 1;
	}
	else {
	    if (++start > 3)    start = 1;
	}

	if (verbose)
	    fprintf(stderr, "current state = %d\n", start);
	if (start >= 3) {
	    int m0, m1;

    	    if (get_common_mode(&con_outputs[0], &con_outputs[1], &m0, &m1)) {
		new_mode[0] = con_outputs[0].smodes[m0];
                new_mode[1] = con_outputs[1].smodes[m1];
	    } else {
		new_mode[0] = get_largest_mode (&con_outputs[0],
			con_outputs[0].smodes[0]);
		new_mode[1] = get_largest_mode (&con_outputs[1],
			con_outputs[1].smodes[0]);
	    }
	} else {
	    if (start_mode[start -1] && valid_mode(&con_outputs[start -1], 
		start_mode[start -1]))
		    new_mode[start -1] = start_mode[start -1]; 
	    else {
	        if (con_outputs[start -1].smodes[0])
		    new_mode[start -1] = 
			get_largest_mode (&con_outputs[start-1],
			con_outputs[start -1].smodes[0]); 
	    }
	}
    }

    if (ncon == 3) {
	if (++start > 6)	start = 1;
	if (verbose)
	    fprintf(stderr, "current state = %d\n", start);
	if ((start == 1) || (start == 2) || (start == 4)) {
	    single = 1;
	    i = start >> 1;
	    j = 0;
	}
	else {
	    single = 0;
	    if (start > 4)
		j = 2;
	    else
		j = 1;
	    if (start > 5)
		i = 1;
	    else
		i = 0;
	}

	if (single) {
	    if (start_mode[i] && valid_mode(&con_outputs[i], start_mode[i]))
		new_mode[i] = start_mode[i];
	    else {
	        if (con_outputs[i].smodes[0])
		    new_mode[i] = get_largest_mode (&con_outputs[i], 
			con_outputs[i].smodes[0]);
	    }
	}
	else {
	    int m0, m1;

    	    if (get_common_mode(&con_outputs[i], &con_outputs[j], &m0, &m1)) {
		new_mode[i] = con_outputs[i].smodes[m0];
		new_mode[j] = con_outputs[j].smodes[m1];
    	    } else {
		new_mode[i] = get_largest_mode (&con_outputs[i], 
		    con_outputs[i].smodes[0]);
		new_mode[j] = get_largest_mode (&con_outputs[j],
		    con_outputs[j].smodes[0]);
	    }
	}
    }

    if (ncon == 1) {
	if (start_mode[0] && valid_mode(&con_outputs[0], start_mode[0]))
	    new_mode[0] = start_mode[0]; 
	else {
	    if (con_outputs[0].smodes[0])
		new_mode[0] = get_largest_mode (&con_outputs[0],
		    con_outputs[0].smodes[0]);
	}
    }

    /* Set mode */
    for (i = 0; i < ncon; i++) {
    	output_t	*output;

    	output = con_outputs[i].output;
	if (new_mode[i]) {
	    if ((!output->mode_info) || (output->mode_info != new_mode[i])) {
    		output->mode_info = new_mode[i];
	        con_outputs[i].on = True;
		if (verbose)
		    fprintf(stderr, "set output %d (%s) to mode %s rotation %d\n", i, 
			con_outputs[i].output->output_info->name, 
			con_outputs[i].output->mode_info->name,
			con_outputs[i].output->rotation);
    	    } 
	} else if (con_outputs[i].on ) {
	    if (!need_off_deferred) {
		output->mode_info = NULL;
		con_outputs[i].on = False;
		if (verbose)
		    fprintf(stderr, "turn off output %d (%s) \n", 
			i, con_outputs[i].output->output_info->name);
	    } else
		save = i;
	}
    }
  
    if ((ncon == 2) && (start >= 4)) {
	if (start == 4) {
	    con_outputs[1].output->relative_to = con_outputs[0].output;
	    con_outputs[1].output->relation = right_of;
	    con_outputs[1].output->changes = changes_relation;
	    con_outputs[0].output->changes = 0;
	}
	else if (start == 5) {
	    con_outputs[0].output->relative_to = con_outputs[1].output;
	    con_outputs[0].output->relation = right_of;
	    con_outputs[0].output->changes = changes_relation;
	    con_outputs[1].output->changes = 0;
	}

	set_positions();
    }

    if (!set_screen_size ()) 
	return False;
    

    /* reset crtcs before allocation */
    reset_crtcs_for_outputs();

    if (!did_init)
	get_crtcs();

    if (!pick_crtcs()) {
	if (verbose)
	    fprintf(stderr, "pick_crtcs failed\n");
	return True;
    }

    set_crtcs ();
    apply();

    if (need_off_deferred && (save != -1)) {
	/* Now, take the deferred output off */
	output_t    *output;
	crtc_t      *crtc;
	Status      s;
	
	output = con_outputs[save].output;
	output->mode_info = NULL;
	con_outputs[save].on = False;
	if (verbose)
	    fprintf(stderr, "turn off output %d (%s) \n",
		save, con_outputs[save].output->output_info->name);
	
	crtc = output->crtc_info;
	s = crtc_disable (crtc);
	if (s != RRSetConfigSuccess)
	    panic (s, crtc);
    }

    XSync (dpy, False);

    did_init = False;

    return True;

}

static Bool 
do_toggle (void)
{
    Atom		atom;
    XEvent		xev;
    int			ret;

    atom = XInternAtom (dpy, "DISPLAYSWITCH_DAEMON", True);
    if (!atom) {
	fprintf(stderr, "dispswitch daemon not running\n");
	return False;
    }
	
    win = XGetSelectionOwner (dpy, atom);
    if (!win) {
	fprintf(stderr, "dispswitch: No owner of dispswitch daemon is found\n");
	return False;
    }

    bzero (&xev, sizeof (XEvent));
    xev.xkey.type = KeyPress;
    xev.xkey.send_event = True;
    xev.xkey.display = dpy;
    /* Any keycode */
    xev.xkey.keycode = 71;


    /* 
     * Send another instance of dispswitch (a daemon) an event to
     * request a switch
     */
    ret = XSendEvent(dpy, win, False, KeyPressMask, &xev);
    XFlush(dpy);

    if (!ret)
	fprintf(stderr, "dispswitch: XSendEvent error\n");

    return (!ret);
}

int
main (int argc, char **argv) 
{
    char    *display_name = NULL;
    int	    major, minor;
    int	    i;
    char    msg[256];
    XEvent  ev;
    unsigned int    modifier = 0;
    Bool    key_given = False;
    Bool    mod_given = False;
    int	    keysym = 0, toggle = False, listen = False;

    Atom    atom;

    program_name = argv[0];

    for (i = 1; i < argc; i++) {
	if (!strcmp ("-display", argv[i]) || !strcmp ("-d", argv[i])) {
	    if (++i>=argc) usage ();
	    	display_name = argv[i];
	    continue;
        }
	if (!strcmp ("-key", argv[i]) || !strcmp ("-k", argv[i])) {
	    if (++i>=argc) usage ();
	    if ((keysym = XStringToKeysym(argv[i])) == NoSymbol) {
		fprintf(stderr, "invalid keysym: -key %s\n", argv[i]);
		usage();
	    }
	    key_given = True;
	    continue;
	}
	if (!strcmp ("-mod", argv[i]) || !strcmp ("-m", argv[i])) {
	    int 	j;
	    char 	*s, *p, *q;
	    int		end = 0;

	    if (++i>=argc) usage ();
	    s = strdup (argv[i]);
	    if (!s) {
		if (verbose)
		    fprintf(stderr, "modifier failed, will use default modifier\n");
	 	continue;
	    }
	    while (*s == ' ') s++;
	    p = s + strlen(s) - 1;
	    while (*p == ' ') *p-- = 0;
	    q = s;
	    for (; ;) {
	    	if (p = strchr(s, '+')) {
		    *p = ' ';
		    while ((p > s) && (*(p-1) == ' ')) p--;
		    *p = 0;
		}
		else
		    end = 1;
	        for (j = 0; j < MAX_MODIFIERS; j++) {
	     	    if (!strcmp(mod_key_table[j].modname, s)) {
			modifier |= mod_key_table[j].mod;
			break;
		    }
		}
	   	if (j == MAX_MODIFIERS) {
		    fprintf(stderr, "invalid modifier: -mod %s\n", q);
	 	    usage();
		}
		if (end)
		    break;
		else {
		    s = ++p;
		    while (*s == ' ') s++;
		}
	    }
	    mod_given = True;
	    free (q);
	    continue;
        }
	if (!strcmp ("-nosideview", argv[i])) {
	    nosideview = True;
	    continue;
        }
	if (!strcmp ("-verbose", argv[i]) || !strcmp ("-v", argv[i])) {
	    verbose = True;
	    continue;
        }
	if (!strcmp ("-testrun", argv[i])) {
	    testrun = True;
	    verbose = True;
	    continue;
        }
	if (!strcmp ("-toggle", argv[i]) || !strcmp ("-t", argv[i])) {
	    toggle = True;
	    continue;
        }
	if (!strcmp ("-listen", argv[i]) || !strcmp ("-l", argv[i])) {
	    listen = True;
	    continue;
        }
	usage();
    }

    dpy = XOpenDisplay (display_name);

    if (dpy == NULL) 
	fatal ("can't open display %s\n", XDisplayName(display_name));

    screen = DefaultScreen (dpy);
    root = RootWindow (dpy, screen);

    if (!XRRQueryVersion (dpy, &major, &minor))
	fatal ("randr extension missing\n");

    if ((major <= 1) &&  (major != 1 || minor < 2))
	fatal ("wrong randr version: %d.%d\n", major, minor);


    if (toggle)
	exit (do_toggle());

    /* 
     * Create an atom, a trivial window, and make it selection owner. 
     * Ready to accept a client event request for switch
     */
    atom = XInternAtom(dpy, "DISPLAYSWITCH_DAEMON", False);
    if (!atom) {
	if (verbose)
	    fprintf(stderr, "cannot create Atom\n");
    }
    else {
	if (XGetSelectionOwner (dpy, atom)) {
	    if (verbose)
		fprintf(stderr, "dispswitch daemon is already running, quit\n");
	    exit (1);
	}
	win = XCreateSimpleWindow(dpy, root, 0, 0, 10, 10, 0, 10, 0);
	if (!win) {
	    if (verbose)
		fprintf(stderr, "cannot create window\n");
	}
	else {
	    XSetSelectionOwner(dpy, atom, win, CurrentTime);
	    if (XGetSelectionOwner(dpy, atom) != win) {
		if (verbose)
		    fprintf(stderr, "set selection owner failed\n");
	    } else
		XSelectInput(dpy, win, KeyPressMask);
	}
    }

    /* set default key and modifier if not given in command */
    if (!key_given)
	keysym  = XStringToKeysym ("F5");
    if (!mod_given)
	modifier = ShiftMask;

    if (!listen)
	cur_keycode = grab_key (dpy, keysym, modifier, root);

    XRRGetScreenSizeRange (dpy, root, &minWidth, &minHeight,
                           &maxWidth, &maxHeight);

    fb_width_mm = DisplayWidthMM (dpy, screen);
    fb_height_mm = DisplayHeightMM (dpy, screen);
    dpi = (25.4 * DisplayHeight (dpy, screen)) / DisplayHeightMM(dpy, screen);

    res = XRRGetScreenResources (dpy, root);
    if (!res)
	fatal ("could not get screen resources\n");
    if (res->ncrtc < 2)
	fatal ("too few crtcs: %d\n", res->ncrtc);

    do_init();

    X_GETTIMEOFDAY(&time_val);

    for(;;)
    {
	need_off_deferred = False;

	if (testrun) {
	    usleep(4000000);
	    fprintf(stderr, "\n");
	} else
	    XNextEvent(dpy, &ev);

	if (!listen && !testrun && (ev.type == MappingNotify) && 
	    ((ev.xmapping.request == MappingKeyboard) || 
	    (ev.xmapping.request == MappingModifier))) {
	    /* keyboard/modifier mapping changed */
	    if (verbose)
		fprintf(stderr, "\nkeyboard/modifier mapping changed ...\n");

	    XUngrabKey(dpy, cur_keycode, modifier, root);
	    cur_keycode = grab_key (dpy, keysym, modifier, root);
	}

	if (testrun || (ev.type == KeyPress)) {
	    if (verbose)
		fprintf(stderr, "\na key press event was grabbed ...\n");

	    do_not_switch = False;

	    if (testrun || need_probe()) {
	    /* Too long since last switch, need to check output changes */
		if (probe_and_check_output_changes ()) {
		    output_t    *output, *next;

		    output = outputs;
		    while (output) {
			if (output->output_info)
			    XRRFreeOutputInfo (output->output_info);
			if (output->crtc_info && output->crtc_info->outputs) {
			    free(output->crtc_info->outputs);
			    output->crtc_info->outputs = NULL;
			}
			next = output->next;
			free(output);
			output = next;
		    }
		    outputs = NULL;
		    outputs_tail = &outputs;
		    for (i = 0; i < ncon; i++) {
			con_outputs[i].output = NULL;
			con_outputs[i].on = False;
			if (con_outputs[i].smodes) {
			    free(con_outputs[i].smodes);
			    con_outputs[i].smodes = NULL;
			}
			con_outputs[i].nsmodes = 0;
		    }

		    do_init();
		} else if (ncon == 1)
		    do_not_switch = True;
	    } else if (ncon == 1)
		do_not_switch = True;

    	    if (!do_not_switch) {
		if ((ncon == 2) && (start == 1))
		    /* 
		     * Workaround for intel based graphics: in switching from 
		     * LVDS to VGA, off on LVDS needs to be deferred.
		     */
		    need_off_deferred = True;
	    	if (!do_switch()) {
		    if ((ncon == 2) && (start == 4)) {
			start = 5;
			if (verbose)
			    fprintf(stderr, "too small screen, skipping side view\n");
			(void) do_switch();
		    }
		}
	    }
    
	    X_GETTIMEOFDAY(&time_val);
	}
    }
}

