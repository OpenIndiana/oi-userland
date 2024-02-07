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
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         faad2
COMPONENT_VERSION=      2.11.1
COMPONENT_SUMMARY=      Freeware Advanced Audio (AAC) Decoder including SBR decoding
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:72dbc0494de9ee38d240f670eccf2b10ef715fd0508c305532ca3def3225bb06
COMPONENT_PROJECT_URL=  https://github.com/knik0/faad2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_FMRI=         audio/faad2
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

#COMPONENT_POST_CONFIGURE_ACTION = ( $(CP) -rp $(BUILD_DIR_$(BITS))/include/*.h $(SOURCE_DIR)/include/ )

CFLAGS += $(CPP_LARGEFILES)

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Two man pages are in the sources that need to be copied into the proto area
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
	$(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
	$(CP) $(SOURCE_DIR)/frontend/faad.man $(PROTOUSRSHAREMAN1DIR)/faad.1 ; \
	$(CP) $(SOURCE_DIR)/docs/libfaad.3 $(PROTOUSRSHAREMAN3DIR)/

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
