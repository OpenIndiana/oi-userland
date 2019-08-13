/* $XConsortium: Template.c,v 1.2 88/10/25 17:40:25 swick Exp $ */
/* Copyright	Massachusetts Institute of Technology	1987, 1988 */

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include <X11/Xaw/TemplateP.h>

static XtResource resources[] = {
#define offset(field) XtOffset(TemplateWidget, template.field)
    /* {name, class, type, size, offset, default_type, default_addr}, */
    { XtNtemplateResource, XtCTemplateResource, XtRTemplateResource, sizeof(char*),
	  offset(resource), XtRString, "default" },
#undef offset
};

static void TemplateAction(/* Widget, XEvent*, String*, Cardinal* */) {
};

static XtActionsRec actions[] =
{
  /* {name, procedure}, */
    {"template",	TemplateAction},
};

static char translations[] =
"<Key>:		template()	\n\
";

TemplateClassRec templateClassRec = {
  { /* core fields */
    /* superclass		*/	(WidgetClass) &widgetClassRec,
    /* class_name		*/	"Template",
    /* widget_size		*/	sizeof(TemplateRec),
    /* class_initialize		*/	NULL,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	NULL,
    /* initialize_hook		*/	NULL,
    /* realize			*/	XtInheritRealize,
    /* actions			*/	actions,
    /* num_actions		*/	XtNumber(actions),
    /* resources		*/	resources,
    /* num_resources		*/	XtNumber(resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	NULL,
    /* resize			*/	NULL,
    /* expose			*/	NULL,
    /* set_values		*/	NULL,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	translations,
    /* query_geometry		*/	XtInheritQueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
  },
  { /* template fields */
    /* empty			*/	0
  }
};

WidgetClass templateWidgetClass = (WidgetClass)&templateClassRec;
