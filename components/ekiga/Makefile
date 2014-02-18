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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ekiga
COMPONENT_VERSION=	3.2.7
COMPONENT_PROJECT_URL=	http://www.ekiga.org
COMPONENT_SUMMARY=	A GNOME based H.323/SIP video conferencing application
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f25a1309b68eafe69f0d7aed461bc9a8196939060543d09bd2f19e0bb1e3fd8f
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/ekiga/3.2/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all )
					
CFLAGS+=	-DSOLARIS -D__EXTENSIONS__
CXXFLAGS+=	-DSOLARIS -D__EXTENSIONS__ -I/usr/g++/include 

PKG_CONFIG_PATH.32   = /usr/g++/lib/pkgconfig:/usr/lib/pkgconfig

LDFLAGS.32  +=  -L/usr/g++/lib -R/usr/g++/lib
LDFLAGS += $(LDFLAGS.$(BITS))

CONFIGURE_SCRIPT=       $(@D)/configure

gcc_OPT		= -O2

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-ldap
CONFIGURE_OPTIONS+=	--disable-notify
CONFIGURE_OPTIONS+=	--enable-xv

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
