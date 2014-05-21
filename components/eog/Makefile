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

COMPONENT_NAME=		eog
COMPONENT_VERSION=	2.32.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/EyeOfGnome
COMPONENT_SUMMARY=	GNOME image viewer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:543672fb8e8e300bf2cf4c7eef43b5b1624e2e48e6aa0801a083ae7beb2d7078
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all &&\
					for i in $(@D)/po-sun/*.po; do dos2unix -ascii $$i $$i; done &&\
					cd $(@D) && gnome-doc-common &&\
					libtoolize --force && glib-gettextize --force --copy &&\
					intltoolize --force --copy --automake &&\
					aclocal -I . &&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )
					
CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-scrollkeeper

CONFIGURE_EENV+=	PYTHON=$(PYTHON)

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
