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
BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= libXext
COMPONENT_VERSION= 1.3.4
COMPONENT_FMRI = x11/library/libxext
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_SUMMARY= libXext - X11 protocol common extensions client library
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:59ad6fcce98deaecc14d39a672cf218ca37aba617c9a0f691cac3bcd28edf82b
COMPONENT_ARCHIVE_URL= $(XORG_LIB_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -DSUNSOFT

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

COMPONENT_PREP_ACTION =        ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
					cd $(@D) &&  libtoolize --copy --force &&\
                                        aclocal -I . &&\
                                        automake -c -f -a &&\
                                        autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += LIB_MAN_SUFFIX=3xext
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto
REQUIRED_PACKAGES += x11/header/xextproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxevie
REQUIRED_PACKAGES += x11/library/libxscrnsaver
