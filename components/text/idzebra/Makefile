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

COMPONENT_NAME= idzebra
COMPONENT_VERSION= 2.1.2
COMPONENT_SUMMARY= idzebra - text indexing and retrieval engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:cf6eaa7354ce85df7df5604c9530301052a7e1ff6d10cbc930b7fd53a8e701c4
COMPONENT_ARCHIVE_URL= \
  http://ftp.indexdata.dk/pub/zebra/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.indexdata.dk/zebra
COMPONENT_FMRI= text/idzebra
COMPONENT_CLASSIFICATION = System/Text Tools
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = LICENSE.zebra

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# For tests to pass we should be very careful about files
COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

# Without this tests fail
ENV=/usr/bin/env -i

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/yaz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
