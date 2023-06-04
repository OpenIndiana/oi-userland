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
# Copyright 2014 EveryCity Ltd. All rights reserved.
# Copyright 2015 Alexander Pyhalov
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
# Copyright 2022 Daniel Chan
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			qt
COMPONENT_VERSION_MJR=	5.15
COMPONENT_VERSION=		$(COMPONENT_VERSION_MJR).4
COMPONENT_REVISION=		7
COMPONENT_SUMMARY=		Qt cross-platform application and UI framework
COMPONENT_PROJECT_URL=	https://www.qt.io/
COMPONENT_SRC=			$(COMPONENT_NAME)-everywhere-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_NAME)-everywhere-opensource-src-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:615ff68d7af8eef3167de1fd15eac1b150e1fd69d1e2f4239e54447e7797253b
COMPONENT_ARCHIVE_URL=	https://download.qt.io/official_releases/qt/$(COMPONENT_VERSION_MJR)/$(COMPONENT_VERSION)/single/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/qt5
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		QT5
COMPONENT_LICENSE_FILE=	qt5.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PG_BINDIR):$(MYSQL_BINDIR):$(GCC_BINDIR):$(PATH.gnu)

QT_PREFIX= $(QT5_BASEDIR)

QT_ARCHSUBDIR.64= $(MACH64)
QT_PLATFORM.64= solaris-g++-64

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

OPENSSL_VERSION= 1.1
CONFIGURE_ENV += OPENSSL_LIBS='-L$(OPENSSL_LIBDIR) -lssl -lcrypto'
CONFIGURE_ENV += OPENSSL_INCLUDE_PATH=$(OPENSSL_INCDIR)

CONFIGURE_OPTIONS = -prefix $(QT_PREFIX)
#CONFIGURE_OPTIONS += -verbose
CONFIGURE_OPTIONS += -opensource
CONFIGURE_OPTIONS += -confirm-license
CONFIGURE_OPTIONS += -nomake examples
CONFIGURE_OPTIONS += -nomake tests
CONFIGURE_OPTIONS += -c++std c++11
CONFIGURE_OPTIONS += -disable-reduce-exports
CONFIGURE_OPTIONS += -xcb
CONFIGURE_OPTIONS += -xcb-xlib
CONFIGURE_OPTIONS += -bundled-xcb-xinput
CONFIGURE_OPTIONS += -bindir $(QT_PREFIX)/bin/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS += -libdir $(QT_PREFIX)/lib/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS += -plugindir $(QT_PREFIX)/plugins/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS += -importdir $(QT_PREFIX)/imports/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS += -qmldir $(QT_PREFIX)/qml/$(QT_ARCHSUBDIR.$(BITS))
CONFIGURE_OPTIONS += -platform $(QT_PLATFORM.$(BITS))
CONFIGURE_OPTIONS += -plugin-sql-mysql
CONFIGURE_OPTIONS += -plugin-sql-psql
CONFIGURE_OPTIONS += -plugin-sql-sqlite
CONFIGURE_OPTIONS += -system-sqlite
CONFIGURE_OPTIONS += -openssl-linked
CONFIGURE_OPTIONS += OPENSSL_INCDIR=$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += OPENSSL_LIBDIR=$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

COMPONENT_INSTALL_ENV+=	INSTALL_ROOT=$(PROTO_DIR)

# Set runpaths to sql/egl plugins
QT_LIBDIR= $(QT_PREFIX)/lib/$(QT_ARCHSUBDIR.$(BITS))
QT_SQLDIR= $(QT_PREFIX)/plugins/$(QT_ARCHSUBDIR.$(BITS))/sqldrivers
QT_EGLDIR= $(QT_PREFIX)/plugins/$(QT_ARCHSUBDIR.$(BITS))/egldeviceintegrations
QT_XORGDIR= $(QT_PREFIX)/lib/xorg/$(QT_ARCHSUBDIR.$(BITS))

COMPONENT_POST_INSTALL_ACTION= ( \
/usr/bin/elfedit -e 'dyn:runpath "$(GCC_LIBDIR):$(QT_LIBDIR):$(MYSQL_LIBDIR)"' \
	$(PROTO_DIR)$(QT_SQLDIR)/libqsqlmysql.so; \
/usr/bin/elfedit -e 'dyn:runpath "$(GCC_LIBDIR):$(QT_LIBDIR):$(PG_LIBDIR)"' \
	$(PROTO_DIR)$(QT_SQLDIR)/libqsqlpsql.so; \
/usr/bin/elfedit -e 'dyn:runpath "$(GCC_LIBDIR):$(QT_LIBDIR):$(QT_XORGDIR)"' \
	$(PROTO_DIR)$(QT_EGLDIR)/libqeglfs-kms-integration.so; \
/usr/bin/elfedit -e 'dyn:runpath "$(GCC_LIBDIR):$(QT_LIBDIR):$(QT_XORGDIR)"' \
	$(PROTO_DIR)$(QT_EGLDIR)/libqeglfs-kms-egldevice-integration.so; \
/usr/bin/elfedit -e 'dyn:runpath "$(GCC_LIBDIR):$(QT_LIBDIR)"' \
	$(PROTO_DIR)$(QT_LIBDIR)/libQt5EglFsKmsSupport.so.$(COMPONENT_VERSION); \
)

# Build dependencies
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
REQUIRED_PACKAGES += database/freetds
REQUIRED_PACKAGES += system/header/header-drm
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/library/libpthread-stubs
#REQUIRED_PACKAGES += x11/library/libxi

# Auto-generated dependencies
REQUIRED_PACKAGES += $(CLANG_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/speech-dispatcher
REQUIRED_PACKAGES += library/double-conversion
REQUIRED_PACKAGES += library/freetds
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libmng
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/md4c
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/hunspell
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
