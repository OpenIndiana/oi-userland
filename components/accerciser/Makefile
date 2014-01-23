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

COMPONENT_NAME=		accerciser
COMPONENT_VERSION=	1.10.1
IPS_COMPONENT_VERSION=  2.30.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/action/show/Apps/Accerciser
COMPONENT_SUMMARY=	An interactive Python accessibility explorer for the GNOME desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7d6238b23a68ffff47634e3d5d503801d75db9be4251d831e12b927a47d0bc42
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.10/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--sysconfdir=/etc

COMPONENT_CONFIGURE_ENV += PYTHON=$(PYTHON)
COMPONENT_CONFIGURE_ENV += PERL=$(PERL)

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

COMPONENT_POST_INSTALL_ACTION = ( $(GSED) -i -e 's:\#!/usr/bin/env python:\#!/usr/bin/python2.6:' \
        $(PROTO_DIR)/usr/bin/accerciser )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
