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
# Copyright 2016 Jim Klimov
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libmad
COMPONENT_VERSION=      0.16.5
COMPONENT_SUMMARY=      A high-quality MPEG Audio Decoder
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e32320a010e3cc00bfa66e0cde523a969313cddfd81e07ec4e3ef06d10ad3fe0
COMPONENT_ARCHIVE_URL=  https://codeberg.org/tenacityteam/libmad/archive/$(HUMAN_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://www.underbit.com/products/mad/
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         library/audio/libmad

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DOPTIMIZE=ACCURACY

COMPONENT_POST_UNPACK_ACTION += ( $(MV) $(COMPONENT_NAME) $(COMPONENT_SRC) )

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
