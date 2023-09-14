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
# Copyright 2015 Aurelien Larcher
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         faad2
COMPONENT_VERSION=      2.10.1
COMPONENT_SUMMARY=      Freeware Advanced Audio (AAC) Decoder including SBR decoding
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4c16c71295ca0cbf7c3dfe98eb11d8fa8d0ac3042e41604cfd6cc11a408cf264
COMPONENT_PROJECT_URL=  https://github.com/knik0/faad2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_FMRI=         audio/faad2
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -if)
COMPONENT_POST_CONFIGURE_ACTION = ( $(CP) -rp $(BUILD_DIR_$(BITS))/include/*.h $(SOURCE_DIR)/include/ )

CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --without-drm
CONFIGURE_OPTIONS += --with-mpeg4ip

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
