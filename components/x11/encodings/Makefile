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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           encodings
COMPONENT_VERSION=        1.0.5
COMPONENT_FMRI=           x11/library/libfontenc/encodings
COMPONENT_CLASSIFICATION= System/Fonts
COMPONENT_SUMMARY=  encodings - data files for libfontenc to map font encodings between character sets
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:bd96e16143a044b19e87f217cf6a3763a70c561d1076aad6f6d862ec41774a31
COMPONENT_ARCHIVE_URL= $(XORG_FONT_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --disable-gzip-small-encodings
CONFIGURE_OPTIONS+= --disable-gzip-large-encodings

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros
REQUIRED_PACKAGES += x11/mkfontscale
