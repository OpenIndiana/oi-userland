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
COMPONENT_VERSION= 1.14.17
COMPONENT_SUMMARY= Portable C library for UPnP
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:9b877242eba0428c7f949af4d6e7b7b908ce5ebc67cc13475ee6eb0d9bcb6ffb
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/pupnp/files/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://pupnp.sourceforge.io/
COMPONENT_FMRI= system/library/libupnp
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

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

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
