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
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE=	meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gst-rtsp-server1
COMPONENT_VERSION=      1.22.1
COMPONENT_SUMMARY=      Multimedia graph framework - rtsp server
COMPONENT_SRC_NAME=	gst-rtsp-server
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:4e0b972608f67d5d8f5363c827cfcf132b0e00877be6f1905358d514249b05a3
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer1/rtsp-server
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= gst-rtsp-server1.license

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

#gcc_OPT = -O2

PATH = $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "s/[        ]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
        '-e "s/[        ]*exit status [0-9][0-9]*//" ' \
        '-e "/^[        ]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
        '-e "/^Summary of/p" ' \
        '-e "/^Ok:/,/^Timeout:/p" ' \
        '-e "/^Full log written.*/,/^ninja: build stopped.*/d" '

# build dependency not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio

# Manually added dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/bad

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
