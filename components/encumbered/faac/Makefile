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
# Copyright 2015 Alexander Pyhalov
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         faac
COMPONENT_VERSION=      1.50
COMPONENT_SUMMARY=      Reference encoder and encoding library for MPEG2/4 AAC
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=  https://sourceforge.net/projects/faac
COMPONENT_ARCHIVE_HASH= sha256:e6876cba00cbd786a7f984d9aaada4d5bcb08d2582100366c70f6164d5c89214
COMPONENT_ARCHIVE_URL=  https://github.com/knik0/faac/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_FMRI=         audio/faac

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME)-$(COMPONENT_SRC) $(COMPONENT_SRC) )

# Missing files in build dir for configure without this.
#COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

#CONFIGURE_SCRIPT = $(@D)/configure

CFLAGS += $(CPP_LARGEFILES)

#CONFIGURE_OPTIONS += --enable-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
