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
#

BUILD_STYLE= configure
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-python
COMPONENT_VERSION=	1.16.2
COMPONENT_SUMMARY=	Python bindings for the GStreamer streaming media framework
COMPONENT_PROJECT_URL=	http://freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:208df3148d73d9f416d016564737585d8ea763d91201732d44b5fe688c6288a8
COMPONENT_ARCHIVE_URL=	http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/python-gst
COMPONENT_LICENSE=	LGPL v2.1
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSION=		3.5
PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		CPPFLAGS="$(CFLAGS)"
CONFIGURE_ENV+=		am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV+=		am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Ran 39 tests/d" '

# Build dependencies
REQUIRED_PACKAGES += library/python/pygobject-3

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
