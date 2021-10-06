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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gc

COMPONENT_VERSION= 8.0.6
COMPONENT_FMRI= library/gc
COMPONENT_SUMMARY= Boehm-Demers-Weiser garbage collector for C/C++
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_PROJECT_URL= http://www.hboehm.info/gc/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3b4914abc9fa76593596773e4da671d7ed4d5390e3d46fbf2e5f155e121bea11
COMPONENT_ARCHIVE_URL= \
  https://github.com/ivmai/bdwgc/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, MIT

COMPONENT_NAME_1= libatomic_ops
COMPONENT_VERSION_1= 7.6.12
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
  sha256:f0ab566e25fce08b560e1feab6a3db01db4a38e5bc687804334ef3920c549f3e
COMPONENT_ARCHIVE_URL_1= \
  https://github.com/ivmai/libatomic_ops/releases/download/v$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION= (cd $(@D);\
  autoreconf -f -i; $(CP) -rf ../$(COMPONENT_SRC_1) $(COMPONENT_NAME_1))

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-threads=posix
CONFIGURE_OPTIONS += --enable-large-config
CONFIGURE_OPTIONS += --with-libatomic-ops=no

COMPONENT_POST_INSTALL_ACTION= ( cd $(@D)/libatomic_ops && \
  env $(COMPONENT_INSTALL_ENV) gmake $(COMPONENT_INSTALL_ARGS) install )

unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
