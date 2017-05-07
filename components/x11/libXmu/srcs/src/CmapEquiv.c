/*
 * Copyright (c) 1996, Oracle and/or its affiliates. All rights reserved.
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


#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xmu/XmuSolaris.h>

#if defined(DEBUG)
#include <stdio.h>
#endif

#define INIT_LIST_SIZE 100

/*
 * Get's next pair of integers from a string
 */
static VisualID
getNextEntry(char **pp)
{
    char  *newP;
    VisualID	  entry;

    entry = strtoul(*pp, &newP, 0);
    if (newP == *pp) {
	return 0;
    }
    *pp = newP;

    return entry;
}

/*
 * Build a list of VisualIds that are equivalant to vidIn
 *
 * The format of the property string is a sequence of lists of
 * integers separated by a newline.
 * The first entry in each is the number of elements in the list.
 * The list of ids follows.
 */
static VisualID *
buildList(char *string, VisualID vidIn, VisualID *pOriginalList)
{
    VisualID  	*pList;
    char 	*p = string;
    int	 	num;

#ifdef DEBUG
    (void) memset(pOriginalList, 0, sizeof(VisualID)*INIT_LIST_SIZE);
#endif

    while (num = strtoul(p, &p, 0)) {
	int foundIt = 0;
	int i;
	if ((num + 1) > INIT_LIST_SIZE) {
	    pList = (VisualID *) malloc((num + 1) * sizeof(VisualID));
	    if (pList == NULL)
		return NULL;
	} else {
	    pList = pOriginalList;
	}
	for (i=0; i < num; i++) {
	    /* Build the list of VisualIDs equivalent to v */
	    VisualID vid;
	    if (vid = getNextEntry(&p)) {
		pList[i] = vid;
		if (vid == vidIn)
		    foundIt = 1;
	    } else {
	        /* string is formatted wrong */
#ifdef DEBUG
		fprintf(stderr, "property string is formatted wrong: %s\n",
			string);
#endif
	        break;
	    }
	}
#ifdef DEBUG
	if (*p != '\n')
	    fprintf(stderr, "property string is missing a newline: %s\n",
			string);
#endif
	if (foundIt) {
	    /* terminate the list */
	    pList[num] = 0;
	    break;
	}
	if (pList != pOriginalList)
	    free(pList);
	pList = NULL;
    }

    return pList;
}


static int
searchList(VisualID *pList, VisualID v)
{
	int i;
	for (i=0; pList[i] != 0; i++) {
	    if (pList[i] == v)
		return 1;
	}
	return 0;
}

static Bool
areEquiv(char *pPropString, VisualID v1, VisualID v2)
{
	VisualID list[INIT_LIST_SIZE];
	VisualID *pList;
	Bool foundMatch = False;

	/*
	 * Build a list of VisualIDS which are equivalent to v1
	 * using the array list if it fits.
	 */
	pList = buildList(pPropString, v1, list);
	if (pList == NULL)
	    return False;

	/* now see if v2 is in the list */
	if (searchList(pList, v2)) {
	    foundMatch  = True;
	}

	if (pList != list)
	    free(pList);

	return foundMatch;
}

#define SUN_CMAP_EQUIV_ATOM_NAME "_SUN_CMAP_EQUIV"

Bool
XSolarisCheckColormapEquivalence(Display *dpy,  int screen_number, 
				Visual *pVis1, Visual* pVis2)
{
	Atom theAtom;
	Atom actualType;
	int  actualFormat;
	unsigned long  nitems;
	unsigned long  bytesAfter;
	char  *prop;

	theAtom = XInternAtom(dpy, SUN_CMAP_EQUIV_ATOM_NAME, True);
	if (theAtom == None)
	    return False;

	if (!XGetWindowProperty(dpy, XRootWindow(dpy, screen_number), theAtom,
			    0, 8192, False, XA_STRING, &actualType,
			    &actualFormat, &nitems, &bytesAfter, 
			    (unsigned char **)&prop)) {
	     if (prop != NULL) {
		 Bool ret = areEquiv(prop, pVis1->visualid, pVis2->visualid);
		 XFree(prop);
		 return ret;
	     }
	}
	
	return False;
}
