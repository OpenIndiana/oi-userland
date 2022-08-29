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
# Copyright 2015 Alexander Pyhalov#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= speexdsp
COMPONENT_VERSION= 1.2.1
COMPONENT_SUMMARY= Speex DSP library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8c777343e4a6399569c72abc38a95b24db56882c83dbdb6c6424a5f4aeb54d3d
COMPONENT_ARCHIVE_URL=	http://downloads.xiph.org/releases/speex/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.speex.org/
COMPONENT_FMRI=	library/speexdsp
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = COPYING

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
