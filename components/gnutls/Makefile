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

COMPONENT_NAME= gnutls

COMPONENT_VERSION= 2.8.6
COMPONENT_SUMMARY= GNU transport layer security library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d6f846a7064af3ee2c9aebd65dcee76953b767170cbcd719e990ed6b9688a356
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnu.org/gnu/gnutls/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnutls.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2
PATH = /usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-guile=no
CONFIGURE_OPTIONS += --disable-camellia

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
