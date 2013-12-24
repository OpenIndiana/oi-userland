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

COMPONENT_NAME= gc

COMPONENT_VERSION= 7.2
COMPONENT_SUMMARY= Boehm-Demers-Weiser garbage collector for C/C++
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)e.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:09315b48a82d600371207691126ad058c04677281ac318d86fa84c98c3c9af4b
COMPONENT_ARCHIVE_URL= \
  https://launchpad.net/libgc/main/$(COMPONENT_VERSION)e/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://launchpad.net/libgc

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =    ($(CLONEY) $(SOURCE_DIR) $(@D)) 

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-threads=posix
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-large-config
CONFIGURE_OPTIONS += --with-libatomic-ops=no

COMPONENT_POST_INSTALL_ACTION+= cd $(BUILD_DIR_$(BITS))/libatomic_ops && env $(COMPONENT_INSTALL_ENV) gmake $(COMPONENT_INSTALL_ARGS) install ;

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
