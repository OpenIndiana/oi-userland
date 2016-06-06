/*-
 * HSBmap.c - Create an HSB ramp.
 *
 * Copyright (c) 1991, 2011, Oracle and/or its affiliates. All rights reserved.
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
 *
 * Author: Patrick J. Naughton
 * naughton@sun.com
 */


#include <sys/types.h>
#include <math.h>
#include "xcolor.h"

static void
hsb2rgb(
    double      H,
    double      S,
    double      B,
    u_char     *r,
    u_char     *g,
    u_char     *b)
    
{
    register int i;
    register double f,
                bb;
    register u_char p,
                q,
                t;

    H -= floor(H);		/* remove anything over 1 */
    H *= 6.0;
    i = floor(H);		/* 0..5 */
    f = H - (float) i;		/* f = fractional part of H */
    bb = 255.0 * B;
    p = (u_char) (bb * (1.0 - S));
    q = (u_char) (bb * (1.0 - (S * f)));
    t = (u_char) (bb * (1.0 - (S * (1.0 - f))));
    switch (i) {
    case 0:
	*r = (u_char) bb;
	*g = t;
	*b = p;
	break;
    case 1:
	*r = q;
	*g = (u_char) bb;
	*b = p;
	break;
    case 2:
	*r = p;
	*g = (u_char) bb;
	*b = t;
	break;
    case 3:
	*r = p;
	*g = q;
	*b = (u_char) bb;
	break;
    case 4:
	*r = t;
	*g = p;
	*b = (u_char) bb;
	break;
    case 5:
	*r = (u_char) bb;
	*g = p;
	*b = q;
	break;
    }
}


void
HSBramp(
    double      h1,
    double      s1,
    double      b1,
    double      h2,
    double      s2,
    double      b2,
    int         start,
    int         end,
    u_char     *red,
    u_char     *green,
    u_char     *blue)
{
    double      dh,
                ds,
                db;
    register u_char *r,
               *g,
               *b;
    register int i;

    r = red;
    g = green;
    b = blue;
    dh = (h2 - h1) / 255.0;
    ds = (s2 - s1) / 255.0;
    db = (b2 - b1) / 255.0;
    for (i = start; i <= end; i++) {
	hsb2rgb(h1, s1, b1, r++, g++, b++);
	h1 += dh;
	s1 += ds;
	b1 += db;
    }
}
