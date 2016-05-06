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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnutls
COMPONENT_VERSION= 2.12.23
COMPONENT_SUMMARY= GNU transport layer security library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:dfa67a7e40727eb0913e75f3c44911d5d8cd58d1ead5acfe73dd933fc0d17ed2
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnutls.org/gcrypt/gnutls/v2.12/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnutls.org
COMPONENT_FMRI = library/gnutls
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = GPLv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CPPFLAGS += -I/usr/include/gmp

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-guile=no
CONFIGURE_OPTIONS += --disable-camellia
CONFIGURE_OPTIONS += --without-p11-kit

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
