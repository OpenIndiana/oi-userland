/* Copyright (c) 1993, 2015, Oracle and/or its affiliates. All rights reserved.
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
** draw_db.c - Drawable veneer for DGA window buffer control routines
*/

#ifdef SERVER_DGA
#include <X11/Xlib.h>
#endif  /* SERVER_DGA */
#include "dga_incls.h"

int
dga_draw_db_grab (Dga_drawable dgadraw, int nbuffers, 
		  int (*vrtfunc)(Dga_drawable), u_int *vrtcounterp)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    return (0);
	}
	return (dga_db_grab((Dga_window)dgawin, nbuffers, vrtfunc, vrtcounterp));
    }
    case DGA_DRAW_PIXMAP:
    default:
	return (0);
    }
}

int
dga_draw_db_ungrab (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    return (0);
	}
	return (dga_db_ungrab((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	return (0);
    }
}

void
dga_draw_db_write (Dga_drawable dgadraw, int buffer,
		   int (*writefunc)(void*, Dga_drawable, int), 
		   void *data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    break;
	}
	dga_db_write((Dga_window)dgawin, buffer, writefunc, data);
	break;
    }
    case DGA_DRAW_PIXMAP:
	break;
    }
}

void
dga_draw_db_read (Dga_drawable dgadraw, int buffer,
		  int (*readfunc)(void*, Dga_drawable, int), 
		  void *data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    break;
	}
	dga_db_read((Dga_window)dgawin, buffer, readfunc, data);
	break;
    }
    case DGA_DRAW_PIXMAP:
	break;
    }
}

void
dga_draw_db_display (Dga_drawable dgadraw, int buffer,
		    int (*visfunc)(void*, Dga_drawable, int), 
		     void *data)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    break;
	}
	dga_db_display((Dga_window)dgawin, buffer, visfunc, data);
	break;
    }
    case DGA_DRAW_PIXMAP:
	break;
    }
}

void
dga_draw_db_interval (Dga_drawable dgadraw, int interval)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    break;
	}
	dga_db_interval((Dga_window)dgawin, interval);
	break;
    }
    case DGA_DRAW_PIXMAP:
	break;
    }
}

void
dga_draw_db_interval_wait (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    break;
	}
	dga_db_interval_wait((Dga_window)dgawin);
	break;
    }
    case DGA_DRAW_PIXMAP:
	break;
    }
}

int
dga_draw_db_interval_check (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - consider interval always expired */
	    return (1);
	}
	return (dga_db_interval_check((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - consider interval always expired */
	return (1);
    }
}

int
dga_draw_db_write_inquire (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - always return an invalid buffer index */
	    return (-1);
	}
	return (dga_db_write_inquire((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - always return an invalid buffer index */
	return (-1);
    }
}

int
dga_draw_db_read_inquire (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - always return an invalid buffer index */
	    return (-1);
	}
	return (dga_db_read_inquire((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - always return an invalid buffer index */
	return (-1);
    }
}

int
dga_draw_db_display_inquire (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - always return an invalid buffer index */
	    return (-1);
	}
	return (dga_db_display_inquire((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - always return an invalid buffer index */
	return (-1);
    }
}

int
dga_draw_db_display_done (Dga_drawable dgadraw, int flag, 
			  int (*display_done_func)(Dga_drawable))
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - consider display done (to prevent hangs) */
	    return (1);
	}
	return (dga_db_display_done((Dga_window)dgawin, flag, display_done_func));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - consider display done (to prevent hangs) */
	return (1);
    }
}

Dga_dbinfo *
dga_draw_db_dbinfop (Dga_drawable dgadraw)
{
    switch ( ((_Dga_drawable)dgadraw)->drawable_type) {
    case DGA_DRAW_WINDOW: {
	_Dga_window dgawin = (_Dga_window)dgadraw;
	if (!DGA_LOCKSUBJ_WINDOW(dgawin, dgawin->eLockSubj)) {
	    /* not applicable to multibuffers - return NULL */
	    return (NULL);
	}
	return (dga_win_dbinfop((Dga_window)dgawin));
    }
    case DGA_DRAW_PIXMAP:
    default:
	/* not applicable to pixmaps - return NULL */
	return (NULL);
    }
}
