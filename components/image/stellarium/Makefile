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
# Copyright 2022 Jake Goerzen
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		stellarium
COMPONENT_VERSION=	23.2
COMPONENT_SUMMARY=	Planetarium with realistic 3D sky just like seeing with naked eye, binoculars or telescope.
COMPONENT_PROJECT_URL=	https://stellarium.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:3aee154d0de3ed484e3e6fee027cf73e6dd0a677b3ea1af348b225ac02339008
COMPONENT_ARCHIVE_URL=  https://github.com/Stellarium/stellarium/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		image/stellarium
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	GPLv2.0
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

LDFLAGS += -lsocket -lnsl
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CMAKE_OPTIONS += -DENABLE_GPS=OFF
CMAKE_OPTIONS += -DENABLE_SHOWMYSKY=ON
CMAKE_OPTIONS+=  -DQt5_DIR=$(QT5_LIBDIR)/cmake/Qt5/
CMAKE_OPTIONS += -DQt5Charts_DIR=$(QT5_LIBDIR)/cmake/Qt5Charts
CMAKE_OPTIONS += -DQt5Concurrent_DIR=$(QT5_LIBDIR)/cmake/Qt5Concurrent
CMAKE_OPTIONS += -DQt5Core_DIR=$(QT5_LIBDIR)/cmake/Qt5Core
CMAKE_OPTIONS += -DQt5Gui_DIR=$(QT5_LIBDIR)/cmake/Qt5Gui
CMAKE_OPTIONS += -DQt5LinguistTools_DIR=$(QT5_LIBDIR)/cmake/Qt5LinguistTools
CMAKE_OPTIONS += -DQt5MultimediaWidgets_DIR=$(QT5_LIBDIR)/cmake/Qt5MultimediaWidgets
CMAKE_OPTIONS += -DQt5Multimedia_DIR=$(QT5_LIBDIR)/cmake/Qt5Multimedia
CMAKE_OPTIONS += -DQt5Network_DIR=$(QT5_LIBDIR)/cmake/Qt5Network
CMAKE_OPTIONS += -DQt5OpenGL_DIR=$(QT5_LIBDIR)/cmake/Qt5OpenGL
CMAKE_OPTIONS += -DQt5Positioning_DIR=$(QT5_LIBDIR)/cmake/Qt5Positioning
CMAKE_OPTIONS += -DQt5PrintSupport_DIR=$(QT5_LIBDIR)/cmake/Qt5PrintSupport
CMAKE_OPTIONS += -DQt5Script_DIR=$(QT5_LIBDIR)/cmake/Qt5Script
CMAKE_OPTIONS += -DQt5SerialPort_DIR=$(QT5_LIBDIR)/cmake/Qt5SerialPort
CMAKE_OPTIONS += -DQt5Widgets_DIR=$(QT5_LIBDIR)/cmake/Qt5Widgets
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
