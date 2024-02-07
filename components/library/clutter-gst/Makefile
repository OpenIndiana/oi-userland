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
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         clutter-gst
COMPONENT_VERSION=      3.0.27
COMPONENT_FMRI=      	library/desktop/clutter/clutter-gst
COMPONENT_SUMMARY=      gstreamer integration library for clutter
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:fe69bd6c659d24ab30da3f091eb91cd1970026d431179b0724f13791e8ad9f9d
COMPONENT_ARCHIVE_URL=  \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.0/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.clutter-project.org/

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -I/usr/X11/include
LDFLAGS += -lgdk_pixbuf-2.0

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Build dependencies
REQUIRED_PACKAGES += library/desktop/json-glib

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/cogl
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
