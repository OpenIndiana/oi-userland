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
# Copyright 2014-2017, Aurelien Larcher.  All rights reserved.
# Copyright 2019, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		graphite2
COMPONENT_VERSION=	1.3.13
COMPONENT_FMRI=		library/c++/graphite2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SUMMARY=	Graphite2 - Library for rendering non-roman scripts
COMPONENT_PROJECT_URL=	http://graphite.sil.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
	sha256:dd63e169b0d3cf954b397c122551ab9343e0696fb2045e1b326db0202d875f06
COMPONENT_ARCHIVE_URL= \
	https://github.com/silnrsi/graphite/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1

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

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
