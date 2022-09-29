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
# Copyright 2022 Niklas Poslovski
#
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libupnp
COMPONENT_VERSION= 1.14.13
COMPONENT_SUMMARY= Portable C library for UPnP
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:025d7aee1ac5ca8f0bd99cb58b83fcfca0efab0c5c9c1d48f72667fe40788a4e
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/pupnp/files/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pupnp.sourceforge.io/
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = system/library/libupnp
COMPONENT_LICENSE = BSD

include $(WS_MAKE_RULES)/common.mk

unexport SHELLOPTS

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

LDLFAGS += -lsocket -lnsl

CPPFLAGS += -DSOLARIS -D_POSIX_PTHREAD_SEMANTICS
CFLAGS.32 =  -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
