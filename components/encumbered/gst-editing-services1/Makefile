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
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE=	meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-editing-services1
COMPONENT_VERSION=	1.20.1
COMPONENT_SUMMARY=	Multimedia graph framework - editing services
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI=		library/audio/gstreamer1/editing-services
COMPONENT_SRC_NAME=	gst-editing-services
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:6ace1b21b58e0110b7dadd469f79b77e2f47d6207604231492531ae9fd4148df
COMPONENT_ARCHIVE_URL= \
  https://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org/
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	gst-editing-services1.license

# Set python version used by this product
PYTHON_VERSION=		3.9

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

#gcc_OPT = -O2

PATH = $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

test: $(NO_TESTS)

# build dependency not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/devtools
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
