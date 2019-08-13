/*
* $XConsortium: LogoP.h,v 1.6 89/05/11 01:05:52 kit Exp $
*/

/*
Copyright 1988 by the Massachusetts Institute of Technology

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of M.I.T. not be used in
advertising or publicity pertaining to distribution of the
software without specific, written prior permission.
M.I.T. makes no representations about the suitability of
this software for any purpose.  It is provided "as is"
without express or implied warranty.
*/

#ifndef _XawLogoP_h
#define _XawLogoP_h

#include <./Xaw3_1Logo.h>

typedef struct {
	 Pixel	 fgpixel;
	 Boolean reverse_video;
	 GC	 foreGC;
	 GC	 backGC;
   } LogoPart;

typedef struct _LogoRec {
   CorePart core;
   LogoPart logo;
   } LogoRec;

typedef struct {int dummy;} LogoClassPart;

typedef struct _LogoClassRec {
   CoreClassPart core_class;
   LogoClassPart logo_class;
   } LogoClassRec;

extern LogoClassRec logoClassRec;

#endif /* _XawLogoP_h */
