#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Daniel Chan
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		extra-cmake-modules
COMPONENT_VERSION=	5.104.0
COMPONENT_SUMMARY=	KDE extra modules and scripts for CMake
COMPONENT_PROJECT_URL=	https://kde.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://invent.kde.org/frameworks/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:8fdd8ee6bdcaf7727d9f167be9f4a08ef5db1de06233021f3e84cbe4532a4c62
COMPONENT_FMRI=		developer/kde/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=	BSD 2-Clause, BSD 3-Clause, CC0v1, MIT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTION += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTION += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTION += -DBUILD_TESTING=OFF
CMAKE_OPTION += -DBUILD_QTHELP_DOCS=ON

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/sphinx

# Build dependencies
REQUIRED_PACKAGES += library/qt5

# Auto-generated dependencies
