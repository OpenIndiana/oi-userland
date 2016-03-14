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
# Copyright 2016 Till Wegmueller
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		qt
COMPONENT_FMRI=		library/qt5
COMPONENT_VERSION=	5.5.1
COMPONENT_VERSION_MJR=	5.5
COMPONENT_LICENSE=	LGPL
COMPONENT_LICENSE_FILE=	qt5.license
COMPONENT_PROJECT_URL=	"http://qt.io"
COMPONENT_SUMMARY=	Qt cross-platform application and UI framework
COMPONENT_CLASSIFICATION=	Desktop (KDE)/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-everywhere-opensource-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c7fad41a009af1996b62ec494e438aedcb072b3234b2ad3eeea6e6b1f64be3b3
COMPONENT_ARCHIVE_URL=	http://download.qt.io/official_releases/qt/$(COMPONENT_VERSION_MJR)/$(COMPONENT_VERSION)/single/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

MYSQL_BINDIR.32=/usr/mariadb/5.5/bin
MYSQL_BINDIR.64=/usr/mariadb/5.5/bin/$(MACH64)

PATH=$(PG_BINDIR.$(BITS)):$(MYSQL_BINDIR.$(BITS)):/usr/bin

MYSQL_LIBDIR.32=/usr/mariadb/5.5/lib
MYSQL_LIBDIR.64=/usr/mariadb/5.5/lib/$(MACH64)
LDFLAGS +=   -L$(MYSQL_LIBDIR.$(BITS)) -R$(MYSQL_LIBDIR.$(BITS)) 
LDFLAGS +=   -L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS)) 

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

COMPONENT_INSTALL_ENV+=	INSTALL_ROOT=$(PROTO_DIR)

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
CONFIGURE_OPTIONS+=	-no-opengl
CONFIGURE_OPTIONS+=	-nomake examples
CONFIGURE_OPTIONS+=	$(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS+=	-plugin-sql-sqlite
CONFIGURE_OPTIONS+=	-plugin-sql-mysql
CONFIGURE_OPTIONS+=	-plugin-sql-psql
CONFIGURE_OPTIONS+=	-system-sqlite
CONFIGURE_OPTIONS+=     -accessibility
CONFIGURE_OPTIONS+=     -dbus-linked
CONFIGURE_OPTIONS+=     -fontconfig
CONFIGURE_OPTIONS+=     -force-pkg-config
CONFIGURE_OPTIONS+=     -icu
CONFIGURE_OPTIONS+=     -openssl-linked
CONFIGURE_OPTIONS+=     -no-pch
CONFIGURE_OPTIONS+=     -no-sql-db2
CONFIGURE_OPTIONS+=     -no-sql-ibase
CONFIGURE_OPTIONS+=     -no-sql-mysql
CONFIGURE_OPTIONS+=     -no-sql-oci
CONFIGURE_OPTIONS+=     -no-sql-odbc
CONFIGURE_OPTIONS+=     -no-sql-psql
CONFIGURE_OPTIONS+=     -no-sql-sqlite
CONFIGURE_OPTIONS+=     -no-sql-sqlite2
CONFIGURE_OPTIONS+=     -no-sql-tds
CONFIGURE_OPTIONS+=     -no-strip
CONFIGURE_OPTIONS+=     -system-harfbuzz
CONFIGURE_OPTIONS+=     -system-libjpeg
CONFIGURE_OPTIONS+=     -system-libpng
#TODO Find Out why System pcre is not usable
CONFIGURE_OPTIONS+=     -qt-pcre
CONFIGURE_OPTIONS+=     -system-sqlite
CONFIGURE_OPTIONS+=     -system-zlib
#TODO Find out how to use system xcb
CONFIGURE_OPTIONS+=     -qt-xcb

COMPONENT_POST_INSTALL_ACTION.32= ( cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/mkspecs ; \
	mv qconfig.pri qconfig.pri.32 ; \
	cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR); \
	mv tests tests.32 ; \
	find $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/tests.32 -type f | \
		xargs -n 1 /usr/bin/elfedit -e 'dyn:runpath "/usr/lib:/usr/lib/qt/$(COMPONENT_VERSION_MJR)/lib"')
	

COMPONENT_POST_INSTALL_ACTION.64= ( cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/mkspecs ; \
	mv qconfig.pri qconfig.pri.64 ; ln -s qconfig.pri.32 qconfig.pri ; \
	cd $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR); \
	mv tests tests.64; \
	mv tests.32 tests; \
	mv tests.64 tests/$(MACH64); \
	find $(PROTO_DIR)/usr/lib/qt/$(COMPONENT_VERSION_MJR)/tests/$(MACH64) -type f | \
		xargs -n 1 /usr/bin/elfedit -e 'dyn:runpath "/usr/lib/64:/usr/lib/qt/$(COMPONENT_VERSION_MJR)/lib/$(MACH64)"')

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION.$(BITS))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

