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

COMPONENT_NAME=         gst-devtools1
COMPONENT_VERSION=      1.22.3
COMPONENT_SUMMARY=      Multimedia graph framework - devtools
COMPONENT_SRC_NAME=		gst-devtools
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:446ac9c42d502cbfd9081737cc1b853b3c1f50db77ca7ccd01aea10f687550c1
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer1/devtools
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python3' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
#
COMPONENT_POST_INSTALL_ACTION += \
    $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' \
	$(PROTOUSRBINDIR)/gst-validate-launcher;

# Test fail because we are missing gst-validate
unexport SHELLOPTS

# As test results keep only everything between the lines containing Ok: and Timeout:
COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^Ok:/,/^Timeout:/p" '

# build dependency not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/bad
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/gstreamer1/rtsp-server
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
