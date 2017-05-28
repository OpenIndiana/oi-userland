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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         awesome
COMPONENT_REVISION=     2
COMPONENT_VERSION=      4.1
COMPONENT_PROJECT_URL=  https://awesomewm.org
COMPONENT_SUMMARY=      A highly configurable, next generation framework window manager for X.
COMPONENT_FMRI=         desktop/window-manager/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:27a1db13ef4aa8e104a795e8c11c8611d75d8b0d864c277b8ef7c6f1ab6d04b8
COMPONENT_ARCHIVE_URL=  https://github.com/awesomeWM/awesome-releases/raw/master/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64=	$(CONFIGURE_BINDIR.32)


# CMake bug workaround: https://gitlab.kitware.com/cmake/cmake/issues/16404
CMAKE_OPTIONS += "-DLUA_INCLUDE_DIR=/usr/include/lua5.3"


build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TEST)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/xdg/libxdg-basedir
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += library/lua/lgi-53
REQUIRED_PACKAGES += SUNWcs
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
