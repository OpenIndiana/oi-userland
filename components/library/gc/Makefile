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

COMPONENT_VERSION= 8.2.2
COMPONENT_FMRI= library/gc
COMPONENT_SUMMARY= Boehm-Demers-Weiser garbage collector for C/C++
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_PROJECT_URL= http://www.hboehm.info/gc/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:f30107bcb062e0920a790ffffa56d9512348546859364c23a14be264b38836a0
COMPONENT_ARCHIVE_URL= \
  https://github.com/ivmai/bdwgc/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, MIT

COMPONENT_NAME_1= libatomic_ops
COMPONENT_VERSION_1= 7.6.14
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
  sha256:390f244d424714735b7050d056567615b3b8f29008a663c262fb548f1802d292
COMPONENT_ARCHIVE_URL_1= \
  https://github.com/ivmai/libatomic_ops/releases/download/v$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

USE_DEFAULT_TEST_TRANSFORMS = yes
include $(WS_MAKE_RULES)/common.mk

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
