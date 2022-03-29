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

COMPONENT_NAME=         gst-devtools1
COMPONENT_VERSION=      1.20.1
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      Multimedia graph framework - devtools
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         library/audio/gstreamer1/devtools
COMPONENT_SRC_NAME=	gst-devtools
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:81f1c7ef105b8bdb63412638952f6320723b3161c96a80f113b020e2de554b2b
COMPONENT_ARCHIVE_URL=  \
	https://gstreamer.freedesktop.org/src/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://gstreamer.freedesktop.org/
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= gst-devtools1.license

# Set python version used by this product
PYTHON_VERSION=		3.7

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

#gcc_OPT = -O2

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

test: $(NO_TESTS)

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
