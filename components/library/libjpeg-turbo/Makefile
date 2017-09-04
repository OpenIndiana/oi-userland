#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libjpeg-turbo
COMPONENT_VERSION= 1.5.2
COMPONENT_FMRI= image/library/libjpeg-turbo
COMPONENT_PROJECT_URL= http://www.libjpeg-turbo.org/
COMPONENT_SUMMARY= libjpeg -JPEG Turbo libraries
COMPONENT_SRC= libjpeg-turbo-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:9098943b270388727ae61de82adec73cf9f0dbb240b3bc8b172595ebf405b528
COMPONENT_ARCHIVE_URL= http://sourceforge.net/projects/libjpeg-turbo/files/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz/download
COMPONENT_LICENSE= IJG,BSD,zlib
COMPONENT_CLASSIFICATION= System/Multimedia Libraries


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_DEFAULT_DIRS=no

# Warnings are normal: libtool:   error: ignoring unknown tag NASM

CONFIGURE_OPTIONS.JPEG6= 
CONFIGURE_OPTIONS.JPEG7= --with-jpeg7
CONFIGURE_OPTIONS.JPEG8= --with-jpeg8

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
# Allow for build with different API compliance
CONFIGURE_OPTIONS+=	$(CONFIGURE_OPTIONS.JPEG$(JPEG_API_VERSION))
CONFIGURE_OPTIONS+= --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS+= --includedir=$(CONFIGURE_INCLUDEDIR)/libjpeg$(JPEG_API_VERSION)-turbo
CONFIGURE_OPTIONS.32+= --bindir=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/bin
CONFIGURE_OPTIONS.32+= --libdir=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/lib
# Autoconf infers the build type incorrectly from the host triplet
CONFIGURE_OPTIONS.64+= --build=x86_64-solaris2.11
CONFIGURE_OPTIONS.64+= --bindir=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/bin/$(MACH64)
CONFIGURE_OPTIONS.64+= --libdir=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo/lib/$(MACH64)

# Define rules for each API build
BUILD_DIR_32_6 =		$(BUILD_DIR)/$(MACH32)/6
BUILD_DIR_32_7 =		$(BUILD_DIR)/$(MACH32)/7
BUILD_DIR_32_8 =		$(BUILD_DIR)/$(MACH32)/8
BUILD_DIR_64_6 =		$(BUILD_DIR)/$(MACH64)/6
BUILD_DIR_64_7 =		$(BUILD_DIR)/$(MACH64)/7
BUILD_DIR_64_8 =		$(BUILD_DIR)/$(MACH64)/8
$(BUILD_DIR_32)/%/.configured:	BITS=32
$(BUILD_DIR_64)/%/.configured:	BITS=64
$(BUILD_DIR)/%/6/.configured:	JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.configured:	JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.configured:	JPEG_API_VERSION=8

BUILD_32 =		$(BUILD_DIR_32_6)/.built $(BUILD_DIR_32_7)/.built $(BUILD_DIR_32_8)/.built
BUILD_64 =		$(BUILD_DIR_64_6)/.built $(BUILD_DIR_64_7)/.built $(BUILD_DIR_64_8)/.built
BUILD_32_and_64 =	$(BUILD_32) $(BUILD_64)
$(BUILD_DIR_32)/%/.built:	BITS=32
$(BUILD_DIR_64)/%/.built:	BITS=64
$(BUILD_DIR)/%/6/.built:	JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.built:	JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.built:	JPEG_API_VERSION=8

INSTALL_32 =		$(BUILD_DIR_32_6)/.installed $(BUILD_DIR_32_7)/.installed $(BUILD_DIR_32_8)/.installed
INSTALL_64 =		$(BUILD_DIR_64_6)/.installed $(BUILD_DIR_64_7)/.installed $(BUILD_DIR_64_8)/.installed
INSTALL_32_and_64 =	$(INSTALL_32) $(INSTALL_64)
$(BUILD_DIR_32)/%/.installed: BITS=32
$(BUILD_DIR_64)/%/.installed: BITS=64
$(BUILD_DIR)/%/6/.installed: JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.installed: JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.installed: JPEG_API_VERSION=8

TEST_32 =		$(BUILD_DIR_32_6)/.tested $(BUILD_DIR_32_7)/.tested $(BUILD_DIR_32_8)/.tested
TEST_64 =		$(BUILD_DIR_64_6)/.tested $(BUILD_DIR_64_7)/.tested $(BUILD_DIR_64_8)/.tested
TEST_32_and_64 =	$(TEST_32) $(TEST_64)
$(BUILD_DIR_32)/%/.tested:		BITS=32
$(BUILD_DIR_64)/%/.tested:		BITS=64
$(BUILD_DIR)/%/6/.tested: JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.tested: JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.tested: JPEG_API_VERSION=8

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
