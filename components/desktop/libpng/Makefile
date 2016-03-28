#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =		gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpng
COMPONENT_VERSION=	1.4.19
COMPONENT_PROJECT_URL=	http://www.libpng.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b73b7f0aec1f4d89fb6a587d4174dede493af8a3c04bb6eb87b0d10a8623bd7f
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libpng/files/libpng14/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libpng

COMPONENT_VERSION_1 =   1.2.49
COMPONENT_SRC_1 =       $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1 =   $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:f906778030f5dc7930844b9d67ddf4f2809f7407784c4eba7e8d6e0db9f61671
COMPONENT_ARCHIVE_URL_1= https://sourceforge.net/projects/libpng/files/libpng12/older-releases/1.2.49/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1 =          $(COMPONENT_DIR)/$(COMPONENT_SRC_1)


COMPONENT_VERSION_2 =   1.0.59
COMPONENT_SRC_2 =       $(COMPONENT_NAME)-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2 =   $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_HASH_2 = \
    sha256:33e0d3ac3b7c48450acd298e198d243e0d5400e2436d6eec67f2a283cd82e7c4
COMPONENT_ARCHIVE_URL_2= https://sourceforge.net/projects/libpng/files/libpng10/older-releases/1.0.59/$(COMPONENT_ARCHIVE_2)
SOURCE_DIR_2 =          $(COMPONENT_DIR)/$(COMPONENT_SRC_2)

TPNO=		27311

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS +=	$(CC_BITS)

CONFIGURE_OPTIONS +=	--with-esd-prefix=$(PROTOUSRDIR)
CONFIGURE_OPTIONS +=	LDFLAGS=$(LDFLAGS)

# ------------------------ libpng10 ----------------------------

# Macros to configure, build, and install the libpng10 files.
BUILD_PNG10_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH32)
BUILD_PNG10_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_2)-$(MACH64)

$(BUILD_PNG10_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_2)/configure
$(BUILD_PNG10_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_2)/configure
$(BUILD_PNG10_DIR_32)/.configured: BITS=32
$(BUILD_PNG10_DIR_64)/.configured: BITS=64

BUILD_32 += $(BUILD_PNG10_DIR_32)/.built
BUILD_64 += $(BUILD_PNG10_DIR_64)/.built

INSTALL_32 += $(BUILD_PNG10_DIR_32)/.installed
INSTALL_64 += $(BUILD_PNG10_DIR_64)/.installed

$(BUILD_DIR_32)/.installed:     $(BUILD_PNG10_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_PNG10_DIR_64)/.installed

# ------------------------ libpng12 ----------------------------

# Macros to configure, build, and install the libpng12 files.
BUILD_PNG12_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_PNG12_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_PNG12_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_PNG12_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_PNG12_DIR_32)/.configured: BITS=32
$(BUILD_PNG12_DIR_64)/.configured: BITS=64

BUILD_32 += $(BUILD_PNG12_DIR_32)/.built
BUILD_64 += $(BUILD_PNG12_DIR_64)/.built

INSTALL_32 += $(BUILD_PNG12_DIR_32)/.installed
INSTALL_64 += $(BUILD_PNG12_DIR_64)/.installed

$(BUILD_DIR_32)/.installed:     $(BUILD_PNG12_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_PNG12_DIR_64)/.installed

# -----------------------------------------------------------------

CLEAN_PATHS +=	$(SOURCE_DIR_1)
CLEAN_PATHS +=	$(SOURCE_DIR_2)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS = -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/Pass /p" ' \
        '-e "/TOTAL:/p" ' \
        '-e "/Filter/p" ' \
        '-e "/PASS/p" ' \
        '-e "/ERROR:/p" '

# for pngtest to run
COMPONENT_TEST_ENV +=   libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=   libtool_execute_magic='%%%MAGIC variable%%%'

ASLR_MODE =	$(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
