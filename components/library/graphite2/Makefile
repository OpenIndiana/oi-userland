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
# Copyright 2016 Gary Mills
# Copyright 2014 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		graphite2
COMPONENT_VERSION=	1.3.6
COMPONENT_FMRI=		library/c++/graphite2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/silgraphite
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	graphite-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:475e7657ac606ed8805518031729c1273cf7d9d422169ac6f7882e01d832af75
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/silgraphite/files/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

COMPONENT_SUMMARY=	Graphite2 - Library for rendering non-roman scripts

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

# need this to use abs(float)
LDFLAGS += -lm

CMAKE_OPTIONS+=		-DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+=		-DGRAPHITE2_ASAN=OFF
CMAKE_OPTIONS+=		-DGRAPHITE2_COMPARE_RENDERER=OFF
CMAKE_OPTIONS+=		-DGRAPHITE2_DOXYGEN_CONFIG=public
CMAKE_OPTIONS+=		-DGRAPHITE2_NFILEFACE=OFF
CMAKE_OPTIONS+=		-DGRAPHITE2_NSEGCACHE=OFF
CMAKE_OPTIONS+=		-DGRAPHITE2_NTRACING=ON
CMAKE_OPTIONS+=		-DGRAPHITE2_TELEMETRY=OFF
CMAKE_OPTIONS+=		-DGRAPHITE2_VM_TYPE=auto
#CMAKE_OPTIONS+=	-DLATEX=/usr/bin/latex

COMPONENT_TEST_CMD = ctest
COMPONENT_TEST_TARGETS =

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk


