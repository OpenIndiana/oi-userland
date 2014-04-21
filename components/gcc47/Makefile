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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gcc
COMPONENT_VERSION= 4.7.3
COMPONENT_REVISION=1
MPFR_NAME= mpfr
MPFR_VERSION=3.1.2
MPC_NAME=mpc
MPC_VERSION=1.0.1
GMP_NAME=gmp
GMP_VERSION=5.0.5
COMPONENT_SUMMARY= GNU Compiler Collection
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2f7c37eb4fc14422ff2358a9ef59c974a75ab41204ef0e49fc34ab1d8981a9c3
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gcc.gnu.org/
PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES = $(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort) $(EXTRA_PATCHES)

COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= http://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= \
    sha256:79c73f60af010a30a5c27a955a1d2d01ba095b72537dab0ecaad57f5a7bb1b6b
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += mv $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME)

COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  http://www.multiprecision.org/mpc/download/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2= \
    sha256:ed5a815cfea525dc778df0cb37468b9c1b554aaf30d9328b1431ca705b7400ff
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += mv $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME)

COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_ARCHIVE_HASH_3= \
    sha256:1f588aaccc41bb9aed946f9fe38521c26d8b290d003c5df807f65690f2aadec9
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += mv $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CC_BITS=
CFLAGS=         -g -O2

CONFIGURE_PREFIX= /usr/gcc/4.7
PATH=/usr/bin:/usr/gnu/bin:/usr/perl5/bin

PARCH = $(MACH:i386=i386-pc)
GNU_ARCH = $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_ARCH="$(GNU_ARCH)"

# Build recipe borrowed from OmniOS

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=/usr/bin/ld
COMMON_ENV+= LD_FOR_HOST=/usr/bin/ld
COMMON_ENV+= LD=/usr/bin/ld

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

COMPONENT_PRE_CONFIGURE_ACTION+= pfexec chmod 444 /usr/gnu/$(GNU_ARCH)/bin/ld
COMPONENT_POST_CONFIGURE_ACTION+= pfexec chmod 555 /usr/gnu/$(GNU_ARCH)/bin/ld

CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_ARCH)
CONFIGURE_OPTIONS+= --build $(GNU_ARCH)
CONFIGURE_OPTIONS+= --target $(GNU_ARCH)
CONFIGURE_OPTIONS+= --with-boot-ldflags=-R$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto,objc
CONFIGURE_OPTIONS+= --enable-ld=no
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_ARCH)/bin
CONFIGURE_OPTIONS+= --disable-libitm

# On SPARC systems, use Sun Assembler
CONFIGURE_OPTIONS.sparc+= --without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386+= --with-gnu-as --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS+= LDFLAGS="-R$(CONFIGURE_PREFIX)/lib"

COMPONENT_POST_INSTALL_ACTION = \
  for file in $(PROTO_DIR)/usr/gcc/4.7/lib/libgfortran.so.3.0.0 $(PROTO_DIR)/usr/gcc/4.7/lib/$(MACH64)/libgfortran.so.3.0.0; do \
    elfedit -e 'dyn:delete RUNPATH' $$file ; \
    elfedit -e 'dyn:delete RPATH' $$file ; \
  done ; \
  $(RM) -r $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/gcc/$(GNU_ARCH)/$(COMPONENT_VERSION)/include-fixed

build: $(BUILD_32)

install: $(INSTALL_32)
