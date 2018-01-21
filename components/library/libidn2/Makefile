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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libidn2
COMPONENT_VERSION= 2.0.4
COMPONENT_SUMMARY= An implementation of IDNA2008 internationalized domain names
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:644b6b03b285fb0ace02d241d59483d98bc462729d8bb3608d5cad5532f3d2f0
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/libidn/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnu.org/software/libidn/
COMPONENT_FMRI= library/libidn2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = LGPLv3, GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --includedir=/usr/include/idn2

COMPONENT_TEST_TRANSFORMS += '-ne "/^SKIP/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^TOTAL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += system/library
