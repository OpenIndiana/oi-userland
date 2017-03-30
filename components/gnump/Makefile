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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER=gcc
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(USRBINDIR):$(GNUBIN)

COMPONENT_NAME=		gmp
COMPONENT_VERSION=      6.1.2
COMPONENT_PROJECT_URL=	http://gmplib.org/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz 
COMPONENT_ARCHIVE_HASH= \
    sha256:87b565e89a9a684fe4ebeeddb8399dce2599f9c9049854ca8c0dfbdea0e21912
COMPONENT_ARCHIVE_URL=  https://gmplib.org/download/gmp/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gnump
COMPONENT_ANITYA_ID=	1186

TPNO=			33317
TPNO_4.3.2=		16955

COMPONENT_VERSION_1=      4.3.2
COMPONENT_SRC_1=          $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=      $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:7be3ad1641b99b17f6a8be6a976f1f954e997c41e919ad7e0c418fe848c13c97
COMPONENT_ARCHIVE_URL_1=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_1)


COMPONENT_PREP_ACTION = (cd $(@D) ; $(AUTORECONF) -fiv)

# We need to build an extra static version of this library for
# GRUB/Wanboot support.

WANBOOT_CONFIGURE.amd64 = $(BUILD_DIR)/wanboot-amd64/.configured
WANBOOT_BUILD.amd64 = $(BUILD_DIR)/wanboot-amd64/.built
WANBOOT_INSTALL.amd64 = $(BUILD_DIR)/wanboot-amd64/.installed

CONFIGURE_32_and_64 += $(WANBOOT_CONFIGURE.$(MACH64))
BUILD_32_and_64 += $(WANBOOT_BUILD.$(MACH64))
INSTALL_32_and_64 += $(WANBOOT_INSTALL.$(MACH64))

$(BUILD_DIR_64)/.installed:	$(WANBOOT_INSTALL.$(MACH64))


# Macros to configure, build, and install the old version so we can contiune
# to deliver runtime support for GCC until a newer build of GCC built against
# the new GNU MP is part of the CBE.  Once the newer GCC packages are
# on the build systems, we can stop building and delivering the old version.
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured:        BITS=32
$(BUILD_OLD_DIR_64)/.configured:        BITS=64

CONFIGURE_32 +=	$(BUILD_OLD_DIR_32)/.configured
CONFIGURE_64 +=	$(BUILD_OLD_DIR_64)/.configured

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:     $(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_OLD_DIR_64)/.installed
#
# End old version

include $(WS_MAKE_RULES)/gnu-component.mk


MCS = mcs
STRIP = strip

# Set the wanboot CFLAGS as needed for the wanboot compilation
CFLAGS.wanboot += -D_BOOT
CFLAGS.wanboot += -g
CFLAGS.wanboot += -falign-jumps=1
CFLAGS.wanboot += -falign-loops=1
CFLAGS.wanboot += -falign-functions
CFLAGS.wanboot += -mno-mmx
CFLAGS.wanboot += -mno-3dnow
CFLAGS.wanboot += -fno-dwarf2-cfi-asm
CFLAGS.wanboot += -fno-asynchronous-unwind-tables
CFLAGS.wanboot += -fno-common
CFLAGS.wanboot += -mcmodel=large
CFLAGS.wanboot += -fno-stack-protector
CFLAGS.wanboot += -mno-stack-arg-probe

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# We want to run tests in a stripped environment so nothing interferes
COMPONENT_TEST_ENV += -i

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/^make\[[0-9]\{1,\}\]/make/g"' \
	'-n ' \
	'-e "/make:.*directory/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/ERROR/p" ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" '

PARCH.32 =	$(MACH:i386=i386-pc)
PARCH.64 =	$(MACH:i386=x86_64-pc)
GNU_TRIPLE.32 =	$(PARCH.32:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)
GNU_TRIPLE.64 =	$(PARCH.64:sparc=sparcv9-sun)-solaris$(SOLARIS_VERSION)

CONFIGURE_OPTIONS += --host $(GNU_TRIPLE.$(BITS))

CONFIGURE_OPTIONS.shared += --enable-shared
CONFIGURE_OPTIONS.shared += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --disable-alloca
CONFIGURE_OPTIONS.shared += --enable-cxx
CONFIGURE_OPTIONS += --enable-fft
CONFIGURE_OPTIONS += --disable-fat
CONFIGURE_OPTIONS.shared += --with-pic

# Set the wanboot configure options as needed for wanboot

CONFIGURE_OPTIONS.wanboot += --disable-assert
CONFIGURE_OPTIONS.wanboot += --disable-cxx
CONFIGURE_OPTIONS.wanboot += --disable-nails
CONFIGURE_OPTIONS.wanboot += --disable-profiling
CONFIGURE_OPTIONS.wanboot += --disable-minithres
CONFIGURE_OPTIONS.wanboot += --disable-shared
CONFIGURE_OPTIONS.wanboot += --enable-static
CONFIGURE_OPTIONS.wanboot += --disable-libtool-lock
CONFIGURE_OPTIONS.wanboot += --without-readline
CONFIGURE_OPTIONS.wanboot += --without-pic

COMPONENT_POST_INSTALL_ACTION.shared = \
	(cd $(PROTOUSRINCDIR) ; $(MV) -f gmp.h gmp-$(BITS).h)

COMPONENT_POST_INSTALL_ACTION.wanboot = \
      ( $(MKDIR) $(PROTOUSRLIBDIR)/grub/wanboot; \
	$(MV) $(PROTOUSRLIBDIR64)/libgmp.a $(PROTO_DIR)/usr/lib/grub/wanboot/libgmp.a; \
	$(STRIP) -x $(PROTOUSRLIBDIR)/grub/wanboot/libgmp.a; \
	$(MCS) -d $(PROTOUSRLIBDIR)/grub/wanboot/libgmp.a; \
	$(AR) ts $(PROTOUSRLIBDIR)/grub/wanboot/libgmp.a )

# Skipping this during automated tests since it hangs sometimes
$(SKIP_TEST_AT_TOP_LEVEL)

# common targets
configure:	$(CONFIGURE_32_and_64)

$(BUILD_DIR)/$(MACH32)/.configured: CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.shared)
$(BUILD_DIR)/$(MACH64)/.configured: CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.shared)
$(BUILD_DIR)/wanboot-amd64/.configured: BITS=64
$(BUILD_DIR)/wanboot-amd64/.configured: COMPILER=gcc
$(BUILD_DIR)/wanboot-amd64/.configured: CPPFLAGS += $(CPPFLAGS.wanboot)
$(BUILD_DIR)/wanboot-amd64/.configured: CFLAGS += $(CFLAGS.wanboot)
$(BUILD_DIR)/wanboot-amd64/.configured: CXXFLAGS += $(CXXFLAGS.wanboot)
$(BUILD_DIR)/wanboot-amd64/.configured: CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.wanboot)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

$(BUILD_DIR)/$(MACH32)/.installed: COMPONENT_POST_INSTALL_ACTION = $(COMPONENT_POST_INSTALL_ACTION.shared)
$(BUILD_DIR)/$(MACH64)/.installed: COMPONENT_POST_INSTALL_ACTION = $(COMPONENT_POST_INSTALL_ACTION.shared)
$(BUILD_DIR)/wanboot-amd64/.installed: COMPONENT_POST_INSTALL_ACTION = $(COMPONENT_POST_INSTALL_ACTION.wanboot)

REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
