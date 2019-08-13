/*
* $XConsortium: CommandI.h,v 1.16 89/05/11 01:05:05 kit Exp $
*/


/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 *
 *  A few definitions to make Command.c easier to read.
 *   
 */

  /* Yes, this is gross, but the code will be easier to read.
     Trust me.  */
#define ComWx                            cbw->core.x
#define ComWy                            cbw->core.y
#define ComWdepth                        cbw->core.depth
#define ComWwidth                        cbw->core.width
#define ComWheight                       cbw->core.height
#define ComWborder_width                 cbw->core.border_width
#define ComWbackground                   cbw->core.background_pixel
#define ComWforeground                   cbw->label.foreground
#define ComWfont                         cbw->label.font
#define ComWlabel                        cbw->label.label
#define ComWjustify                      cbw->label.justify
#define ComWinternalWidth                cbw->label.internal_width
#define ComWinternalHeight               cbw->label.internal_height
#define ComWlabelX                       cbw->label.label_x
#define ComWlabelY                       cbw->label.label_y + cbw->label.font->max_bounds.ascent
#define ComWlabelWidth                   cbw->label.label_width
#define ComWlabelHeight                  cbw->label.label_height
#define ComWlabelLen                     cbw->label.label_len
#define ComWlabelGC                      cbw->label.normal_GC
#define ComWnormalGC                     cbw->command.normal_GC
#define ComWgrayGC                       cbw->label.gray_GC
#define ComWgrayPixmap                   cbw->label.gray_pixmap
#define ComWsensitive                    cbw->core.sensitive 
#define ComWcallbackList                 cbw->command.callback_list
#define ComWcallback                     cbw->command.callback
#define ComWclosure                      cbw->command.closure
#define ComWinverseGC                    cbw->command.inverse_GC
#define ComWhighlightThickness           cbw->command.highlight_thickness
#define ComWset                          cbw->command.set
#define ComWhighlighted                  cbw->command.highlighted

#define XtCBField(cbw,field)  cbw->command.field
#define XtLField(cbw,field)   cbw->label.field
#define XtCField(cbw,field)   cbw->core.field


static void Initialize();
static void Redisplay();
static Boolean SetValues();
static void Set();
static void Reset();
static void Notify();
static void Unset();
static void Highlight();
static void Unhighlight();
static void Unset();
static void Destroy();
