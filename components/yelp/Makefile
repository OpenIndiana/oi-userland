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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= yelp
COMPONENT_VERSION= 2.30.2
COMPONENT_SUMMARY= The GNOME Help Browser
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:5f8c35847bdae654e21cbba66865d6b582d9fc80a059ad29081bb87e146bb165
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CXXFLAGS+= -DMOZ_DEFAULT_TOOLKIT=\"cairo-gtk2\"
CXXFLAGS+= -std=gnu++0x

LDFLAGS.32  +=  -L/usr/g++/lib -R/usr/g++/lib
LDFLAGS.64  +=  -L/usr/g++/lib/$(MACH64) -R/usr/g++/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))

PKG_CONFIG_PATH.32   = /usr/g++/lib/pkgconfig:/usr/lib/pkgconfig
PKG_CONFIG_PATH.64   = /usr/g++/lib/$(MACH64)/pkgconfig:/usr/lib/$(MACH64)/pkgconfi

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) &&\
		aclocal -I ./m4 &&\
		autoheader &&\
		automake -a -c -f&&\
		autoconf)

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --with-gecko=firefox
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt

build: $(BUILD_32)

install: $(INSTALL_32)
