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
# Copyright 2016 Alexander Pyhalov
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE= meson
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-python
COMPONENT_VERSION=	1.22.1
COMPONENT_SUMMARY=	Python bindings for the GStreamer streaming media framework
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:96008a441d685a64275a515b893ccad0fea1d560c43acd0763533e17f3a13ebb
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/python-gst
COMPONENT_LICENSE=	LGPL v2.1
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		CPPFLAGS="$(CFLAGS)"
CONFIGURE_ENV+=		am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV+=		am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "s/[        ]*[0-9][0-9]*\.[0-9][0-9]s//" ' \
        '-e "s/[        ]*exit status [0-9][0-9]*//" ' \
        '-e "/^[        ]*[0-9][0-9]*\/[0-9][0-9]* /p" ' \
        '-e "/^Summary of/p" ' \
        '-e "/^Ok:/,/^Timeout:/p" ' \
        '-e "/^Full log written.*/,/^ninja: build stopped.*/d" '

# Build dependencies
REQUIRED_PACKAGES += library/python/pygobject-3

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
