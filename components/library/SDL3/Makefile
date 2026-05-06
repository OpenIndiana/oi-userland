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
# Copyright (c) 2025 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
# At the moment building static libs cannot be switched off and if removed eg. by DROP_STATIC_LIBS it will create problems
# (missing reference to static libs)
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		SDL3
COMPONENT_VERSION=	3.4.8
COMPONENT_SUMMARY=	Simple DirectMedia Layer is a cross-platform library to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware
COMPONENT_PROJECT_URL=	https://www.libsdl.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e9fff7467fb60f037e6708da18b25560649e4c63edc2a69bb871b960d9cbfbba
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/sdl3
COMPONENT_CLASSIFICATION =	System/Libraries
COMPONENT_LICENSE=	ZLIB
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG7MODE)

CMAKE_OPTIONS += -DSDL_TESTS=ON
CMAKE_OPTIONS += -DSDL_X11_XRANDR=ON
CMAKE_OPTIONS += -DSDL_X11_XINPUT=ON

COMPONENT_TEST_ENV += TZ=UTC
COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

# Manually added build dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver


# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
