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

BUILD_BITS=		64
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPILER=gcc
COMPONENT_NAME=		extra-cmake-modules
COMPONENT_VERSION=	5.93.0
COMPONENT_FMRI=		developer/kde/ECM
COMPONENT_PROJECT_URL=	https://kde.org/
COMPONENT_SUMMARY=	KDE extra modules and scripts for CMake
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_PREP_GIT=yes
GIT_TAG=v$(COMPONENT_VERSION)
GIT_REPO=https://github.com/KDE/$(COMPONENT_NAME)
GIT_BRANCH=refs/tags/$(GIT_TAG)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	sha256:6e53e70f293a11836353a5d81eac37d221d9525a85a28c02bb5e1060539c06c3
COMPONENT_LICENSE=	BSD 2-Clause, BSD 3-Clause, CC0v1, MIT

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTION += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTION += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTION += -DBUILD_TESTING=OFF
CMAKE_OPTION += -DBUILD_QTHELP_DOCS=ON

# Build dependencies
REQUIRED_PACKAGES += library/qt5

