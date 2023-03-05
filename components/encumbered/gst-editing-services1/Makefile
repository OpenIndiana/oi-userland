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

COMPONENT_NAME=		gst-editing-services1
COMPONENT_VERSION=	1.22.1
COMPONENT_SUMMARY=	Multimedia graph framework - editing services
COMPONENT_SRC_NAME=	gst-editing-services
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:0f9e5e08ef80a4b9a0e971c5f032b13c71aa6fef236265c2d615456e15161438
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI=		library/audio/gstreamer1/editing-services
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	gst-editing-services1.license

# Set python version used by this product
PYTHON_VERSION=		3.9

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Some tests are failing because we miss some packages
# (first) delete the timing information from any line
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

# Dependencies not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/bad
REQUIRED_PACKAGES += library/audio/gstreamer1/devtools

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
