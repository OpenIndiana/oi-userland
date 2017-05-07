/*
 * Copyright (c) 1988-91 by Patrick J. Naughton.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 */

/*
 * Copyright (c) 1990, 2015, Oracle and/or its affiliates. All rights reserved.
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

#ifndef _XLOCK_H
#define _XLOCK_H

/*-
 *
 * xlock.h - external interfaces for new modes and OS defines.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>

#define MAXSCREENS 16
#define NUMCOLORS 64

typedef struct {
    GC          gc;		/* graphics context for animation */
    int         npixels;	/* number of valid entries in pixels */
    u_long      pixels[NUMCOLORS];	/* pixel values in the colormap */
}           perscreen;

extern perscreen Scr[MAXSCREENS];
extern Display *dsp;
extern int  screen;
extern XColor ssblack[MAXSCREENS];/* black color for screen saver screen */
extern XColor sswhite[MAXSCREENS];/* white color for screen saver screen */

extern char *ProgramName;
extern char *fontname;
extern char *background;
extern char *foreground;
extern char *text_name;
extern char *text_pass;
extern char *text_info;
extern char *text_valid;
extern char *text_invalid;
extern double saturation;
extern int  nicelevel;
extern int  delay;
extern int  batchcount;
extern int  reinittime;
extern int  timeout;
extern Bool usefirst;
extern Bool mono;
extern Bool nolock;
extern Bool allowroot;
extern Bool enablesaver;
extern Bool allowaccess;
extern Bool echokeys;
extern Bool verbose;
extern void (*callback) (Window);
extern void (*init) (Window);

extern void GetResources(int argc, char *argv[]);
extern void CheckResources(void);
extern void hsbramp(double h1, double s1, double b1,
		    double h2, double s2, double b2,
		    int count, u_char *red, u_char *green, u_char *blue);

#define seconds()	time(NULL)

/* PRINTFLIKE1 */
extern void error(const char *format, ...) _X_ATTRIBUTE_PRINTF(1,2) _X_NORETURN;

/*
 * Declare external interface routines for supported screen savers.
 */

extern void inithop(Window);
extern void drawhop(Window);

extern void initlife(Window);
extern void drawlife(Window);

extern void initqix(Window);
extern void drawqix(Window);

extern void initimage(Window);
extern void drawimage(Window);

extern void initblank(Window);
extern void drawblank(Window);

extern void initswarm(Window);
extern void drawswarm(Window);

extern void initrotor(Window);
extern void drawrotor(Window);

extern void initpyro(Window);
extern void drawpyro(Window);

extern void initflame(Window);
extern void drawflame(Window);

#define MAXRAND (2147483648.0)

#endif /* _XLOCK_H */
