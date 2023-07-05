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

BUILD_BITS= 32_and_64
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libjpeg-turbo
COMPONENT_VERSION= 3.0.0
COMPONENT_SUMMARY= libjpeg -JPEG Turbo libraries
COMPONENT_PROJECT_URL= https://www.libjpeg-turbo.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c77c65fcce3d33417b2e90432e7a0eb05f59a7fff884022a9d931775d583bfaa
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libjpeg-turbo/files/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.gz/download
COMPONENT_FMRI= image/library/libjpeg-turbo
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= IJG,BSD,zlib
COMPONENT_LICENSE_FILE= LICENSE.md

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_DEFAULT_DIRS= no

# Warnings are normal: libtool:   error: ignoring unknown tag NASM

CMAKE_OPTIONS.JPEG6= 
CMAKE_OPTIONS.JPEG7= -DWITH_JPEG7=ON
CMAKE_OPTIONS.JPEG8= -DWITH_JPEG8=ON

LIBJPEG_TURBO_X_PREFIX=$(USRLIBDIR)/libjpeg$(JPEG_API_VERSION)-turbo

CMAKE_OPTIONS+=	-DENABLE_STATIC=FALSE
# Allow for build with different API compliance
CMAKE_OPTIONS+=	$(CMAKE_OPTIONS.JPEG$(JPEG_API_VERSION))
CMAKE_OPTIONS+=	-DCMAKE_INSTALL_PREFIX=$(LIBJPEG_TURBO_X_PREFIX)
CMAKE_OPTIONS+= -DCMAKE_INSTALL_MANDIR=$(USRSHAREMANDIR)
CMAKE_OPTIONS+= -DCMAKE_INSTALL_DOCDIR=$(USRSHAREDOCDIR)/libjpeg-turbo
CMAKE_OPTIONS+= -DCMAKE_INSTALL_INCLUDEDIR=$(USRINCDIR)/libjpeg$(JPEG_API_VERSION)-turbo
CMAKE_OPTIONS.32+= -DCMAKE_INSTALL_BINDIR=$(LIBJPEG_TURBO_X_PREFIX)/bin
CMAKE_OPTIONS.32+= -DCMAKE_INSTALL_LIBDIR=$(LIBJPEG_TURBO_X_PREFIX)/lib
CMAKE_OPTIONS.64+= -DCMAKE_INSTALL_BINDIR=$(LIBJPEG_TURBO_X_PREFIX)/bin/$(MACH64)
CMAKE_OPTIONS.64+= -DCMAKE_INSTALL_LIBDIR=$(LIBJPEG_TURBO_X_PREFIX)/lib/$(MACH64)

COMPONENT_TEST_TRANSFORMS+= '-e "s/[0-9. ]*sec//g"'

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

ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 = $(BUILD_DIR_32_6)/.tested $(BUILD_DIR_32_7)/.tested $(BUILD_DIR_32_8)/.tested
TEST_64 = $(BUILD_DIR_64_6)/.tested $(BUILD_DIR_64_7)/.tested $(BUILD_DIR_64_8)/.tested
$(BUILD_DIR_32)/%/.tested:		BITS=32
$(BUILD_DIR_64)/%/.tested:		BITS=64
$(BUILD_DIR)/%/6/.tested: JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.tested: JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.tested: JPEG_API_VERSION=8
else
TEST_32 = $(BUILD_DIR_32_6)/.tested-and-compared $(BUILD_DIR_32_7)/.tested-and-compared $(BUILD_DIR_32_8)/.tested-and-compared
TEST_64 = $(BUILD_DIR_64_6)/.tested-and-compared $(BUILD_DIR_64_7)/.tested-and-compared $(BUILD_DIR_64_8)/.tested-and-compared
$(BUILD_DIR_32)/%/.tested-and-compared:	BITS=32
$(BUILD_DIR_64)/%/.tested-and-compared:	BITS=64
$(BUILD_DIR)/%/6/.tested-and-compared: JPEG_API_VERSION=6
$(BUILD_DIR)/%/7/.tested-and-compared: JPEG_API_VERSION=7
$(BUILD_DIR)/%/8/.tested-and-compared: JPEG_API_VERSION=8
endif

TEST_32_and_64 =	$(TEST_32) $(TEST_64)

build:         $(BUILD_32_and_64)

install:       $(INSTALL_32_and_64)

test:          $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
