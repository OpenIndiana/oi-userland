#include <X11/copyright.h>

/* $XConsortium: Template.h,v 1.4 89/07/21 01:41:49 kit Exp $ */
/* Copyright	Massachusetts Institute of Technology	1987, 1988 */

#ifndef _Template_h
#define _Template_h

/****************************************************************
 *
 * Template widget
 *
 ****************************************************************/

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 height		     Height		Dimension	0
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 sensitive	     Sensitive		Boolean		True
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0

*/

/* define any special resource names here that are not in <X11/StringDefs.h> */

#define XtNtemplateResource "templateResource"

#define XtCTemplateResource "TemplateResource"

/* declare specific TemplateWidget class and instance datatypes */

typedef struct _TemplateClassRec*	TemplateWidgetClass;
typedef struct _TemplateRec*		TemplateWidget;

/* declare the class constant */

extern WidgetClass templateWidgetClass;

#endif /* _Template_h */
