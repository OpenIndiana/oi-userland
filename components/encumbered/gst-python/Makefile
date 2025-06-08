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
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-python
COMPONENT_VERSION=	1.26.2
COMPONENT_SUMMARY=	Python bindings for the GStreamer streaming media framework
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:757ae964c16a542d60708bcb8a67c56c5be83785c0d1c534b9b9366bf676746e
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=	library/python/python-gst
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

#
# Reasons for encumbered:
# - depends on encumbered library/audio/gstreamer/plugin/bad
#

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# https://gitlab.freedesktop.org/gstreamer/gstreamer/-/issues/4023
CONFIGURE_OPTIONS += -Dpython.platlibdir=$(PYTHON_VENDOR_PACKAGES)

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/bad
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
