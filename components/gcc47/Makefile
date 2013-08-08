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
COMPONENT_SUMMARY= "GNU Compiler Collection"
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2f7c37eb4fc14422ff2358a9ef59c974a75ab41204ef0e49fc34ab1d8981a9c3
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gcc.gnu.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/gcc/4.7


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
CONFIGURE_OPTIONS+= --with-gmp=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS+= --with-mpfr=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS+= --with-mpc=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto
CONFIGURE_OPTIONS+= --enable-ld=no
CONFIGURE_OPTIONS+= --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= --with-gnu-as
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_ARCH)/bin
CONFIGURE_OPTIONS+= --disable-libitm

CONFIGURE_OPTIONS+= LDFLAGS="-R$(CONFIGURE_PREFIX)/lib"

$(COMPONENT_DIR)/../gcc47-libgmp/build/$(MACH32)/.installed:
	$(GMAKE) -C $(COMPONENT_DIR)/../gcc47-libgmp install
$(COMPONENT_DIR)/../gcc47-libmpc/build/$(MACH32)/.installed:
	$(GMAKE) -C $(COMPONENT_DIR)/../gcc47-libmpc install
$(COMPONENT_DIR)/../gcc47-libmpfr/build/$(MACH32)/.installed:
	$(GMAKE) -C $(COMPONENT_DIR)/../gcc47-libmpfr install

COMPONENT_POST_INSTALL_ACTION = \
  for file in $(PROTO_DIR)/usr/gcc/4.7/lib/libgfortran.so.3.0.0 $(PROTO_DIR)/usr/gcc/4.7/lib/$(MACH64)/libgfortran.so.3.0.0; do \
    elfedit -e 'dyn:delete RUNPATH' $$file ; \
    elfedit -e 'dyn:delete RPATH' $$file ; \
  done ; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libgmp/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/include/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/include; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libgmp/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/lib/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libmpc/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/include/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/include; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libmpc/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/lib/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libmpfr/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/include/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/include; \
  $(CP) -PR $(COMPONENT_DIR)/../gcc47-libmpfr/build/prototype/$(MACH)$(CONFIGURE_PREFIX)/lib/* \
    $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib; \
  $(RM) -r $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/gcc/$(GNU_ARCH)/$(COMPONENT_VERSION)/include-fixed

build: \
  $(COMPONENT_DIR)/../gcc47-libgmp/build/$(MACH32)/.installed \
  $(COMPONENT_DIR)/../gcc47-libmpc/build/$(MACH32)/.installed \
  $(COMPONENT_DIR)/../gcc47-libmpfr/build/$(MACH32)/.installed \
  $(BUILD_32)

install: $(INSTALL_32)

clean::
	$(RM) -r $(COMPONENT_DIR)/../gcc47-libgmp/build $(COMPONENT_DIR)/../gcc47-libmpc/build $(COMPONENT_DIR)/../gcc47-libmpfr/build
