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
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-editing-services1
COMPONENT_VERSION=	1.22.5
COMPONENT_SUMMARY=	Multimedia graph framework - editing services
COMPONENT_SRC_NAME=	gst-editing-services
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:bccdd3bd61d86829b16ce0e206db61b33f794ac1792423f9e7cc65d75d1a31b5
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI=		library/audio/gstreamer1/editing-services
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Some tests are failing because we miss some packages
unexport SHELLOPTS

# As test results keep only everything between the lines containing Ok: and Timeout:
COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^Ok:/,/^Timeout:/p" '

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
