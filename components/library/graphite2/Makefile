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
BUILD_BITS=32_and_64
BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		graphite2
COMPONENT_VERSION=	1.3.14
COMPONENT_FMRI=		library/c++/graphite2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SUMMARY=	Graphite2 - Library for rendering non-roman scripts
COMPONENT_PROJECT_URL=	http://graphite.sil.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
	sha256:f99d1c13aa5fa296898a181dff9b82fb25f6cc0933dbaa7a475d8109bd54209d
COMPONENT_ARCHIVE_URL= \
	https://github.com/silnrsi/graphite/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

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

# Manually added build dependencies
# For some reason, the SPARC build is needing this, but x86 does not.
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
