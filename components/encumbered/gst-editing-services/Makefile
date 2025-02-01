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

COMPONENT_NAME=		gst-editing-services
COMPONENT_VERSION=	1.24.12
COMPONENT_SUMMARY=	Multimedia graph framework - editing services
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:688222f270d24be4ed8a3852fa331897db662c7b813fbc39f6deb176b33ec9c0
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_FMRI=		library/audio/gstreamer/editing-services
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

# We use python vendor-packages instead of site-packages
COMPONENT_POST_INSTALL_ACTION += \
    cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
    $(RM) -r vendor-packages ; \
    $(MV) site-packages vendor-packages ;

# Dynamic library version number
SOVER := 0.$(shell printf '%02s%02s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION)))).0
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Dependencies not detected by REQUIRED_PACKAGES
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/bad
REQUIRED_PACKAGES += utility/bash-completion

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/devtools
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
