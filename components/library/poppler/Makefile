#! /usr/bin/sh
#
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
# Copyright 2014 Andrzej Szeszo.  All rights reserved.
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	25.2.0
HUMAN_VERSION=	25.02.0
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base
COMPONENT_PROJECT_URL=	https://poppler.freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:21234cb2a9647d73c752ce4031e65a79d11a511a835f2798284c2497b8701dee
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libpoppler
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_NAME_1=   testfiles
GIT_REPO_1=			https://gitlab.freedesktop.org/poppler/test.git
GIT_COMMIT_ID_1=    ff3133cd


include $(WS_MAKE_RULES)/common.mk

PATH= $(QT5_BINDIR):$(PATH.gnu)
PKG_CONFIG_PATH += $(QT5_PKG_CONFIG_PATH)

CFLAGS += $(XPG6MODE)

# Add qt library run path
LDFLAGS += -Wl,-rpath,$(QT5_LIBDIR)

CMAKE_OPTIONS += -DENABLE_STATIC=FALSE
CMAKE_OPTIONS += -DWITH_Cairo=ON
CMAKE_OPTIONS += -DWITH_GLIB=ON
CMAKE_OPTIONS += -DWITH_GTK=ON
CMAKE_OPTIONS += -DWITH_JPEG=ON
CMAKE_OPTIONS += -DWITH_PNG=ON
CMAKE_OPTIONS += -DWITH_GObjectIntrospection=ON
CMAKE_OPTIONS += -DENABLE_UNSTABLE_API_ABI_HEADERS=ON
CMAKE_OPTIONS += -DENABLE_BOOST=OFF
# We don't have gpgmepp.
CMAKE_OPTIONS += -DENABLE_GPGME=OFF
# jpeg-turbo is not detected without this.
CMAKE_OPTIONS += -DENABLE_QT6=OFF
CMAKE_OPTIONS += -DQt5Core_DIR=$(QT5_LIBDIR)/cmake/Qt5Core
CMAKE_OPTIONS += -DQt5Gui_DIR=$(QT5_LIBDIR)/cmake/Qt5Gui
CMAKE_OPTIONS += -DQt5Xml_DIR=$(QT5_LIBDIR)/cmake/Qt5Xml
CMAKE_OPTIONS += -DQt5Widgets_DIR=$(QT5_LIBDIR)/cmake/Qt5Widgets
CMAKE_OPTIONS += -DQt5Test_DIR=$(QT5_LIBDIR)/cmake/Qt5Test
CMAKE_OPTIONS += -DTESTDATADIR=$(COMPONENT_DIR)/$(COMPONENT_NAME_1)-$(GIT_COMMIT_ID_1)

COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
COMPOMENT_TEST_ENV += PATH="$(PATH)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libpoppler-data
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += web/curl
