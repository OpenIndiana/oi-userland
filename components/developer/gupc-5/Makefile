#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           gupc-5
COMPONENT_MAJOR=          5
COMPONENT_VERSION=        $(COMPONENT_MAJOR).2.0.1
COMPONENT_SUMMARY=        GNU UPC - compilation and execution environment for the UPC (Unified Parallel C) language
COMPONENT_PROJECT_URL=    http://www.gccupc.org/
COMPONENT_FMRI=           developer/gupc-5
COMPONENT_CLASSIFICATION= Development/C 
COMPONENT_SRC_NAME=       upc
COMPONENT_SRC=            $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://www.gccupc.org/downloads/upc/rls/$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).src.tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:45805995497cf7f52902d234f02bcd773e421a77b8b515026825aac46f64c6ad

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/bin:/usr/gnu/bin:$(dir $(PERL))

PARCH = $(MACH:i386=i386-pc)
GNU_ARCH = $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_ARCH="$(GNU_ARCH)"

CC_BITS=
CFLAGS=         -g -O2

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=/usr/bin/ld
COMMON_ENV+= LD=/usr/bin/ld
COMMON_ENV+= AS_FOR_TARGET=$(GAS)
COMMON_ENV+= AS=$(GAS)

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

CONFIGURE_PREFIX= /usr/gupc/$(COMPONENT_MAJOR)

CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_ARCH)
CONFIGURE_OPTIONS+= --build $(GNU_ARCH)
CONFIGURE_OPTIONS+= --target $(GNU_ARCH)
CONFIGURE_OPTIONS+= --enable-languages=c
CONFIGURE_OPTIONS+= --enable-lto
CONFIGURE_OPTIONS+= --without-gnu-ld
CONFIGURE_OPTIONS+= --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_ARCH)/bin
CONFIGURE_OPTIONS+= --with-gmp-include=$(USRINCDIR)/gmp
CONFIGURE_OPTIONS+= --with-mpfr-include=$(USRINCDIR)/mpfr
CONFIGURE_OPTIONS+= --with-mpc-include=$(USRINCDIR)/mpc

# On SPARC systems, use Sun Assembler
CONFIGURE_OPTIONS.sparc+= --without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 += --with-gnu-as --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(MACH))

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpc
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
