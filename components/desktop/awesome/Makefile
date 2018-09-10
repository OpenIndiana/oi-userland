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
# Copyright (c) 2017 Dariusz Sendkowski
# Copyright (c) 2018 Till Wegmüller
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         awesome
COMPONENT_VERSION=      4.2
COMPONENT_PROJECT_URL=  https://awesomewm.org
COMPONENT_SUMMARY=      A highly configurable, next generation framework window manager for X.
COMPONENT_FMRI=         desktop/window-manager/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:ac5da1a99f5fad083821993d2b56d1cd9594164eafc0be2beb540598345d974f
COMPONENT_ARCHIVE_URL=  https://github.com/awesomeWM/awesome-releases/raw/master/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64=	$(CONFIGURE_BINDIR.32)

CMAKE_OPTIONS += "-DLUA_LIBRARY=/usr/lib/64/liblua.so"


build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TEST)

# Packages Required at Buildtime. Not found By gmake
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += library/lua/lgi-52

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/xdg/libxdg-basedir
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxkbcommon
REQUIRED_PACKAGES += x11/library/xcb-util
REQUIRED_PACKAGES += x11/library/xcb-util-cursor
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-wm
REQUIRED_PACKAGES += x11/library/xcb-util-xrm
