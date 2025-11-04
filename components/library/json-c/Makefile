#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2022 Niklas Poslovski
# Copyright 2025 Klaus Ziegler
#
BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		json-c
COMPONENT_VERSION=	0.18
COMPONENT_SUMMARY=	A JSON implementation in C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:876ab046479166b869afc6896d288183bbc0e5843f141200c677b3e8dfb11724
COMPONENT_PROJECT_URL=	https://github.com/json-c/json-c
COMPONENT_ARCHIVE_URL=	https://s3.amazonaws.com/json-c_releases/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/json-c
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_FMRI.json-c-32= $(COMPONENT_FMRI)/32

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS:BOOL=OFF

# Note that tests might fail if valgrind is installed.
TEST_CONFLICTING_PACKAGES += developer/debug/valgrind

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
