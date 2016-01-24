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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= shairplay
COMPONENT_VERSION= 1.0.0
COMPONENT_FMRI = library/audio/shairplay
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_PROJECT_URL = https://github.com/juhovh/shairplay
COMPONENT_SUMMARY= Free portable AirPlay server implementation similar to ShairPort.
COMPONENT_SRC_VERSION= ce80e005908f41d0e6fde1c4a21e9cb8ee54007b
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:49ac0e0470ec6367f720c7b79a09165138f57b60f5949a2d9c38be5823d13294
COMPONENT_ARCHIVE_URL= \
  https://github.com/juhovh/shairplay/archive/$(COMPONENT_SRC_VERSION).tar.gz
COMPONENT_LICENSE = MIT 

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION= \
    ( cd  $(COMPONENT_DIR)/$(COMPONENT_SRC) && sh autogen.sh )

COMPONENT_POST_INSTALL_ACTION= \
	  ( $(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" \
              -e "s:%VERSION%:$(COMPONENT_VERSION):g" \
              $(SOURCE_DIR)/shairplay.pc > $(BUILD_DIR)/shairplay.pc.$(BITS)  )

CONFIGURE_OPTIONS+= --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
