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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		brotli
COMPONENT_VERSION=	1.1.0
COMPONENT_SUMMARY=	Library for generic-purpose lossless compression algorithm
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/google/brotli
COMPONENT_ARCHIVE_URL= 	$(COMPONENT_PROJECT_URL)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e720a6ca29428b803f4ad165371771f5398faba397edf6778837a18599ea13ff
COMPONENT_FMRI=		library/brotli
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=1

CMAKE_OPTIONS.64 += -DLIB_SUFFIX=/$(MACH64)

# Strip times from test output, since they're always different
COMPONENT_TEST_TRANSFORMS += '-e "s%\([0-9\.]\)* sec%%"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
