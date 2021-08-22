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
# Copyright 2021 Jake Goerzen
#

BUILD_BITS= 64
BUILD_STYLE= cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		stellarium
COMPONENT_VERSION=	0.21.1
COMPONENT_SUMMARY=	Stellarium Astronomy Software
COMPONENT_PROJECT_URL=	https://stellarium.org
COMPONENT_FMRI=		image/stellarium
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SRC_NAME=	stellarium
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:072309c6bc48233b39884ae558b23764d0e08eabd96b014b53d780be11a33211
COMPONENT_ARCHIVE_URL=  https://github.com/Stellarium/stellarium/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz
COMPONENT_LICENSE=	GPLv2.0
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lnsl
LD_OPTIONS += -L/usr/lib/qt/5.12/lib/amd64 -R/usr/lib/qt/5.12/lib/amd64

CMAKE_OPTIONS += -DENABLE_GPS=OFF
CMAKE_OPTIONS += -DQt5Concurrent_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Concurrent
CMAKE_OPTIONS += -DQt5Core_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Core
CMAKE_OPTIONS += -DQt5Gui_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Gui
CMAKE_OPTIONS += -DQt5LinguistTools_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5LinguistTools
CMAKE_OPTIONS += -DQt5MultimediaWidgets_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5MultimediaWidgets
CMAKE_OPTIONS += -DQt5Multimedia_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Multimedia
CMAKE_OPTIONS += -DQt5Network_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Network
CMAKE_OPTIONS += -DQt5OpenGL_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5OpenGL
CMAKE_OPTIONS += -DQt5Positioning_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Positioning
CMAKE_OPTIONS += -DQt5PrintSupport_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5PrintSupport
CMAKE_OPTIONS += -DQt5Script_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Script
CMAKE_OPTIONS += -DQt5SerialPort_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5SerialPort
CMAKE_OPTIONS += -DQt5Widgets_DIR=/usr/lib/qt/5.12/lib/amd64/cmake/Qt5Widgets
CMAKE_OPTIONS += -DUSE_PLUGIN_CALENDARS=OFF
CMAKE_OPTIONS += -DGETTEXT_MSGMERGE_EXECUTABLE=/usr/bin/gmsgmerge
CMAKE_OPTIONS += -DGETTEXT_MSGFMT_EXECUTABLE=/usr/bin/gmsgfmt


# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
