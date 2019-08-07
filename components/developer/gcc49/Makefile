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
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gcc
COMPONENT_VERSION= 4.9.4
COMPONENT_REVISION=6
MPFR_NAME= mpfr
MPFR_VERSION=3.1.3
MPC_NAME=mpc
MPC_VERSION=1.0.3
GMP_NAME=gmp
GMP_VERSION=5.0.5
COMPONENT_SUMMARY= GNU Compiler Collection
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:6c11d292cd01b294f9f84c9a59c230d80e9e4a47e5c6355f046bb36d4f358092
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_PROJECT_URL = http://gcc.gnu.org/
PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES = $(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort) $(EXTRA_PATCHES)

COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= http://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_SIG_URL_1= $(COMPONENT_ARCHIVE_URL_1).asc
COMPONENT_ARCHIVE_HASH_1= \
    sha256:f63bb459157cacd223caac545cb816bcdb5a0de28b809e7748b82e9eb89b0afd
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += ( $(RM) -r $(COMPONENT_SRC)/$(MPFR_NAME) && $(CP) -rpP $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME) )

COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  http://www.multiprecision.org/mpc/download/$(COMPONENT_ARCHIVE_2)
COMPONENT_SIG_URL_2=	$(COMPONENT_ARCHIVE_URL_2).sig 
COMPONENT_ARCHIVE_HASH_2= \
    sha256:617decc6ea09889fb08ede330917a00b16809b8db88c29c31bfbb49cbf88ecc3
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += ( $(RM) -r $(COMPONENT_SRC)/$(MPC_NAME) && $(CP) -rpP $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME) )

COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_SIG_URL_3=	$(COMPONENT_ARCHIVE_URL_3).sig 
COMPONENT_ARCHIVE_HASH_3= \
    sha256:1f588aaccc41bb9aed946f9fe38521c26d8b290d003c5df807f65690f2aadec9
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += ( $(RM) -r $(COMPONENT_SRC)/$(GMP_NAME) && $(CP) -rpP $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME) )

GCC_VERSION= 4.9

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CC_BITS=
CFLAGS=         -g -O2

COMPONENT_BUILD_ARGS=

CONFIGURE_PREFIX= /usr/gcc/4.9
PATH=$(PATH.gnu)

# Build recipe borrowed from OmniOS

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=/usr/bin/ld
COMMON_ENV+= LD_FOR_HOST=/usr/bin/ld
COMMON_ENV+= LD=/usr/bin/ld

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --build $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --target $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --with-boot-ldflags=-R$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto,objc
CONFIGURE_OPTIONS+= --without-gnu-ld
CONFIGURE_OPTIONS+= --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_TRIPLET)/bin
CONFIGURE_OPTIONS+= --disable-libitm
CONFIGURE_OPTIONS+= --enable-install-libiberty

# On SPARC systems, use Sun Assembler
CONFIGURE_OPTIONS.sparc+= --without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386+= --with-gnu-as --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS+= LDFLAGS="-R$(CONFIGURE_PREFIX)/lib"

COMPONENT_POST_INSTALL_ACTION += \
  $(RM) -r $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/gcc/$(GNU_TRIPLET)/$(COMPONENT_VERSION)/include-fixed ;

build: $(BUILD_32)

install: $(INSTALL_32)

# GCC uses installed runtime libraries
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/gfortran-4-runtime
REQUIRED_PACKAGES += system/library/gobjc-4-runtime
REQUIRED_PACKAGES += system/library/math
