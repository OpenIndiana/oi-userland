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
#
BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		json-c
COMPONENT_VERSION=	0.17
COMPONENT_SUMMARY=	A JSON implementation in C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7550914d58fb63b2c3546f3ccfbe11f1c094147bd31a69dcd23714d7956159e6
COMPONENT_PROJECT_URL=	https://github.com/json-c/json-c
COMPONENT_ARCHIVE_URL=	https://s3.amazonaws.com/json-c_releases/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/json-c
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS:BOOL=OFF

# Note that tests might fail if valgrind is installed.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec//"' \
	'-n ' \
	'-e "/Failed/p" \
	'-e "/Passed/p"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
