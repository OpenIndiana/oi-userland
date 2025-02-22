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
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Till Wegmueller
#

BUILD_STYLE= meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libnotify
COMPONENT_VERSION=	0.8.4
COMPONENT_SUMMARY=      Library for desktop notifications
COMPONENT_ARCHIVE_HASH=	sha256:8fa04d4ebdc155b0a239df88bd9f09e8f2739d5707a1390b427ab4985f83d25a
COMPONENT_FMRI=         library/libnotify
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# we miss docbook-xsl-ns
CONFIGURE_OPTIONS += -Dman=false

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
