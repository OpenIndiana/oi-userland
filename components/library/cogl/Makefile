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
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cogl
COMPONENT_VERSION=      1.22.8
COMPONENT_SUMMARY=      cogl - An open source GPU graphics & utilities API
COMPONENT_PROJECT_URL=  https://rib.github.io/cogl/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:a805b2b019184710ff53d0496f9f0ce6dcca420c141a0f4f6fcc02131581d759
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.22/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/desktop/cogl
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

# make gcc-14 happy.
CFLAGS += -Wno-implicit-function-declaration

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-cogl-gst=yes
CONFIGURE_OPTIONS += --enable-sdl2=yes

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrandr
