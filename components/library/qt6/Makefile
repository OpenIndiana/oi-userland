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

BUILD_STYLE = cmake
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				qt
COMPONENT_VERSION=		6.11.2
QTV=				$(basename $(COMPONENT_VERSION))
QT6_VERSION=			$(QTV)
COMPONENT_SUMMARY=		Qt cross-platform application and UI framework
COMPONENT_PROJECT_URL=		https://www.qt.io/
COMPONENT_SRC=			$(COMPONENT_NAME)-everywhere-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:6dcfbca271d76a6502741a2c0dc6fc98ef7dd0b7b4cfd0abcebb285a86a26f33
COMPONENT_ARCHIVE_URL=		https://download.qt.io/official_releases/qt/$(QTV)/$(COMPONENT_VERSION)/single/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/qt6
COMPONENT_CLASSIFICATION= 	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		FDLv1.3, GPLv2, GPLv3, LGPLv2.1, LGPLv3
COMPONENT_LICENSE_FILE=		qt6.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

QT_PREFIX= $(QT6_BASEDIR)

QT_ARCHSUBDIR= $(MACH64)
QT_PLATFORM= solaris-g++-64
PKG_VARS += QTV

CFLAGS += -Wno-unused-variable
LDFLAGS += -Wl,-rpath,$(QT6_LIBDIR):$(USRLIBDIR)/xorg/$(MACH64)/:$(CLANG_LIBDIR):$(MYSQL_LIBDIR):$(PG_LIBDIR):$(JPEG_LIBDIR)

COMPONENT_CONFIGURE_ACTION = \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(CONFIGURE_ENV) \
	$(CONFIG_SHELL) \
	$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS)

CONFIGURE_SCRIPT = $(SOURCE_DIR)/configure

CONFIGURE_OPTIONS = -prefix $(QT_PREFIX)
CONFIGURE_OPTIONS += -opensource
CONFIGURE_OPTIONS += -confirm-license
CONFIGURE_OPTIONS += -nomake examples
CONFIGURE_OPTIONS += -nomake tests
CONFIGURE_OPTIONS += -c++std c++17
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
CONFIGURE_OPTIONS += -sql-mysql
CONFIGURE_OPTIONS += -sql-psql
CONFIGURE_OPTIONS += -sql-sqlite
CONFIGURE_OPTIONS += -plugin-system-sqlite
CONFIGURE_OPTIONS += -no-pch
CONFIGURE_OPTIONS += -no-gstreamer
CONFIGURE_OPTIONS += -skip qtgrpc
CONFIGURE_OPTIONS += CMAKE_PREFIX_PATH="$(BUILD_DIR)/$(MACH64)/qtbase/lib/$(MACH64)/cmake"
CONFIGURE_OPTIONS += MySQL_LIBRARY=$(MYSQL_LIBDIR)/libmysqlclient.so
CONFIGURE_OPTIONS += MySQL_INCLUDE_DIR=$(MYSQL_INCDIR)
CONFIGURE_OPTIONS += PostgreSQL_LIBRARY=$(PG_LIBDIR)/libpq.so
CONFIGURE_OPTIONS += PostgreSQL_INCLUDE_DIR=$(PG_INCDIR)
# needed by 3rdparty/open62541
CONFIGURE_OPTIONS += -D__EXTENSIONS__

COMPONENT_POST_CONFIGURE_ACTION= mkdir -p $(BUILD_DIR)/$(MACH64)/qtbase/translations ;
COMPONENT_POST_CONFIGURE_ACTION += $(GSED) -i 's;LINK_LIBRARIES =;LINK_LIBRARIES = -lgcc ;' $(@D)/build.ninja ;

COMPONENT_INSTALL_ENV += DESTDIR=$(PROTO_DIR)

# We do not want to distribute compiled Python files
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTO_DIR)/$(QT6_BINDIR)/__pycache__/ ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTO_DIR)/$(QT6_BASEDIR)/mkspecs/features/uikit/__pycache__/ ;

# Create symlinks with the -qt6 suffix in /usr/bin
COMPONENT_POST_INSTALL_ACTION += \
	for f in assistant designer lconvert linguist lrelease lupdate moc \
	    pixeltool qdbus qdbuscpp2xml qdbusviewer qdbusviewer qdbusxml2cpp \
	    qhelpgenerator qmake qmlplugindump rcc uic ; do \
		$(call create-symlinks,$(QT6_BINDIR)/$$f,$(USRBINDIR),-qt6) ; \
	done ;

PYTHON_SCRIPTS += $(QT6_BASEDIR)/mkspecs/features/uikit/devices.py
PYTHON_SCRIPTS += $(QT6_BINDIR)/sanitizer-testrunner.py
PYTHON_SCRIPTS += $(QT6_BINDIR)/qt-testrunner.py
PYTHON_SCRIPTS += $(QT6_BINDIR)/qt-android-runner.py

PKG_HARDLINKS += $(QT6_BINDIR:/%=%)/androiddeployqt
PKG_HARDLINKS += $(QT6_BINDIR:/%=%)/qmake
PKG_HARDLINKS += $(QT6_BINDIR:/%=%)/qtdiag
PKG_HARDLINKS += $(QT6_BINDIR:/%=%)/qtpaths

# Replace qt version number by QTV
QTV_RE = $(subst .,\.,$(QTV))
GENERATE_EXTRA_SED += -e 's/$(QTV_RE)/$$(QTV)/'

# Build dependencies
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += database/freetds
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/library/libpthread-stubs

# Auto-generated dependencies
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
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/pulseaudio
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
REQUIRED_PACKAGES.python += runtime/python
