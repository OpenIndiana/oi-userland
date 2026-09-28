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
# Copyright 2024 Geoff Weiss
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gjs
HUMAN_VERSION =			1.90.0
COMPONENT_SUMMARY =		GNOME Javascript bindings
COMPONENT_ARCHIVE_HASH =	\
	sha256:47e9f22b1d4aca841c6c492b449b6de32ff680972183e26fe7b98a45c5c3fee1
COMPONENT_PROJECT_URL =		https://wiki.gnome.org/Projects/Gjs
COMPONENT_FMRI =		library/desktop/gjs
COMPONENT_CLASSIFICATION =	Desktop (GNOME)/Libraries
COMPONENT_LICENSE =		BSD-3-Clause, CC-BY-3.0, CC0-1.0, GPL-2.0+, GPL-3.0+, LGPL-2.0+, LGPL-3.0+, MIT, MPL-1.1, MPL-2.0
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# need for locale_t
CFLAGS += $(XPG7MODE)

CONFIGURE_OPTIONS += -Dprofiler=disabled
CONFIGURE_OPTIONS += -Dinstalled_tests=false

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:1
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/mozjs-140
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
