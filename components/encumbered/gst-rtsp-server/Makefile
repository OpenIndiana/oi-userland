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

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-rtsp-server
COMPONENT_VERSION=	1.26.0
COMPONENT_SUMMARY=      Multimedia graph framework - rtsp server
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:e983c039496e3f75e39696554ce74db4120e2465de17aa1cc37160568e9b40bc
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/audio/gstreamer/rtsp-server
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# Dynamic library version number
SOVER := 0.$(shell printf '%02s%02s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION)))).0
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# build dependency not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/bad

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
