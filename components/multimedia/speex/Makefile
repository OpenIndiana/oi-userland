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
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= speex
COMPONENT_VERSION= 1.2.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Open Source speech codec
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4b44d4f2b38a370a2d98a78329fefc56a0cf93d1c1be70029217baae6628feea
COMPONENT_ARCHIVE_URL= https://downloads.xiph.org/releases/speex/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.speex.org/
COMPONENT_FMRI=	codec/speex
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
