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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= liblogging
COMPONENT_VERSION= 1.0.5
COMPONENT_SUMMARY= An easy to use logging library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:310dc1691279b7a669d383581fe4b0babdc7bf75c9b54a24e51e60428624890b
COMPONENT_ARCHIVE_URL= \
  http://download.rsyslog.com/liblogging/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.liblogging.org/
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = BSD
COMPONENT_FMRI = library/liblogging
COMPONENT_CLASSIFICATION = System/Libraries

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-journal=no

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
