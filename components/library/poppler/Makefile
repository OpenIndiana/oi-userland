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
COMPONENT_VERSION=	26.2.0
COMPONENT_REVISION=	1
HUMAN_VERSION=		26.02.0
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base
COMPONENT_PROJECT_URL=	https://poppler.freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:dded8621f7b2f695c91063aab1558691c8418374cd583501e89ed39487e7ab77
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libpoppler
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_NAME_1=   testfiles
GIT_REPO_1=			https://gitlab.freedesktop.org/poppler/test.git
#GIT_COMMIT_ID_1=    b85e4d1ce75636b3e727555a9d31da34ad771c1c
GIT_COMMIT_ID_1=    b85e4d1c

include $(WS_MAKE_RULES)/common.mk

PATH= $(QT6_BINDIR):$(PATH.gnu)
PKG_CONFIG_PATH += $(QT6_PKG_CONFIG_PATH)

CFLAGS += $(XPG6MODE)

# Add qt library run path
LDFLAGS += -Wl,-rpath,$(QT6_LIBDIR)

CMAKE_OPTIONS += -DENABLE_STATIC=FALSE
CMAKE_OPTIONS += -DWITH_Cairo=ON
CMAKE_OPTIONS += -DWITH_GLIB=ON
CMAKE_OPTIONS += -DWITH_GTK=ON
CMAKE_OPTIONS += -DWITH_NSS3=ON
CMAKE_OPTIONS += -DWITH_JPEG=ON
CMAKE_OPTIONS += -DWITH_PNG=ON
CMAKE_OPTIONS += -DWITH_GObjectIntrospection=ON
CMAKE_OPTIONS += -DENABLE_UNSTABLE_API_ABI_HEADERS=ON
CMAKE_OPTIONS += -DENABLE_BOOST=OFF
# We don't have gpgmepp.
CMAKE_OPTIONS += -DENABLE_GPGME=OFF
CMAKE_OPTIONS += -DENABLE_QT5=OFF
CMAKE_OPTIONS += -DENABLE_QT6=ON
CMAKE_OPTIONS += -DQt6Core_DIR=$(QT6_LIBDIR)/cmake/Qt6Core
CMAKE_OPTIONS += -DQt6Gui_DIR=$(QT6_LIBDIR)/cmake/Qt6Gui
CMAKE_OPTIONS += -DQt6Xml_DIR=$(QT6_LIBDIR)/cmake/Qt6Xml
CMAKE_OPTIONS += -DQt6Widgets_DIR=$(QT6_LIBDIR)/cmake/Qt6Widgets
CMAKE_OPTIONS += -DQt6Test_DIR=$(QT6_LIBDIR)/cmake/Qt6Test
CMAKE_OPTIONS += -DTESTDATADIR=$(COMPONENT_DIR)/$(COMPONENT_NAME_1)-$(GIT_COMMIT_ID_1)

COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8
COMPONENT_TEST_ENV += PATH="$(PATH)"

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
REQUIRED_PACKAGES += library/qt6
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += web/curl
