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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		qt
COMPONENT_FMRI=		library/qt4
COMPONENT_VERSION=	4.8.7
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
CONFIGURE_OPTIONS+=	-plugin-sql-psql
CONFIGURE_OPTIONS+=	-system-sqlite

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

