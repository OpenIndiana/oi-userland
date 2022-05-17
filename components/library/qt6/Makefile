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

include ../../../make-rules/shared-macros.mk

COMPILER=gcc
COMPONENT_NAME=				qt
COMPONENT_VERSION_MJR=		$(QT6_VERSION)
COMPONENT_VERSION=			$(COMPONENT_VERSION_MJR).4
COMPONENT_REVISION=     	1
COMPONENT_FMRI=				library/qt6
COMPONENT_PROJECT_URL=		https://www.qt.io/
COMPONENT_SUMMARY=			Qt cross-platform application and UI framework
COMPONENT_CLASSIFICATION= 	Desktop (GNOME)/Libraries
COMPONENT_SRC=				$(COMPONENT_NAME)-everywhere-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=		sha256:cfe41905b6bde3712c65b102ea3d46fc80a44c9d1487669f14e4a6ee82ebb8fd
COMPONENT_ARCHIVE_URL=		https://download.qt.io/official_releases/qt/$(COMPONENT_VERSION_MJR)/$(COMPONENT_VERSION)/single/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=			FDLv1.3, GPLv2, GPLv3, LGPLv2.1, LGPLv3
COMPONENT_LICENSE_FILE=		qt6.license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk
PATH=$(PG_BINDIR.$(BITS)):$(MYSQL_BINDIR.$(BITS)):$(GCC_ROOT)/bin:$(PATH.gnu)

QT_PREFIX=$(USRLIBDIR)/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)

#QT_ARCHSUBDIR.32=
QT_ARCHSUBDIR.64=$(MACH64)
#QT_PLATFORM.32= solaris-g++
QT_PLATFORM.64= solaris-g++-64

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

GCC_VERSION 	= 10
MYSQL_VERSION	= 10.3
PG_VERSION		= 14
OPENSSL_VERSION	= 1.1
Clang_VERSION	= 13.0


LDFLAGS += -Wl,-rpath,$(QT_PREFIX)/lib/$(QT_ARCHSUBDIR.$(BITS)):/usr/clang/$(Clang_VERSION)/lib:$(MYSQL_LIBDIR):$(PG_LIBDIR)
#CONFIGURE_ENV+= MySQL_LIBRARY=/usr/mysql/lib/amd64
#CONFIGURE_ENV+= MySQL_INCLUDE_DIR=/usr/mysql/include
CONFIGURE_OPTIONS = -prefix $(QT_PREFIX)
#CONFIGURE_OPTIONS+= -verbose
CONFIGURE_OPTIONS+= -opensource
CONFIGURE_OPTIONS+= -confirm-license
CONFIGURE_OPTIONS+= -nomake examples
CONFIGURE_OPTIONS+= -nomake tests
CONFIGURE_OPTIONS+= -c++std c++11
CONFIGURE_OPTIONS+= -disable-reduce-exports
CONFIGURE_OPTIONS+= -xcb
CONFIGURE_OPTIONS+= -xcb-xlib
CONFIGURE_OPTIONS+= -bundled-xcb-xinput
CONFIGURE_OPTIONS+= -openssl-linked
CONFIGURE_OPTIONS+= -bindir $(QT_PREFIX)/bin/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS+= -libexecdir $(QT_PREFIX)/bin/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS+= -libdir $(QT_PREFIX)/lib/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS+= -plugindir $(QT_PREFIX)/plugins/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS+= -qmldir $(QT_PREFIX)/qml/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS+= -platform $(QT_PLATFORM.$(BITS))
CONFIGURE_OPTIONS+= -plugin-sql-mysql
CONFIGURE_OPTIONS+= -plugin-sql-psql
CONFIGURE_OPTIONS+= -plugin-sql-sqlite
CONFIGURE_OPTIONS+= -plugin-system-sqlite
CONFIGURE_OPTIONS+= -cmake-generator 'Unix Makefiles'
CONFIGURE_OPTIONS+= -no-gstreamer
CONFIGURE_OPTIONS+= -no-pch
#CONFIGURE_OPTIONS.32+= CMAKE_PREFIX_PATH=$(BUILD_DIR)/i86/qtbase/lib/cmake
CONFIGURE_OPTIONS.64+= CMAKE_PREFIX_PATH="$(BUILD_DIR)/amd64/qtbase/lib/amd64/cmake;/usr/clang/$(Clang_VERSION)"
CONFIGURE_OPTIONS.64+= MySQL_LIBRARY=$(MYSQL_LIBDIR)/libmysqlclient.so
CONFIGURE_OPTIONS.64+= MySQL_INCLUDE_DIR=$(MYSQL_INCDIR)
CONFIGURE_OPTIONS.64+= PostgreSQL_LIBRARY=$(PG_LIBDIR)/libpq.so
CONFIGURE_OPTIONS.64+= PostgreSQL_INCLUDE_DIR=$(PG_INCDIR)
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(BITS))
#COMPONENT_POST_CONFIGURE_ACTION.32= mkdir -p $(BUILD_DIR)/i86/qtbase/translations
COMPONENT_POST_CONFIGURE_ACTION.64= mkdir -p $(BUILD_DIR)/amd64/qtbase/translations

include $(WS_MAKE_RULES)/cmake.mk

$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

COMPONENT_INSTALL_ENV+=	INSTALL_ROOT=$(PROTO_DIR)

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += database/freetds
REQUIRED_PACKAGES += database/mariadb-101/client
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/library/libpthread-stubs
#REQUIRED_PACKAGES += x11/library/libxi

# Manually added dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/mariadb-103/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/double-conversion
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libmng
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/md4c
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/clang-13
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += text/hunspell
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxkbcommon
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += x11/library/xcb-util-image
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-renderutil
REQUIRED_PACKAGES += x11/library/xcb-util-wm
