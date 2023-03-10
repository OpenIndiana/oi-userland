#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	gtkperf
COMPONENT_VERSION= 	0.40
COMPONENT_REVISION=	3
COMPONENT_SUMMARY= 	Gtk+ performance testing application
COMPONENT_SRC= 		$(COMPONENT_NAME)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)_$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9704344e732038eecbd007dd996a56293a6b027b5b76f3f036273a3fae1ab27b
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gtkperf/files/gtkperf/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL= http://gtkperf.sourceforge.net/
COMPONENT_BUILD_ARGS= -j50

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += \
	( cd $(@D) && \
		$(TOUCH) config.rpath &&\
		autoreconf -fi)

CONFIGURE_OPTIONS += --disable-nls

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
