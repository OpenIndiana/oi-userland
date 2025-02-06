#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libwnck
HUMAN_VERSION=		43.2
COMPONENT_SUMMARY=	Window Navigator Construction Kit Library
COMPONENT_ARCHIVE_HASH=	sha256:55a7444ec1fbb95c086d40967388f231b5c0bbc8cffaa086bf9290ae449e51d5
COMPONENT_FMRI=         library/desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH= $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxres
