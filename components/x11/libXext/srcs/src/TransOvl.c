/* Copyright (c) 1996, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * TransOvl.c - the client side interface to the Transparent Overlays
 * extension.
 */

#define NEED_EVENTS
#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/transovlstr.h>
#include <X11/extensions/multibuf.h>
#include <limits.h>

typedef struct {
    XExtData		extdata;
    int			numVisPairs;
    Bool		pairsRestricted;
    int			visdatatypes;
} XOvlScrExtData;

typedef struct {
    VisualID		vid;
    Visual		*vis;
    int			depth;
} XOvlVisInfo;

typedef struct {
    XOvlVisInfo		overlay;
    XOvlVisInfo		underlay;
} XOvlVisPair;

#ifdef _LP64
#define XOvlMBXBuffers		(1L << 0)
#define XOvlSharedPixels	(1L << 1)
#define XOvlSharedColors	(1L << 2)

#define XOVL_MAX_BUFFERS	(~0L)
#define XOVL_ALL_PLANES		(~0L)
#define XOVL_ANY_POOL		(~0L)
#else  /* _LP64 */
#define XOvlMBXBuffers		(1 << 0)
#define XOvlSharedPixels	(1 << 1)
#define XOvlSharedColors	(1 << 2)

#define XOVL_MAX_BUFFERS	(~0)
#define XOVL_ALL_PLANES		(~0)
#define XOVL_ANY_POOL		(~0)
#endif /* _LP64 */

typedef struct {
    XExtData		extdata;
    int			datatypes;
    int			numBuffers;
    unsigned long	ovplanes;
    unsigned long	unplanes;
    unsigned long	clutpool;
    int			clutcount;
} XOvlVisExtData;

typedef struct {
    XExtData		extdata;
    XSolarisOvlPaintType paintType;
} XOvlGCExtData;

typedef struct {
    int			screen;
    XOvlVisInfo		candidate;
    XOvlVisInfo		partner;
    Bool		partnerpreferred;
    XSolarisOvlSelectType	searchtype;
    unsigned long	hardfailures;
    unsigned long	softfailures;
    int			numhardfailures;
    int			numsoftfailures;
} XOvlVisualMatch;

typedef struct {
    int		nDepths;
    Depth	*pDepths;
    int		depth;
    int		nVisuals;
    Visual	*pVisuals;
} XOvlVisEnumData;

static int  close_display(Display *dpy, XExtCodes *codes);

static XExtensionInfo	*ext_info;
static char		*ext_name = OVLNAME;
static XExtensionHooks	 ext_hooks = {
    NULL,			/* create_gc */
    NULL,			/* copy_gc */
    NULL,			/* flush_gc */
    NULL,			/* free_gc */
    NULL,			/* create_font */
    NULL,			/* free_font */
    close_display,		/* close_display */
    NULL,			/* wire_to_event */
    NULL,			/* event_to_wire */
    NULL,			/* error */
    NULL,			/* error_string */
};

static
XEXT_GENERATE_CLOSE_DISPLAY(close_display,
			    ext_info)

static
XEXT_GENERATE_FIND_DISPLAY(find_display,
			   ext_info, ext_name, &ext_hooks,
			   OvlNumberEvents, NULL)

#define OvlCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, ext_name, val)
#define OvlSimpleCheckExtension(dpy,i) \
  XextSimpleCheckExtension (dpy, i, ext_name)


/**********************************************************************/

/*
 * The utility function _XVIDtoVisual could be used, but we already
 * know the screen structure where the visual is to be found, so there
 * is no need to scan all the screens on the display.  This procedure
 * performs a more direct scan for the visual.
 */
static Bool
find_visual(
    Screen	 *scr,
    VisualID	  vid,
    Visual	**visReturn,
    int		 *depthReturn
)
{
    Depth	 *depth;
    Visual	 *vis;

    for (depth = scr->depths; depth < (scr->depths + scr->ndepths); depth++) {
	if (depth->visuals) {
	    for (vis = depth->visuals;
		 vis < (depth->visuals + depth->nvisuals);
		 vis++)
	    {
		if (vis->visualid == vid) {
		    *visReturn   = vis;
		    *depthReturn = depth->depth;
		    return True;
		}
	    }
	}
    }
    return False;
}


static void
vis_enum_init(
    Screen		*scr,
    XOvlVisEnumData	*visEnumData
)
{
    visEnumData->nDepths  = scr->ndepths;
    visEnumData->pDepths  = scr->depths;
    visEnumData->depth    = 0;
    visEnumData->nVisuals = 0;
    visEnumData->pVisuals = NULL;
}


static Bool
vis_enum_next(
    XOvlVisEnumData	 *visEnumData,
    Visual		**visReturn,
    int			 *depthReturn
)
{
    int			  ndepths;
    Depth		 *depth;

    if (!visEnumData->nVisuals) {
	ndepths = visEnumData->nDepths;
	depth   = visEnumData->pDepths;
	while (ndepths) {
	    if (depth->visuals) {
		break;
	    }
	    ndepths--;
	    depth++;
	}
	if (!ndepths) {
	    return False;
	}
	visEnumData->nDepths  = ndepths - 1;
	visEnumData->pDepths  = depth + 1;
	visEnumData->depth    = depth->depth;
	visEnumData->nVisuals = depth->nvisuals;
	visEnumData->pVisuals = depth->visuals;
    }
    visEnumData->nVisuals--;
    *visReturn   = visEnumData->pVisuals++;
    *depthReturn = visEnumData->depth;
    return True;
}


static XOvlScrExtData *
find_screendata(
    Display			*dpy,
    int				 screen,
    XExtDisplayInfo		*info
)
{
    XOvlScrExtData		*scrextdata;
    Screen			*scr;
    xOvlGetPartnersReq		*req;
    xOvlGetPartnersReply	 rep;
    unsigned long		 nbytes;
    unsigned long		 numPairs;
    XOvlVisPair			*vispairs,
    				*vispair;
    XOvlVidPair			 vidpair;
    XEDataObject		 obj;

    obj.screen = scr = ScreenOfDisplay(dpy, screen);
    scrextdata = (XOvlScrExtData *)
	XFindOnExtensionList(XEHeadOfExtensionList(obj),
			     info->codes->extension);
    if (!scrextdata) {
	GetReq(OvlGetPartners, req);
	req->reqType    = info->codes->major_opcode;
	req->ovlReqType = X_OvlGetPartners;
	req->screen     = screen;
	if (_XReply(dpy, (xReply *)(&rep), 0, xFalse)) {
	    numPairs   = rep.numPairs;
	    nbytes     = numPairs * sizeof(XOvlVisPair);
	    scrextdata = Xmalloc(sizeof(XOvlScrExtData));
	    vispairs   = (XOvlVisPair *)Xmalloc(nbytes);
	    if (scrextdata && vispairs) {
		scrextdata->extdata.number       = info->codes->extension;
		scrextdata->extdata.free_private = NULL;
		scrextdata->extdata.private_data = (char *)vispairs;
		scrextdata->numVisPairs          = rep.numPairs;
		scrextdata->pairsRestricted      = rep.restricted;
		/* BugId: 4126680 - Purify detects reads in uninitialized
		memory generating random results. culprit was id'd to
		be the uninitialized field visdatatypes */
		scrextdata->visdatatypes         = 0;
		vispair = vispairs;
		while (numPairs--) {
		    _XRead(dpy, (char *)(&vidpair), sizeof(vidpair));
		    vispair->overlay.vid  = vidpair.overlayVid;
		    vispair->underlay.vid = vidpair.underlayVid;
		    if (   !find_visual(scr, vidpair.overlayVid,
				        &vispair->overlay.vis,
				        &vispair->overlay.depth)
			|| !find_visual(scr, vidpair.underlayVid,
					&vispair->underlay.vis,
					&vispair->underlay.depth))
		    {
			Xfree(vispairs);
			Xfree(scrextdata);
			scrextdata = NULL;
			if (numPairs) {
			    nbytes = numPairs * sizeof(XOvlVidPair);
			    _XEatData(dpy, nbytes);
			}
			break;
		    }
		    vispair++;
		}
		if (scrextdata) {
		    XAddToExtensionList(XEHeadOfExtensionList(obj),
		    			&(scrextdata->extdata));
		}
	    } else {
		Xfree(scrextdata);
		Xfree(vispairs);
		nbytes = numPairs * sizeof(XOvlVidPair);
		_XEatData(dpy, nbytes);
		scrextdata = NULL;
	    }
	}
    }
    return scrextdata;
}


static XOvlVisExtData *
find_visdata(
    Visual		*vis,
    XExtDisplayInfo	*info
)
{
    XOvlVisExtData	*visextdata;
    XEDataObject	 obj;

    obj.visual = vis;
    visextdata = (XOvlVisExtData *)
	XFindOnExtensionList(XEHeadOfExtensionList(obj),
			     info->codes->extension);
    if (!visextdata) {
	visextdata = Xmalloc(sizeof(XOvlVisExtData));
	if (visextdata) {
	    visextdata->extdata.number       = info->codes->extension;
	    visextdata->extdata.free_private = NULL;
	    visextdata->extdata.private_data = NULL;
	    visextdata->datatypes            = 0;
	    XAddToExtensionList(XEHeadOfExtensionList(obj),
	    			&(visextdata->extdata));
	}
    }

    return visextdata;
}


static int
bitcount(
    unsigned long	mask
)
{
    int			count;

    count = 0;
    while (mask) {
	count++;
	mask &= (mask - 1);
    }
    return count;
}


static int
GetNumMBXBuffers(
    Display		*dpy,
    int			 screen,
    Visual		*candidateVis,
    XExtDisplayInfo	*info)
{
    XOvlVisExtData	*candidateData;
    XOvlScrExtData	*scrextdata;
    int			 i,
    			 nmono,
    			 nstereo;
    XmbufBufferInfo	*mono_info,
    			*stereo_info;
    Visual		*vis;
    int			 depth;
    XOvlVisExtData	*visextdata;
    Screen		*scr;

    candidateData = find_visdata(candidateVis, info);
    if (!candidateData) {
	/*
	 * Cannot store data for this visual, assume the worst case.
	 */
	return 0;
    }
    if (!(candidateData->datatypes & XOvlMBXBuffers)) {
	scrextdata = find_screendata(dpy, screen, info);
	if (!(scrextdata->visdatatypes & XOvlMBXBuffers)) {
	    /*
	     * We haven't queried the MBX extension for the buffer
	     * data on this screen yet.  Call XmbufGetScreenInfo
	     * and fill in the data for all the returned visuals.
	     */
	    scr = ScreenOfDisplay(dpy, screen);
	    scrextdata->visdatatypes |= XOvlMBXBuffers;
	    XmbufGetScreenInfo(dpy, RootWindow(dpy, screen),
			       &nmono, &mono_info,
			       &nstereo, &stereo_info);
	    for (i = 0; i < nmono; i++) {
		if (find_visual(scr, mono_info[i].visualid, &vis, &depth)) {
		    visextdata = find_visdata(vis, info);
		    if (visextdata) {
			visextdata->numBuffers = mono_info[i].max_buffers;
			if (!visextdata->numBuffers) {
			    visextdata->numBuffers = XOVL_MAX_BUFFERS;
			}
			visextdata->datatypes |= XOvlMBXBuffers;
		    } else {
			/*
			 * We were unable to finish the query, so mark
			 * the data as unqueried so we can try again later.
			 */
			scrextdata->visdatatypes &= ~XOvlMBXBuffers;
		    }
		}
	    }
	    XFree(mono_info);
	    XFree(stereo_info);
	}
	if (!(candidateData->datatypes & XOvlMBXBuffers)) {
	    /*
	     * No data was returned from MBX for this visual,
	     * so fill in a default value.  Only mark the
	     * data valid if the server query completed.
	     */
	    candidateData->numBuffers = 0;
	    if (scrextdata->visdatatypes & XOvlMBXBuffers) {
		candidateData->datatypes |= XOvlMBXBuffers;
	    }
	}
    }

    return candidateData->numBuffers;
}


static Bool
CheckSharedPixels(
    Display			*dpy,
    int				 screen,
    XSolarisOvlSelectType		 searchtype,
    Visual			*candidateVis,
    Visual			*partnerVis,
    XExtDisplayInfo		*info)
{
    XOvlVisExtData		*candidateData,
    				*partnerData;
    XOvlScrExtData		*scrextdata;
    Screen			*scr;
    xOvlGetSharedPixelsReq	*req;
    xOvlGetSharedPixelsReply	 rep;
    unsigned int		 i;
    XOvlPGInfo			 pginfo;
    Visual			*vis;
    int				 depth;
    XOvlVisExtData		*visextdata;
    unsigned long		 commonplanes;

    candidateData = find_visdata(candidateVis, info);
    partnerData   = find_visdata(partnerVis, info);
    if (!candidateData || !partnerData) {
	/*
	 * Cannot store data for these visuals, assume the worst case.
	 */
	return True;
    }
    if (   !(candidateData->datatypes & XOvlSharedPixels)
	|| !(  partnerData->datatypes & XOvlSharedPixels))
    {
	scrextdata = find_screendata(dpy, screen, info);
	if (!(scrextdata->visdatatypes & XOvlSharedPixels)) {
	    /*
	     * We haven't queried the server for plane group data
	     * on this screen yet.  Send the query and fill in
	     * the data for the visuals indicated in the reply.
	     */
	    scr = ScreenOfDisplay(dpy, screen);
	    scrextdata->visdatatypes |= XOvlSharedPixels;
	    GetReq(OvlGetSharedPixels, req);
	    req->reqType    = info->codes->major_opcode;
	    req->ovlReqType = X_OvlGetSharedPixels;
	    req->screen     = screen;
	    if (_XReply(dpy, (xReply *)(&rep), 0, xFalse)) {
		for (i = 0; i < rep.numPGInfos; i++) {
		    _XRead(dpy, (char *)(&pginfo), sizeof(pginfo));
		    if (find_visual(scr, pginfo.vid, &vis, &depth)) {
			visextdata = find_visdata(vis, info);
			if (visextdata) {
			    visextdata->ovplanes   = pginfo.ovplanes;
			    visextdata->unplanes   = pginfo.unplanes;
			    visextdata->datatypes |= XOvlSharedPixels;
			} else {
			    /*
			     * We were unable to finish the query, so mark
			     * the data as unqueried so we can try again later.
			     */
			    scrextdata->visdatatypes &= ~XOvlSharedPixels;
			}
		    }
		}
	    }
	}
	if (!(candidateData->datatypes & XOvlSharedPixels)) {
	    /*
	     * No data was returned from the server for this
	     * visual, so fill in a default value.  Only mark
	     * the data valid if the server query completed.
	     */
	    candidateData->ovplanes = XOVL_ALL_PLANES;
	    candidateData->unplanes = XOVL_ALL_PLANES;
	    if (scrextdata->visdatatypes & XOvlSharedPixels) {
		candidateData->datatypes |= XOvlSharedPixels;
	    }
	}
	if (!(partnerData->datatypes & XOvlSharedPixels)) {
	    /*
	     * No data was returned from the server for this
	     * visual, so fill in a default value.  Only mark
	     * the data valid if the server query completed.
	     */
	    partnerData->ovplanes = XOVL_ALL_PLANES;
	    partnerData->unplanes = XOVL_ALL_PLANES;
	    if (scrextdata->visdatatypes & XOvlSharedPixels) {
		partnerData->datatypes |= XOvlSharedPixels;
	    }
	}
    }

    if (searchtype == XSolarisOvlSelectBestOverlay) {
	commonplanes = candidateData->ovplanes & partnerData->unplanes;
    } else {
	commonplanes = candidateData->unplanes & partnerData->ovplanes;
    }
    return commonplanes ? True : False;
}


static Bool
CheckSharedColors(
    Display			*dpy,
    int				screen,
    Visual			*candidateVis,
    Visual			*partnerVis,
    XExtDisplayInfo		*info)
{
    XOvlVisExtData		*candidateData,
    				*partnerData;
    XOvlScrExtData		*scrextdata;
    Screen			*scr;
    xOvlGetSharedColorsReq	*req;
    xOvlGetSharedColorsReply	 rep;
    unsigned int		 i;
    XOvlClutInfo		 clutinfo;
    Visual			*vis;
    int				 depth;
    XOvlVisExtData		*visextdata;

    candidateData = find_visdata(candidateVis, info);
    partnerData   = find_visdata(partnerVis,   info);
    if (!candidateData || !partnerData) {
	/*
	 * Cannot store data for these visuals, assume the worst case.
	 */
	return True;
    }
    if (   !(candidateData->datatypes & XOvlSharedColors)
	|| !(  partnerData->datatypes & XOvlSharedColors))
    {
	scrextdata = find_screendata(dpy, screen, info);
	if (!(scrextdata->visdatatypes & XOvlSharedColors)) {
	    /*
	     * We haven't queried the server for clut pool data
	     * on this screen yet.  Send the query and fill in
	     * the data for the visuals indicated in the reply.
	     */
	    scr = ScreenOfDisplay(dpy, screen);
	    scrextdata->visdatatypes |= XOvlSharedColors;
	    GetReq(OvlGetSharedColors, req);
	    req->reqType    = info->codes->major_opcode;
	    req->ovlReqType = X_OvlGetSharedColors;
	    req->screen     = screen;
	    if (_XReply(dpy, (xReply *)(&rep), 0, xFalse)) {
		for (i = 0; i < rep.numClutInfos; i++) {
		    _XRead(dpy, (char *)(&clutinfo), sizeof(clutinfo));
		    if (find_visual(scr, clutinfo.vid, &vis, &depth)) {
			visextdata = find_visdata(vis, info);
			if (visextdata) {
			    visextdata->clutpool   = (1 << clutinfo.pool);
			    visextdata->clutcount  = clutinfo.count;
			    visextdata->datatypes |= XOvlSharedColors;
			} else {
			    /*
			     * We were unable to finish the query, so mark
			     * the data as unqueried so we can try again later.
			     */
			    scrextdata->visdatatypes &= ~XOvlSharedColors;
			}
		    }
		}
	    }
	}
	if (!(candidateData->datatypes & XOvlSharedColors)) {
	    /*
	     * No data was returned from the server for this
	     * visual, so fill in a default value.  Only mark
	     * the data valid if the server query completed.
	     */
	    candidateData->clutpool  = XOVL_ANY_POOL;
	    candidateData->clutcount = 1;
	    if (scrextdata->visdatatypes & XOvlSharedColors) {
		candidateData->datatypes |= XOvlSharedColors;
	    }
	}
	if (!(partnerData->datatypes & XOvlSharedColors)) {
	    /*
	     * No data was returned from the server for this
	     * visual, so fill in a default value.  Only mark
	     * the data valid if the server query completed.
	     */
	    partnerData->clutpool  = XOVL_ANY_POOL;
	    partnerData->clutcount = 1;
	    if (scrextdata->visdatatypes & XOvlSharedColors) {
		partnerData->datatypes |= XOvlSharedColors;
	    }
	}
    }

    return (  (candidateData->clutpool & partnerData->clutpool)
	    && candidateData->clutcount <= 1)
	? True
	: False;
}


static void
ComputeVisualMatch(
    Display		*dpy,
    XOvlVisualMatch	*match,
    XSolarisOvlVisualCriteria	*pCriteria,
    XExtDisplayInfo	*info)
{
    Visual		*vis = match->candidate.vis;
    unsigned long	 hardmask,
    			 softmask,
    			 mask;
    unsigned long	 hardfailures,
    			 softfailures;

    hardmask = pCriteria->hardCriteriaMask;
    softmask = pCriteria->softCriteriaMask;
    mask = hardmask | softmask;
    hardfailures = 0;
    softfailures = 0;

    if (   (mask & XSolarisOvlVisualClass)
	&& (vis->class != pCriteria->c_class))
    {
	hardfailures |= hardmask & XSolarisOvlVisualClass;
	softfailures |= softmask & XSolarisOvlVisualClass;
    }
    if (   (mask & XSolarisOvlDepth)
	&& (match->candidate.depth != pCriteria->depth))
    {
	hardfailures |= hardmask & XSolarisOvlDepth;
	softfailures |= softmask & XSolarisOvlDepth;
    }
    if (   (mask & XSolarisOvlMinColors)
	&& (vis->map_entries < pCriteria->minColors))
    {
	hardfailures |= hardmask & XSolarisOvlMinColors;
	softfailures |= softmask & XSolarisOvlMinColors;
    }
    if (   (mask & XSolarisOvlMinRed)
	&& ((1 << bitcount(vis->red_mask)) < pCriteria->minRed))
    {
	hardfailures |= hardmask & XSolarisOvlMinRed;
	softfailures |= softmask & XSolarisOvlMinRed;
    }
    if (   (mask & XSolarisOvlMinGreen)
	&& ((1 << bitcount(vis->green_mask)) < pCriteria->minGreen))
    {
	hardfailures |= hardmask & XSolarisOvlMinGreen;
	softfailures |= softmask & XSolarisOvlMinGreen;
    }
    if (   (mask & XSolarisOvlMinBlue)
	&& ((1 << bitcount(vis->blue_mask)) < pCriteria->minBlue))
    {
	hardfailures |= hardmask & XSolarisOvlMinBlue;
	softfailures |= softmask & XSolarisOvlMinBlue;
    }
    if (   (mask & XSolarisOvlMinBitsPerRGB)
	&& (vis->bits_per_rgb < pCriteria->minBitsPerRGB))
    {
	hardfailures |= hardmask & XSolarisOvlMinBitsPerRGB;
	softfailures |= softmask & XSolarisOvlMinBitsPerRGB;
    }
    if (   (mask & XSolarisOvlMinBuffers)
	&& (  GetNumMBXBuffers(dpy, match->screen, vis, info)
	    < pCriteria->minBuffers))
   {
	hardfailures |= hardmask & XSolarisOvlMinBuffers;
	softfailures |= softmask & XSolarisOvlMinBuffers;
    }
    if (   (mask & XSolarisOvlUnsharedPixels)
	&& CheckSharedPixels(dpy, match->screen, match->searchtype,
			     vis, match->partner.vis, info))
    {
	hardfailures |= hardmask & XSolarisOvlUnsharedPixels;
	softfailures |= softmask & XSolarisOvlUnsharedPixels;
    }
    if (   (mask & XSolarisOvlUnsharedColors)
	&& CheckSharedColors(dpy, match->screen,
			     vis, match->partner.vis, info))
    {
	hardfailures |= hardmask & XSolarisOvlUnsharedColors;
	softfailures |= softmask & XSolarisOvlUnsharedColors;
    }
    if (   (mask & XSolarisOvlPreferredPartner)
	&& (!match->partnerpreferred))
    {
	hardfailures |= hardmask & XSolarisOvlPreferredPartner;
	softfailures |= softmask & XSolarisOvlPreferredPartner;
    }
    match->hardfailures    = hardfailures;
    match->numhardfailures = bitcount(hardfailures);
    match->softfailures    = softfailures;
    match->numsoftfailures = bitcount(softfailures);
}


#define XSolarisOvlAllCriteria		  \
    (XSolarisOvlVisualClass		| \
     XSolarisOvlDepth			| \
     XSolarisOvlMinColors		| \
     XSolarisOvlMinRed			| \
     XSolarisOvlMinGreen		| \
     XSolarisOvlMinBlue		| \
     XSolarisOvlMinBitsPerRGB		| \
     XSolarisOvlMinBuffers		| \
     XSolarisOvlUnsharedPixels		| \
     XSolarisOvlUnsharedColors		| \
     XSolarisOvlPreferredPartner)

static void
SetWorstMatch(
    XOvlVisualMatch	*match
)
{
    match->hardfailures = XSolarisOvlAllCriteria;
    match->softfailures = XSolarisOvlAllCriteria;
    match->numhardfailures =
	match->numsoftfailures =
	    bitcount(XSolarisOvlAllCriteria);
}


#define IsPerfectMatch(pm)	(!((pm)->hardfailures | (pm)->softfailures))

#define IsQualifiedMatch(pm)	(!(pm)->hardfailures)

#define IsBetterMatch(pm1, pm2)						\
    (   ((pm1)->numhardfailures < (pm2)->numhardfailures)		\
     || (    ((pm1)->numhardfailures == (pm2)->numhardfailures)		\
          && ((pm1)->numsoftfailures <  (pm2)->numsoftfailures)))


#define IsPerfectPair(povm, punm)					\
    (IsPerfectMatch(povm) && IsPerfectMatch(punm))

#define IsQualifiedPair(povm, punm)					\
    (IsQualifiedMatch(povm) && IsQualifiedMatch(punm))

#define IsBetterPair(povm1, punm1, povm2, punm2)			\
    (   (  ((povm1)->numhardfailures + (punm1)->numhardfailures)	\
         < ((povm2)->numhardfailures + (punm2)->numhardfailures))	\
     || (   (   ((povm1)->numhardfailures + (punm1)->numhardfailures)	\
	     == ((povm2)->numhardfailures + (punm2)->numhardfailures))	\
	 && (   ((povm1)->numsoftfailures + (punm1)->numsoftfailures)	\
	     <  ((povm2)->numsoftfailures + (punm2)->numsoftfailures))))


static void
set_visinfo(
    XVisualInfo		*visinfoReturn,
    XOvlVisualMatch	*match
)
{
    Visual		*vis = match->candidate.vis;

    visinfoReturn->visual        = vis;
    visinfoReturn->visualid      = match->candidate.vid;
    visinfoReturn->screen        = match->screen;
    visinfoReturn->depth         = match->candidate.depth;
    visinfoReturn->class         = vis->class;
    visinfoReturn->red_mask      = vis->red_mask;
    visinfoReturn->green_mask    = vis->green_mask;
    visinfoReturn->blue_mask     = vis->blue_mask;
    visinfoReturn->colormap_size = vis->map_entries;
    visinfoReturn->bits_per_rgb  = vis->bits_per_rgb;
}

/**********************************************************************/

Bool
XSolarisOvlQueryExtension(
    Display		*dpy,
    int			*event_basep,
    int			*error_basep
)
{
    XExtDisplayInfo	*info = find_display(dpy);

    if (XextHasExtension(info)) {
	*event_basep = info->codes->first_event;
	*error_basep = info->codes->first_error;
	return True;
    } else {
	return False;
    }
}


Status
XSolarisOvlQueryVersion(
    Display				*dpy,
    int					*major_versionp,
    int					*minor_versionp)
{
    XExtDisplayInfo			*info = find_display(dpy);
    xOvlQueryVersionReply		 rep;
    xOvlQueryVersionReq			*req;

    OvlCheckExtension(dpy, info, 0);

    LockDisplay(dpy);
    GetReq(OvlQueryVersion, req);
    req->reqType    = info->codes->major_opcode;
    req->ovlReqType = X_OvlQueryVersion;
    if (!_XReply(dpy, (xReply *)(&rep), 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return 0;
    }
    *major_versionp = rep.majorVersion;
    *minor_versionp = rep.minorVersion;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}


Window
XSolarisOvlCreateWindow(
    Display			*dpy,
    Window			 parent,
    int				 x,
    int				 y,
    unsigned int		 width,
    unsigned int		 height,
    unsigned int		 border_width,
    int				 depth,
    unsigned int		 class,
    Visual			*visual,
    unsigned long		 valuemask,
    XSetWindowAttributes	*attr
)
{
    XExtDisplayInfo		*info = find_display(dpy);
    Window			 wid;
    xOvlCreateWindowReq		*req;

    /*
     * REMIND: Is there a proper return value to indicate error?
     */
    OvlCheckExtension(dpy, info, (Window) 0);

    LockDisplay(dpy);
    GetReq(OvlCreateWindow, req);
    req->reqType     = info->codes->major_opcode;
    req->ovlReqType  = X_OvlCreateWindow;
    req->parent      = parent;
    req->x           = x;
    req->y           = y;
    req->width       = width;
    req->height      = height;
    req->borderWidth = border_width;
    req->depth       = depth;
    req->class       = class;
    if (visual == CopyFromParent) {
	req->visual = CopyFromParent;
    } else {
	req->visual = visual->visualid;
    }
    wid = req->wid = XAllocID(dpy);
    valuemask &= AllMaskBits;
    if (req->mask = valuemask) {

/* BugId 4130905 - There were only 3 args to this call instead of 4 -
the last argument attr was missing - causing Bad Xerror Request. When
the client lin libXext was recompiled, the bus error caused the 
client code to fail. Big change between 2.6 and 2.7 file. */

	_XProcessWindowAttributes(dpy, (xChangeWindowAttributesReq *)req,
				  valuemask, attr);
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return wid;
}


Bool
XSolarisOvlIsOverlayWindow(
    Display			*dpy,
    Window			 w
)
{
    XExtDisplayInfo		*info = find_display(dpy);
    xOvlIsOverlayWindowReq	*req;
    xOvlIsOverlayWindowReply	 rep;

    OvlCheckExtension(dpy, info, False);

    LockDisplay(dpy);
    GetReq(OvlIsOverlayWindow, req);
    req->reqType    = info->codes->major_opcode;
    req->ovlReqType = X_OvlIsOverlayWindow;
    req->wid        = w;
    if (_XReply (dpy, (xReply *)(&rep), 0, xTrue) == 0) {
	rep.isoverlay = False;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return rep.isoverlay;
}


void
XSolarisOvlSetWindowTransparent(
    Display			*dpy,
    Window			 w)
{
    XExtDisplayInfo		*info = find_display(dpy);
    xOvlSetWindowTransparentReq	*req;

    OvlSimpleCheckExtension(dpy, info);

    LockDisplay(dpy);
    GetReq(OvlSetWindowTransparent, req);
    req->reqType    = info->codes->major_opcode;
    req->ovlReqType = X_OvlSetWindowTransparent;
    req->wid        = w;
    UnlockDisplay(dpy);
    SyncHandle();
    return;
}


Status
XSolarisOvlSetPaintType(
    Display		*dpy,
    GC			 gc,
    XSolarisOvlPaintType	 paintType
)
{
    XExtDisplayInfo	*info = find_display(dpy);
    XOvlGCExtData	*gcextdata;
    xOvlSetPaintTypeReq	*req;
    XEDataObject	 obj;

    OvlCheckExtension(dpy, info, 0);

    LockDisplay(dpy);
    obj.gc = gc;
    gcextdata = (XOvlGCExtData *)
	XFindOnExtensionList(XEHeadOfExtensionList(obj),
			     info->codes->extension);
    if (!gcextdata) {
	if (paintType == XSolarisOvlPaintOpaque) {
	    /*
	     * No use creating an extension structure just to hold
	     * the default value.
	     */
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return 1;
	}
	gcextdata = Xmalloc(sizeof(XOvlGCExtData));
	if (!gcextdata) {
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return 0;
	}
	gcextdata->extdata.number       = info->codes->extension;
	gcextdata->extdata.free_private = NULL;
	gcextdata->extdata.private_data = NULL;
	gcextdata->paintType            = XSolarisOvlPaintOpaque;
	XAddToExtensionList(XEHeadOfExtensionList(obj), &(gcextdata->extdata));
    }
    if (gcextdata->paintType != paintType) {
	gcextdata->paintType = paintType;
	FlushGC(dpy, gc);
	GetReq(OvlSetPaintType, req);
	req->reqType    = info->codes->major_opcode;
	req->ovlReqType = X_OvlSetPaintType;
	req->gc         = gc->gid;
	req->paintType  = paintType;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}


XSolarisOvlPaintType
XSolarisOvlGetPaintType(
    Display		*dpy,
    GC			 gc
)
{
    XExtDisplayInfo	*info = find_display(dpy);
    XOvlGCExtData	*gcextdata;
    XSolarisOvlPaintType	 paintType;
    XEDataObject	 obj;

    OvlCheckExtension(dpy, info, XSolarisOvlPaintOpaque);

    LockDisplay(dpy);
    obj.gc = gc;
    gcextdata = (XOvlGCExtData *)
	XFindOnExtensionList(XEHeadOfExtensionList(obj),
			     info->codes->extension);
    paintType = (gcextdata) ? gcextdata->paintType : XSolarisOvlPaintOpaque;
    UnlockDisplay(dpy);
    SyncHandle();
    return paintType;
}


Status
XSolarisOvlCopyPaintType(
    Display				*dpy,
    Drawable				 src,
    Drawable				 dst,
    GC					 gc,
    int					 src_x,
    int					 src_y,
    unsigned int			 width,
    unsigned int			 height,
    int					 dest_x,
    int					 dest_y,
    unsigned long			 action_mask,
    unsigned long			 planemask
)
{
    XExtDisplayInfo			*info = find_display(dpy);
    xOvlCopyPaintTypeReq		*req;

    OvlCheckExtension(dpy, info, 0);

    LockDisplay(dpy);
    FlushGC(dpy, gc);
    GetReq(OvlCopyPaintType, req);
    req->reqType     = info->codes->major_opcode;
    req->ovlReqType  = X_OvlCopyPaintType;
    req->srcDrawable = src;
    req->dstDrawable = dst;
    req->gc          = gc->gid;
    req->srcX        = src_x;
    req->srcY        = src_y;
    req->destX       = dest_x;
    req->destY       = dest_y;
    req->width       = width;
    req->height      = height;
    req->action_mask = action_mask;
    req->bitPlane    = planemask;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}


Status
XSolarisOvlCopyAreaAndPaintType(
    Display					*dpy,
    Drawable					 colorSrc,
    Drawable					 paintTypeSrc,
    Drawable					 colorDst,
    Drawable					 paintTypeDst,
    GC						 colorGC,
    GC						 paintTypeGC,
    int						 colorSrcX,
    int						 colorSrcY,
    int						 paintTypeSrcX,
    int						 paintTypeSrcY,
    unsigned int				 width,
    unsigned int				 height,
    int						 colorDstX,
    int						 colorDstY,
    int						 paintTypeDstX,
    int						 paintTypeDstY,
    unsigned long				 action_mask,
    unsigned long				 planemask)
{
    XExtDisplayInfo				*info = find_display(dpy);
    xOvlCopyAreaAndPaintTypeReq			*req;

    OvlCheckExtension(dpy, info, 0);

    LockDisplay(dpy);
    FlushGC(dpy, colorGC);
    if (paintTypeGC && (paintTypeGC != colorGC))
	FlushGC(dpy, paintTypeGC);
    GetReq(OvlCopyAreaAndPaintType, req);
    req->reqType       = info->codes->major_opcode;
    req->ovlReqType    = X_OvlCopyAreaAndPaintType;
    req->colorSrc      = colorSrc;
    req->paintTypeSrc  = paintTypeSrc;
    req->colorDst      = colorDst;
    req->paintTypeDst  = paintTypeDst;
    req->colorGC       = colorGC->gid;
    req->paintTypeGC   = (paintTypeGC) ? paintTypeGC->gid : None;
    req->colorSrcX     = colorSrcX;
    req->colorSrcY     = colorSrcY;
    req->paintTypeSrcX = paintTypeSrcX;
    req->paintTypeSrcY = paintTypeSrcY;
    req->colorDstX     = colorDstX;
    req->colorDstY     = colorDstY;
    req->paintTypeDstX = paintTypeDstX;
    req->paintTypeDstY = paintTypeDstY;
    req->width         = width;
    req->height        = height;
    req->action_mask   = action_mask;
    req->bitPlane      = planemask;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}


XImage *
XReadScreen(
    Display		*dpy,
    Window		 w,
    int			 x,
    int			 y,
    unsigned int	 width,
    unsigned int	 height,
    Bool		 includeCursor
)
{
    XExtDisplayInfo	*info = find_display(dpy);
    xOvlReadScreenReq	*req;
    xOvlReadScreenReply	 rep;
    char		*data;
    long		 nbytes;
    XImage		*image;

    OvlCheckExtension(dpy, info, NULL);

    LockDisplay(dpy);
    GetReq (OvlReadScreen, req);
    req->reqType       = info->codes->major_opcode;
    req->ovlReqType    = X_OvlReadScreen;
    req->window        = w;
    req->x             = x;
    req->y             = y;
    req->width         = width;
    req->height        = height;
    req->includeCursor = includeCursor;

    if (   (_XReply(dpy, (xReply *)(&rep), 0, xFalse) == 0)
        || (rep.length == 0))
    {
	UnlockDisplay(dpy);
	SyncHandle();
	return NULL;
    }
    if (rep.length < (INT_MAX >> 2)) {
	nbytes = (long)rep.length << 2;
	data = Xmalloc((size_t)nbytes);
    } else {
	data = NULL;
    }
    if (!data) {
	_XEatDataWords(dpy, rep.length);
	UnlockDisplay(dpy);
	SyncHandle();
	return NULL;
    }
    _XReadPad (dpy, data, nbytes);
    image = XCreateImage(dpy, None,
			 24, ZPixmap, 0, data, width, height,
			 dpy->bitmap_pad, 0);
    if (image) {
	image->red_mask   = READSCREEN_REDMASK;
	image->green_mask = READSCREEN_GREENMASK;
	image->blue_mask  = READSCREEN_BLUEMASK;
    } else {
	Xfree(data);
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return image;
}


XSolarisOvlSelectStatus
XSolarisOvlSelectPartner(
    Display		*dpy,
    int			 screen,
    VisualID		 vid,
    XSolarisOvlSelectType	 vistype,
    int			 numCriteria,
    XSolarisOvlVisualCriteria	*pCriteria,
    XVisualInfo		*visinfoReturn,
    unsigned long	*unmetCriteriaReturn
)
{
    XExtDisplayInfo	*info = find_display(dpy);
    Screen		*scr;
    XOvlScrExtData	*scrextdata;
    XOvlVisPair		*vispair;
    int			 i,
    			 j;
    Depth		*depth;
    XOvlVisInfo		 partner;
    XOvlVisualMatch	 curMatch,
    			 betterMatch,
    			 bestMatch;
    XOvlVisEnumData	 visEnumData;
    unsigned long	 hardpreferred,
    			 softpreferred;

    OvlCheckExtension(dpy, info, XSolarisOvlFailure);

    LockDisplay(dpy);
    scr = ScreenOfDisplay(dpy, screen);
    scrextdata = find_screendata(dpy, screen, info);
    if (!scrextdata) {
	UnlockDisplay(dpy);
	SyncHandle();
	return XSolarisOvlFailure;
    }
    curMatch.screen = screen;
    curMatch.partner.vid = vid;
    if (!find_visual(scr, vid, &curMatch.partner.vis, &curMatch.partner.depth))
    {
	UnlockDisplay(dpy);
	SyncHandle();
	return XSolarisOvlFailure;
    }
    curMatch.searchtype = vistype;
    SetWorstMatch(&bestMatch);
    for (i = numCriteria; i > 0; --i) {
	SetWorstMatch(&betterMatch);
	curMatch.partnerpreferred = True;
	vispair = (XOvlVisPair *)(scrextdata->extdata.private_data);
	for (j = scrextdata->numVisPairs; j > 0; --j) {
	    if (vid ==
	            ((vistype == XSolarisOvlSelectBestOverlay)
			    ? (vispair->underlay.vid)
			    : (vispair->overlay.vid)))
	    {
		curMatch.candidate = (vistype == XSolarisOvlSelectBestOverlay)
		    ? vispair->overlay
		    : vispair->underlay;
		ComputeVisualMatch(dpy, &curMatch, pCriteria, info);
		if (IsPerfectMatch(&curMatch)) {
		    set_visinfo(visinfoReturn, &curMatch);
		    UnlockDisplay(dpy);
		    SyncHandle();
		    return XSolarisOvlSuccess;
		}
		if (IsBetterMatch(&curMatch, &betterMatch)) {
		    betterMatch = curMatch;
		}
	    }
	    vispair++;
	}
	if (!scrextdata->pairsRestricted) {
	    curMatch.partnerpreferred = False;
	    vis_enum_init(scr, &visEnumData);
	    while (vis_enum_next(&visEnumData,
				 &curMatch.candidate.vis,
				 &curMatch.candidate.depth))
	    {
		curMatch.candidate.vid = curMatch.candidate.vis->visualid;
		ComputeVisualMatch(dpy, &curMatch, pCriteria, info);
		if (IsPerfectMatch(&curMatch)) {
		    set_visinfo(visinfoReturn, &curMatch);
		    UnlockDisplay(dpy);
		    SyncHandle();
		    return XSolarisOvlSuccess;
		}
		if (IsBetterMatch(&curMatch, &betterMatch)) {
		    betterMatch = curMatch;
		}
	    }
	}
	if (IsQualifiedMatch(&betterMatch)) {
	    set_visinfo(visinfoReturn, &betterMatch);
	    *unmetCriteriaReturn = betterMatch.softfailures;
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return XSolarisOvlQualifiedSuccess;
	}
	if (IsBetterMatch(&betterMatch, &bestMatch)) {
	    bestMatch = betterMatch;
	}
	pCriteria++;
    }
    *unmetCriteriaReturn = bestMatch.hardfailures | bestMatch.softfailures;
    UnlockDisplay(dpy);
    SyncHandle();
    return XSolarisOvlCriteriaFailure;
}


XSolarisOvlSelectStatus
XSolarisOvlSelectPair(
    Display		*dpy,
    int			 screen,
    int			 numCriteria,
    XSolarisOvlPairCriteria	*pCriteria,
    XVisualInfo		*ovVisinfoReturn,
    XVisualInfo		*unVisinfoReturn,
    unsigned long	*unmetOvCriteriaReturn,
    unsigned long	*unmetUnCriteriaReturn)
{
    XExtDisplayInfo	*info = find_display(dpy);
    Screen		*scr;
    XOvlScrExtData	*scrextdata;
    XOvlVisPair		*vispair;
    int			 i,
    			 j;
    XOvlVisualMatch	 curOvMatch,	curUnMatch,
			 betterOvMatch,	betterUnMatch,
			 bestOvMatch,	bestUnMatch;
    XOvlVisEnumData	 ovVisEnumData,	unVisEnumData;

    OvlCheckExtension(dpy, info, XSolarisOvlFailure);
    LockDisplay(dpy);
    scr        = ScreenOfDisplay(dpy, screen);
    scrextdata = find_screendata(dpy, screen, info);
    if (!scrextdata) {
	UnlockDisplay(dpy);
	SyncHandle();
	return XSolarisOvlFailure;
    }
    curOvMatch.screen     = curUnMatch.screen = screen;
    curOvMatch.searchtype = XSolarisOvlSelectBestUnderlay;
    curUnMatch.searchtype = XSolarisOvlSelectBestOverlay;
    SetWorstMatch(&bestOvMatch);
    SetWorstMatch(&bestUnMatch);
    for (i = numCriteria; i > 0; --i) {
	SetWorstMatch(&betterOvMatch);
	SetWorstMatch(&betterUnMatch);
	curOvMatch.partnerpreferred = curUnMatch.partnerpreferred = True;
	vispair = (XOvlVisPair *)(scrextdata->extdata.private_data);
	for (j = scrextdata->numVisPairs; j > 0; --j) {
	    curOvMatch.candidate = curUnMatch.partner   = vispair->overlay;
	    curOvMatch.partner   = curUnMatch.candidate = vispair->underlay;
	    ComputeVisualMatch(dpy, &curOvMatch,
			       &pCriteria->overlayCriteria, info);
	    ComputeVisualMatch(dpy, &curUnMatch,
			       &pCriteria->underlayCriteria, info);
	    if (IsPerfectPair(&curOvMatch, &curUnMatch)) {
		set_visinfo(unVisinfoReturn, &curUnMatch);
		set_visinfo(ovVisinfoReturn, &curOvMatch);
		UnlockDisplay(dpy);
		SyncHandle();
		return XSolarisOvlSuccess;
	    }
	    if (IsBetterPair(&curOvMatch, &curUnMatch,
			     &betterOvMatch, &betterUnMatch))
	    {
		betterOvMatch = curOvMatch;
		betterUnMatch = curUnMatch;
	    }
	    vispair++;
	}
	if (!scrextdata->pairsRestricted) {
	    curOvMatch.partnerpreferred = False;
	    curUnMatch.partnerpreferred = False;
	    vis_enum_init(scr, &ovVisEnumData);
	    while (vis_enum_next(&ovVisEnumData,
				 &curOvMatch.candidate.vis,
				 &curOvMatch.candidate.depth))
	    {
		curOvMatch.candidate.vid = curOvMatch.candidate.vis->visualid;
		curUnMatch.partner       = curOvMatch.candidate;
		vis_enum_init(scr, &unVisEnumData);
		while (vis_enum_next(&unVisEnumData,
				     &curUnMatch.candidate.vis,
				     &curUnMatch.candidate.depth))
		{
		    curUnMatch.candidate.vid =
			    curUnMatch.candidate.vis->visualid;
		    curOvMatch.partner = curUnMatch.candidate;
		    ComputeVisualMatch(dpy, &curOvMatch,
				       &pCriteria->overlayCriteria, info);
		    ComputeVisualMatch(dpy, &curUnMatch,
				       &pCriteria->underlayCriteria, info);
		    if (IsPerfectPair(&curOvMatch, &curUnMatch)) {
			set_visinfo(unVisinfoReturn, &curUnMatch);
			set_visinfo(ovVisinfoReturn, &curOvMatch);
			UnlockDisplay(dpy);
			SyncHandle();
			return XSolarisOvlSuccess;
		    }
		    if (IsBetterPair(&curOvMatch, &curUnMatch,
				     &betterOvMatch, &betterUnMatch))
		    {
			betterOvMatch = curOvMatch;
			betterUnMatch = curUnMatch;
		    }
		}
	    }
	}
	if (IsQualifiedPair(&betterOvMatch, &betterUnMatch)) {
	    set_visinfo(ovVisinfoReturn, &betterOvMatch);
	    set_visinfo(unVisinfoReturn, &betterUnMatch);
	    *unmetOvCriteriaReturn = betterOvMatch.softfailures;
	    *unmetUnCriteriaReturn = betterUnMatch.softfailures;
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return XSolarisOvlQualifiedSuccess;
	}
	if (IsBetterPair(&betterOvMatch, &betterUnMatch,
			 &bestOvMatch, &bestUnMatch))
	{
	    bestOvMatch = betterOvMatch;
	    bestUnMatch = betterUnMatch;
	}
	pCriteria++;
    }
    *unmetOvCriteriaReturn = bestOvMatch.hardfailures|bestOvMatch.softfailures;
    *unmetUnCriteriaReturn = bestUnMatch.hardfailures|bestUnMatch.softfailures;
    UnlockDisplay(dpy);
    SyncHandle();
    return XSolarisOvlCriteriaFailure;
}
