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
# Copyright 2023 Niklas Poslovski
#
include ../../../make-rules/shared-macros.mk

QT6_VERSION=				6.6
COMPONENT_NAME=				qt
COMPONENT_VERSION_MJR=		$(QT6_VERSION)
COMPONENT_VERSION=			$(COMPONENT_VERSION_MJR).3
COMPONENT_SUMMARY=			Qt cross-platform application and UI framework
COMPONENT_PROJECT_URL=		https://www.qt.io/
COMPONENT_SRC=				$(COMPONENT_NAME)-everywhere-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=		sha256:69d0348fef415da98aa890a34651e9cfb232f1bffcee289b7b4e21386bf36104
COMPONENT_ARCHIVE_URL=		https://download.qt.io/official_releases/qt/$(COMPONENT_VERSION_MJR)/$(COMPONENT_VERSION)/single/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=				library/qt6
COMPONENT_CLASSIFICATION= 	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=			FDLv1.3, GPLv2, GPLv3, LGPLv2.1, LGPLv3
COMPONENT_LICENSE_FILE=		qt6.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PG_BINDIR):$(MYSQL_BINDIR):$(GCC_BINDIR):$(PATH.gnu)

QT_PREFIX= $(QT6_BASEDIR)

QT_ARCHSUBDIR= $(MACH64)
QT_PLATFORM= solaris-g++-64

LDFLAGS += -Wl,-rpath,$(QT6_LIBDIR):$(USRLIBDIR)/xorg/$(MACH64)/:$(CLANG_LIBDIR):$(MYSQL_LIBDIR):$(PG_LIBDIR):$(JPEG_LIBDIR)

CONFIGURE_OPTIONS = -prefix $(QT_PREFIX)
CONFIGURE_OPTIONS += -opensource
CONFIGURE_OPTIONS += -confirm-license
CONFIGURE_OPTIONS += -nomake examples
CONFIGURE_OPTIONS += -nomake tests
CONFIGURE_OPTIONS += -c++std c++11
CONFIGURE_OPTIONS += -disable-reduce-exports
CONFIGURE_OPTIONS += -xcb
CONFIGURE_OPTIONS += -xcb-xlib
CONFIGURE_OPTIONS += -bundled-xcb-xinput
CONFIGURE_OPTIONS += -openssl-linked
CONFIGURE_OPTIONS += -bindir $(QT_PREFIX)/bin/$(QT_ARCHSUBDIR)
CONFIGURE_OPTIONS += -libexecdir $(QT_PREFIX)/bin/$(QT_ARCHSUBDIR)
CONFIGURE_OPTIONS += -libdir $(QT_PREFIX)/lib/$(QT_ARCHSUBDIR)
CONFIGURE_OPTIONS += -plugindir $(QT_PREFIX)/plugins/$(QT_ARCHSUBDIR)
CONFIGURE_OPTIONS += -qmldir $(QT_PREFIX)/qml/$(QT_ARCHSUBDIR)
CONFIGURE_OPTIONS += -platform $(QT_PLATFORM)
CONFIGURE_OPTIONS += -plugin-sql-mysql
CONFIGURE_OPTIONS += -plugin-sql-psql
CONFIGURE_OPTIONS += -plugin-sql-sqlite
CONFIGURE_OPTIONS += -plugin-system-sqlite
CONFIGURE_OPTIONS += -no-pch
CONFIGURE_OPTIONS += -skip qtgrpc
CONFIGURE_OPTIONS += CMAKE_PREFIX_PATH="$(BUILD_DIR)/amd64/qtbase/lib/amd64/cmake"
CONFIGURE_OPTIONS += MySQL_LIBRARY=$(MYSQL_LIBDIR)/libmysqlclient.so
CONFIGURE_OPTIONS += MySQL_INCLUDE_DIR=$(MYSQL_INCDIR)
CONFIGURE_OPTIONS += PostgreSQL_LIBRARY=$(PG_LIBDIR)/libpq.so
CONFIGURE_OPTIONS += PostgreSQL_INCLUDE_DIR=$(PG_INCDIR)

COMPONENT_POST_CONFIGURE_ACTION= mkdir -p $(BUILD_DIR)/amd64/qtbase/translations ;
COMPONENT_POST_CONFIGURE_ACTION += $(GSED) -i 's;LINK_LIBRARIES =;LINK_LIBRARIES = -lgcc ;' $(@D)/build.ninja ;

COMPONENT_INSTALL_ENV += DESTDIR=$(PROTO_DIR)

include $(WS_MAKE_RULES)/cmake.mk

$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

# build the configured source
$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		cmake --build . --parallel)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
		cmake --install .)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# Build dependencies
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += database/freetds
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/library/libpthread-stubs

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(CLANG_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libjpeg-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/speech-dispatcher
REQUIRED_PACKAGES += library/double-conversion
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libmng
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
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
REQUIRED_PACKAGES += x11/library/xcb-util-cursor
REQUIRED_PACKAGES += x11/library/xcb-util-image
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
REQUIRED_PACKAGES += x11/library/xcb-util-renderutil
REQUIRED_PACKAGES += x11/library/xcb-util-wm
