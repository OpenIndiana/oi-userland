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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ibus
COMPONENT_VERSION= 1.3.9
COMPONENT_SUMMARY= iBus - Intelligent Input Bus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b2784a668666efa8ae04e6f1cff5749917cd18add0a39a1d020ecc9f3df5285d
COMPONENT_ARCHIVE_URL= \
  http://ibus.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://code.google.com/p/ibus/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

gcc_OPT = -O2

PATH = /usr/gnu/bin:/usr/bin

GTK_BIN_VER := $(shell pkg-config --variable=gtk_binary_version gtk+-2.0)

PKG_MACROS += GTK_BIN_VER=$(GTK_BIN_VER)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk2
CONFIGURE_OPTIONS += --enable-xim
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS.32 += --sysconfdir=/etc
CONFIGURE_OPTIONS.64 += --sysconfdir=/etc/$(MACH64)
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib/ibus
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/ibus/$(MACH64)
CONFIGURE_OPTIONS.64 += --with-gtk-im-module-dir=/usr/lib/$(MACH64)/gtk-2.0/$(GTK_BIN_VER)/immodules/

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

$(INSTALL_32):  $(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
