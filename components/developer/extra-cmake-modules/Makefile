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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		extra-cmake-modules
COMPONENT_VERSION=	6.31.0
COMPONENT_SUMMARY=	KDE extra modules and scripts for CMake
COMPONENT_PROJECT_URL=	https://kde.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://invent.kde.org/frameworks/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:a27ff118cb96af3bacffb289f52e56af3eaa1d73b01f5ca794aa29b760f0204e
COMPONENT_FMRI=		developer/kde/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=	BSD 2-Clause, BSD 3-Clause, CC0v1, MIT

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.illumos):$(QT6_BINDIR)

CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH=$(QT6_LIBDIR)/cmake
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS += -DBUILD_TESTING=ON
CMAKE_OPTIONS += -DBUILD_QTHELP_DOCS=ON
CMAKE_OPTIONS += -DCMAKE_INSTALL_RPATH=$(QT6_LIBDIR)
CMAKE_OPTIONS += -DCMAKE_LIBRARY_PATH=$(QT6_LIBDIR)

# filter out timing (N.NN sec, NN.NN sec, etc.)
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[ 	][ 	]*[0-9][0-9]*\.[0-9][0-9] sec//"'

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/sphinx
REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += library/qt6

# Auto-generated dependencies
