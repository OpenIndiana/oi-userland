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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		CalcMySky
COMPONENT_VERSION=	0.3.1
COMPONENT_SUMMARY=	CalcMySky simulates scattering of light by the atmosphere to render daytime and twilight skies (without stars)
COMPONENT_PROJECT_URL=	https://github.com/10110111/CalcMySky
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d284eaabcf21ad3d1f520a1d1b1b533f7c5f5a44ba92495dd38e238874e8e4d7
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		image/calcmysky
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	GPLv3.0
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

LDFLAGS += -lsocket -lnsl
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS=OFF
CMAKE_OPTIONS += -DQT_VERSION=5
CMAKE_OPTIONS += -DQt5_DIR=$(QT5_LIBDIR)/cmake/Qt5
#CMAKE_OPTIONS += -DQt5Charts_DIR=$(QT5_LIBDIR)/cmake/Qt5Charts
#CMAKE_OPTIONS += -DQt5Concurrent_DIR=$(QT5_LIBDIR)/cmake/Qt5Concurrent
#CMAKE_OPTIONS += -DQt5Core_DIR=$(QT5_LIBDIR)/cmake/Qt5Core
#CMAKE_OPTIONS += -DQt5Gui_DIR=$(QT5_LIBDIR)/cmake/Qt5Gui
#CMAKE_OPTIONS += -DQt5LinguistTools_DIR=$(QT5_LIBDIR)/cmake/Qt5LinguistTools
#CMAKE_OPTIONS += -DQt5MultimediaWidgets_DIR=$(QT5_LIBDIR)/cmake/Qt5MultimediaWidgets
#CMAKE_OPTIONS += -DQt5Multimedia_DIR=$(QT5_LIBDIR)/cmake/Qt5Multimedia
#CMAKE_OPTIONS += -DQt5Network_DIR=$(QT5_LIBDIR)/cmake/Qt5Network
#CMAKE_OPTIONS += -DQt5OpenGL_DIR=$(QT5_LIBDIR)/cmake/Qt5OpenGL
#CMAKE_OPTIONS += -DQt5Positioning_DIR=$(QT5_LIBDIR)/cmake/Qt5Positioning
#CMAKE_OPTIONS += -DQt5PrintSupport_DIR=$(QT5_LIBDIR)/cmake/Qt5PrintSupport
#CMAKE_OPTIONS += -DQt5Script_DIR=$(QT5_LIBDIR)/cmake/Qt5Script
#CMAKE_OPTIONS += -DQt5SerialPort_DIR=$(QT5_LIBDIR)/cmake/Qt5SerialPort
#CMAKE_OPTIONS += -DQt5Widgets_DIR=$(QT5_LIBDIR)/cmake/Qt5Widgets

COMPONENT_TEST_TRANSFORMS= \
	' -e "s/[0-9]*\.[0-9]* sec//" ' \
	' -n ' \
	' -e "/Passed/p" ' \
	' -e "/passed/p" ' \
	' -e "/Failed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
