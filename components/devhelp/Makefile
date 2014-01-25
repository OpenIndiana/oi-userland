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

COMPONENT_NAME= devhelp
COMPONENT_VERSION= 0.21
COMPONENT_SUMMARY= API documentation browser for GNOME 2
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:f2f76e1804afcad248216d494ebc331b670851ccf701dacd295baf87f1273c20
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/devhelp/0.21/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Apps/Devhelp

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk


CXXFLAGS+= -DMOZ_DEFAULT_TOOLKIT=\"cairo-gtk2\" 
CXXFLAGS+= -std=gnu++0x
# We get Werror without building in separate directory, and it's not good
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) && autoconf) 

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --disable-gtk-doc
CONFIGURE_OPTIONS+= --with-compile-warnings=yes
CONFIGURE_OPTIONS+= --with-gecko=firefox
CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt

build: $(BUILD_32)

install: $(INSTALL_32)
