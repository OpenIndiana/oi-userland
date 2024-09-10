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

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gc
COMPONENT_VERSION= 8.2.8
COMPONENT_SUMMARY= Boehm-Demers-Weiser garbage collector for C/C++
COMPONENT_PROJECT_URL= https://www.hboehm.info/gc/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7649020621cb26325e1fb5c8742590d92fb48ce5c259b502faf7d9fb5dabb160
COMPONENT_ARCHIVE_URL= https://github.com/ivmai/bdwgc/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/gc
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE= GPLv2, MIT

COMPONENT_NAME_1= libatomic_ops
COMPONENT_VERSION_1= 7.8.2
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:d305207fe207f2b3fb5cb4c019da12b44ce3fcbc593dfd5080d867b1a2419b51
COMPONENT_ARCHIVE_URL_1= https://github.com/ivmai/libatomic_ops/releases/download/v$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

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

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
