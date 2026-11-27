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
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		cmake
USE_DEFAULT_TEST_TRANSFORMS=	yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		highway
COMPONENT_VERSION=	1.4.0
COMPONENT_SUMMARY=	Highway - portable C++ SIMD library with run-time dispatch
COMPONENT_PROJECT_URL=	https://github.com/google/highway
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e72241ac9524bb653ae52ced768b508045d4438726a303f10181a38f764a453c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/highway
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	Apache-2.0 OR BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS +=	-DBUILD_SHARED_LIBS=ON
# Tests use OpenIndiana's googletest instead of downloading one
CMAKE_OPTIONS +=	-DHWY_SYSTEM_GTEST=ON

REQUIRED_PACKAGES +=	developer/googletest

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
