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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libical
COMPONENT_VERSION=	1.0
COMPONENT_FMRI=		library/libical
COMPONENT_SUMMARY=	Libical is an Open Source implementation of the IETF's iCalendar Calendaring and Scheduling protocols
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/freeassociation/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7c39b3448e4927a2de2775d853f52b3aaeb42400970a3db0b01a78987e6ec0b7
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/freeassociation/files/libical/libical-1.0/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS+=		-DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+=		-DBUILD_SHARED_LIBS=On
CMAKE_OPTIONS+=		-DICAL_ERRORS_ARE_FATAL=false
CMAKE_OPTIONS.64 +=	-DLIB_SUFFIX=/$(MACH64)

COMPONENT_TEST_CMD = ctest
COMPONENT_TEST_TARGETS =

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
