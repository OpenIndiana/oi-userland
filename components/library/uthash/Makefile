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
# Copyright 2021 Benjamin S. Osenbach
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uthash
COMPONENT_VERSION=	2.3.0
COMPONENT_SUMMARY= 	C macros for hash tables and more
COMPONENT_PROJECT_URL=	https://github.com/troydhanson/uthash
COMPONENT_FMRI=		library/uthash
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/troydhanson/uthash/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e10382ab75518bad8319eb922ad04f907cb20cccb451a3aa980c9d005e661acc  
COMPONENT_LICENSE=BSD
COMPONENT_LICENSE_FILE=	uthash.license
TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk
