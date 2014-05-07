#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-vfs

COMPONENT_VERSION= 2.24.4
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME virtual file system framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:62de64b5b804eb04104ff98fcd6a8b7276d510a49fbd9c0feb568f8996444faa
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all &&\
					cd $(@D) && glib-gettextize --force --copy &&\
					libtoolize --automake --copy --force && \
					glib-gettextize --force &&\
					intltoolize --force --copy --automake &&\
					aclocal -I . &&\
					gtkdocize &&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )

CONFIGURE_SCRIPT=       $(@D)/configure

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-fam
CONFIGURE_OPTIONS += --enable-samba
CONFIGURE_OPTIONS += --with-samba-includes=/usr/include/samba
CONFIGURE_OPTIONS += --with-samba-libs=/usr/lib/samba
CONFIGURE_OPTIONS.64 += --disable-avahi

CONFIGURE_ENV+= PERL=$(PERL)

COMPONENT_INSTALL_ENV+=  GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
