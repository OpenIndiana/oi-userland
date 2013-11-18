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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		evolution-exchange
COMPONENT_VERSION=	2.30.3
COMPONENT_PROJECT_URL=	https://developer.gnome.org/evolution-exchange/
COMPONENT_SUMMARY=	Evolution connector for Microsoft Exchange
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:45ab89229bc19adca16b979d9b4d8c2c628c07c8b097529773b0a32243e3dfcd
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = (cd $(@D) ; aclocal -I m4; autoheader; automake -a -f -c --gnu; autoconf; )
gcc_OPT		= -O2

LDFLAGS+=	-L/usr/lib/mps -R/usr/lib/mps
CFLAGS+=	-D__EXTENSIONS__ -I/usr/include/kerberosv5/

CONFIGURE_ENV+=		INTLTOOL_PERL=$(PERL)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--with-sunldap=/usr
CONFIGURE_OPTIONS+=	--with-krb5=/usr
CONFIGURE_OPTIONS+=	--disable-gtk-doc

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
