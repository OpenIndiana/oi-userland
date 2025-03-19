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
#

USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 13.3.0
COMPONENT_REVISION=	2
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:bdc80b99f448888bbf33d0432039391634a7210e7c6d014658856ded0347c731

MPFR_VERSION=4.2.1
MPFR_ARCHIVE_HASH= \
  sha256:b9df93635b20e4089c29623b19420c4ac848a1b29df1cfd59f26cab0d2666aa0

MPC_VERSION=1.3.1
MPC_ARCHIVE_HASH= \
  sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8

GMP_VERSION=6.3.0
GMP_ARCHIVE_HASH= \
  sha256:ac28211a7cfb609bae2e2c8d6058d66c8fe96434f740cf6fe2e47b000d1c20cb

include $(WS_MAKE_RULES)/gcc-component.mk

CPPFLAGS+=" -D_TS_ERRNO"
LDFLAGS="-R$OPT/lib"

# SPARC support.
ifeq ($(MACH), sparc)
COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) && autogen Makefile.def && \
	$(GPATCH) -p1 < $(COMPONENT_DIR)/sparc/gmp_asm_sparcv9_cpuflags.patch
CONFIGURE_OPTIONS+= --with-mulhigh-size=2048
CONFIGURE_OPTIONS+= --with-cpu=ultrasparc
else
COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) && autogen Makefile.def
endif

COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTOUSRDIR)/gcc/13/bin ; \
	  $(STRIP) \
		cpp gcov gcov-dump gcov-tool go gofmt lto-dump \
		$(GNU_TRIPLET)-g++ \
		$(GNU_TRIPLET)-gccgo \
		$(GNU_TRIPLET)-gcc-ar \
		$(GNU_TRIPLET)-gcc-nm \
		$(GNU_TRIPLET)-gfortran \
		$(GNU_TRIPLET)-gcc-ranlib \
		$(GNU_TRIPLET)-gcc-$(COMPONENT_VERSION) ; \
	  cd ../lib/gcc/$(GNU_TRIPLET)/$(COMPONENT_VERSION) ; \
	  $(STRIP) \
		cc1* collect2 f951 g++-mapper-server go1 lto-wrapper lto1 )

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_TRIPLET)/bin
CONFIGURE_OPTIONS+= --with-build-config=no
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,go,objc
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --with-system-zlib
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-__cxa_atexit
CONFIGURE_OPTIONS+= --enable-initfini-array
CONFIGURE_OPTIONS+= --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

PKG_HARDLINKS += usr/gcc/13/bin/g++
PKG_HARDLINKS += usr/gcc/13/bin/gcc
PKG_HARDLINKS += usr/gcc/13/bin/gcc-ar
PKG_HARDLINKS += usr/gcc/13/bin/gcc-nm
PKG_HARDLINKS += usr/gcc/13/bin/gcc-ranlib
PKG_HARDLINKS += usr/gcc/13/bin/gccgo
PKG_HARDLINKS += usr/gcc/13/bin/gfortran

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/linker
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c-runtime
REQUIRED_PACKAGES += system/library/math
