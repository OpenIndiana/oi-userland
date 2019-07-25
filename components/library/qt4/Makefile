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
# Copyright 2019 Tim Mooney
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		qt
COMPONENT_FMRI=		library/qt4
COMPONENT_VERSION=	4.8.7
COMPONENT_REVISION=	7
COMPONENT_VERSION_MJR=	4.8
COMPONENT_LICENSE=	QT4
COMPONENT_LICENSE_FILE=	qt4.license
COMPONENT_PROJECT_URL=	"http://qt.nokia.com/products/"
COMPONENT_SUMMARY=	Qt cross-platform application and UI framework
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-everywhere-opensource-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e2882295097e47fe089f8ac741a95fef47e0a73a3f3cdf21b56990638f626ea0
COMPONENT_ARCHIVE_URL=	http://download.qt-project.org/official_releases/qt/$(COMPONENT_VERSION_MJR)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PG_BINDIR.$(BITS)):$(MYSQL_BINDIR.$(BITS)):$(GCC_ROOT)/bin:/usr/bin

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

COMPONENT_INSTALL_ENV+=	INSTALL_ROOT=$(PROTO_DIR)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS=	-prefix /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)
CONFIGURE_OPTIONS.32=	-bindir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/bin
CONFIGURE_OPTIONS.32+=	-libdir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/lib
CONFIGURE_OPTIONS.32+=	-plugindir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/plugins
CONFIGURE_OPTIONS.32+=	-importdir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/imports
CONFIGURE_OPTIONS.64=	-bindir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/bin/$(MACH64)
CONFIGURE_OPTIONS.64+=	-libdir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/lib/$(MACH64)
CONFIGURE_OPTIONS.64+=	-plugindir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/plugins/$(MACH64)
CONFIGURE_OPTIONS.64+=	-importdir /usr/lib/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/imports/$(MACH64)
CONFIGURE_OPTIONS.32+=	-platform solaris-g++
CONFIGURE_OPTIONS.64+=	-platform solaris-g++-64
CONFIGURE_OPTIONS+=	-verbose
CONFIGURE_OPTIONS+=	-opensource
CONFIGURE_OPTIONS+=	-confirm-license
CONFIGURE_OPTIONS+=	-xmlpatterns
CONFIGURE_OPTIONS+=	-webkit
CONFIGURE_OPTIONS+=	-no-opengl
CONFIGURE_OPTIONS+=	-nomake examples
CONFIGURE_OPTIONS+=	-nomake demos
CONFIGURE_OPTIONS+=	-nomake translations
CONFIGURE_OPTIONS+=	-nomake docs
CONFIGURE_OPTIONS+=	$(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS+=	-plugin-sql-sqlite
CONFIGURE_OPTIONS+=	-plugin-sql-mysql
CONFIGURE_OPTIONS+= -I$(MYSQL_INCDIR)
CONFIGURE_OPTIONS+= -L$(MYSQL_LIBDIR.$(BITS)) -R$(MYSQL_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	-plugin-sql-psql
CONFIGURE_OPTIONS+= -I$(PG_INCDIR)
CONFIGURE_OPTIONS+= -L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	-system-sqlite
CONFIGURE_OPTIONS+=	-system-libmng
CONFIGURE_OPTIONS+=	-I/usr/include/libmng

COMPONENT_POST_INSTALL_ACTION.32= ( cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/mkspecs ; \
	mv -f qconfig.pri qconfig.pri.32 ; \
	cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR); \
	mv tests tests.32 ; \
	find $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/tests.32 -type f | \
	xargs -n 1 /usr/bin/elfedit -e 'dyn:runpath "$(GCC_ROOT)/lib:/usr/lib/qt/$(COMPONENT_VERSION_MJR)/lib"')
	

COMPONENT_POST_INSTALL_ACTION.64= ( cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/mkspecs ; \
	mv -f qconfig.pri qconfig.pri.64 ; \
	cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR); \
	mv tests tests.64; \
	mv tests.32 tests; \
	mv tests.64 tests/$(MACH64); \
	find $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/tests/$(MACH64) -type f | \
	xargs -n 1 /usr/bin/elfedit -e 'dyn:runpath "$(GCC_ROOT)/lib/$(MACH64):/usr/lib/qt/$(COMPONENT_VERSION_MJR)/lib/$(MACH64)"')

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += database/postgres-94/developer

# Auto-generated dependencies
REQUIRED_PACKAGES += database/mariadb-101/library
REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/libmng
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
