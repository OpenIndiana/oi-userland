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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#
export PARFAIT_BUILD=no

COMPILER=gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.9.3
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:e6c63b40877bc756cc7cfe6ca98013eb15f02ec6c8c2cf68e24533ad1203aaba
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/gnu-compiler

TPNO=			24017

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# The GNU compiler wants the GNU utilities.
PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

PATCH_LEVEL := 0
ENABLE_CLOOG := 0

PARCH =         $(MACH:i386=i386-pc)
GNU_ARCH =      $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=   GNU_ARCH="$(GNU_ARCH)"

VERSION_NUMBERS = $(subst ., ,$(COMPONENT_VERSION))
GCC_VERSION=$(word 1,$(VERSION_NUMBERS)).$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_VERSION=$(GCC_VERSION)
PKG_MACROS +=	GCC_V=$(word 1,$(VERSION_NUMBERS))$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_BASEDIR=usr/gcc/$(GCC_VERSION)

GNU_SECTIONS_MAPFILE = $(COMPONENT_DIR)/Solaris/map.gnu-sections

CFLAGS.i386 = -mtune=opteron -march=opteron -fno-strict-aliasing
CFLAGS.sparc = -mtune=ultrasparc3 -mcpu=ultrasparc3 -mvis2 \
  -mno-unaligned-doubles -mhard-float -fno-strict-aliasing
CFLAGS = -g -O2 -pthread
CFLAGS += $(CFLAGS.$(MACH))

# _REENTRANT is no longer needed in S12, but still needed in S11.
CFLAGS += -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CXXFLAGS = -g -O2 -pthread
CXXFLAGS += $(CFLAGS.$(MACH))

# If not built with largefile support, cc1 and cc1plus will die
# on some very large translation units in GCC 4.9 and GCC 5.2.
CXXFLAGS += -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

# direct binding causes various testsuite failures
LD_B_DIRECT=

# /usr/lib/ld/map.noexdata destroys Intel
LD_MAP_NOEXDATA.i386=

# /usr/lib/ld/map.noexbss  destroys SPARC
LD_MAP_NOEXDATA.sparc=

CLOOG_PREFIX = /usr
ISLINCLUDE=$(CLOOG_PREFIX)/include
CLOOGINCLUDE=$(CLOOG_PREFIX)/include
ISLLIB.32 = $(CLOOG_PREFIX)/lib
ISLLIB.64 = $(CLOOG_PREFIX)/lib/$(MACH64)
ISLLIB=$(ISLLIB.$(BITS))
CLOOGLIB.32 = $(CLOOG_PREFIX)/lib
CLOOGLIB.64 = $(CLOOG_PREFIX)/lib/$(MACH64)
CLOOGLIB = $(CLOOGLIB.$(BITS))

ifeq ($(ENABLE_CLOOG), 1)
  CPPFLAGS += -I$(CLOOGINCLUDE)
endif

# We need ELF section coalescing when compiling with -fdata-sections
# -ffunction-sections. Otherwise we end up with pathologically high
#  number of ELF sections.
LD_OPTIONS += -M $(GNU_SECTIONS_MAPFILE)
LD_OPTIONS += -z relax=comdat,common,secadj,symbound,transtls

# for some reason the fixincludes target fails with bash on Solaris.
CONFIG_SHELL = /bin/sh
MAKESHELL = /bin/sh

COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_ENV += MAKESHELL=$(MAKESHELL)
COMPONENT_BUILD_ENV += LD_OPTIONS="$(LD_OPTIONS)"

CONFIGURE_PREFIX = /usr/gcc/$(GCC_VERSION)

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_PREFIX)/share/info
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,fortran,objc,lto"
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-ssp=yes
CONFIGURE_OPTIONS +=	--enable-nls=yes

# --enable-largefile=yes gets canceled or reset several times by
#  several different ./configure's. We have to re-enable it via
#  several different patches.
CONFIGURE_OPTIONS +=	--enable-largefile=yes
CONFIGURE_OPTIONS +=	--with-gmp-include=/usr/include/gmp
CONFIGURE_OPTIONS +=	--with-mpfr-include=/usr/include/mpfr
CONFIGURE_OPTIONS +=	--with-gnu-as --with-as=/usr/gnu/bin/as
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS +=    --enable-multilib=yes
CONFIGURE_OPTIONS +=    --enable-threads=posix
CONFIGURE_OPTIONS +=    --enable-tls=yes
CONFIGURE_OPTIONS +=    --enable-libstdcxx-threads=yes
CONFIGURE_OPTIONS +=    --enable-libstdcxx-pch=no
CONFIGURE_OPTIONS +=    --enable-libstdcxx-visibility=no

# This needs additional linker support.
CONFIGURE_OPTIONS +=    --enable-initfini-array=yes

# VTable verification needs additional linker support.
CONFIGURE_OPTIONS +=    --enable-vtable-verify=no
CONFIGURE_OPTIONS +=    --enable-comdat=yes
CONFIGURE_OPTIONS +=    --enable-__cxa_atexit=yes

# Although this is required by the C++11/C++14 standards,
# it appears broken in 4.9.3.
CONFIGURE_OPTIONS +=    --enable-fully-dynamic-string=yes
CONFIGURE_OPTIONS +=    --enable-libstdcxx-debug=yes
CONFIGURE_OPTIONS +=    --enable-libstdcxx-threads=yes
CONFIGURE_OPTIONS +=    --enable-c99=yes
CONFIGURE_OPTIONS +=    --enable-long-long=yes
CONFIGURE_OPTIONS +=    --enable-wchar_t=yes
CONFIGURE_OPTIONS +=    --with-system-zlib

# We'll enable ISL and CLooG as soon as CLooG integrates and is
# available on the build machines.
ifeq ($(ENABLE_CLOOG), 1)
  CONFIGURE_OPTIONS +=    --disable-isl-version-check
  CONFIGURE_OPTIONS +=    --disable-cloog-version-check
  CONFIGURE_OPTIONS +=    --with-isl=$(CLOOG_PREFIX)
  CONFIGURE_OPTIONS +=    --with-isl-include=$(ISLINCLUDE)
  CONFIGURE_OPTIONS +=    --with-isl-lib=$(ISLLIB)
  CONFIGURE_OPTIONS +=    --with-cloog=$(CLOOG_PREFIX)
  CONFIGURE_OPTIONS +=    --with-cloog-include=$(CLOOGINCLUDE)
  CONFIGURE_OPTIONS +=    --with-cloog-lib=$(CLOOGLIB)
else
  CONFIGURE_OPTIONS +=    --with-isl=no
  CONFIGURE_OPTIONS +=    --with-cloog=no
endif

CONFIGURE_OPTIONS +=    --with-build-time-tools=/usr/gnu/bin
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=    CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_ENV     += PYTHON="$(PYTHON)"

COMPONENT_BUILD_TARGETS=bootstrap

# compile python modules
COMPONENT_POST_INSTALL_ACTION = \
    ( gfind $(PROTOUSRDIR) -name '*.py' | xargs -n 1 dirname | sort -u | \
        xargs $(PYTHON) -m compileall )

# strip elves, strip ignores non-elf files
COMPONENT_POST_INSTALL_ACTION += ; \
    ( gfind $(PROTOUSRDIR) -type f -perm /0111 | xargs /usr/bin/strip -x \
        2>/dev/null ; exit 0 )

# ASLR has side-effects with libitm and libgomp.
# Disable ASLR for now.
ASLR_MODE=$(ASLR_DISABLE)

configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)

# To ensure that all tests that are expected to pass actually
# pass, we have to increase the stacksize limit to at least
# 16MB. Otherwise we'll get spurious failures in the test
# harness (gcc.c-torture/compile/limits-exprparen.c and others).
# With the soft stacksize limit set to 16384 we get reasonably good
# test results.
COMPONENT_PRE_TEST_ACTION = ulimit -Ss 16384
COMPONENT_TEST_ARGS = -k -i
COMPONENT_TEST_TARGETS = check check-target

COMPONENT_TEST_ENV += TCL_LIBRARY="/usr/lib/tcl8.5"
COMPONENT_TEST_ENV += DEJAGNULIBS="/usr/share/dejagnu"

test:	$(TEST_32)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

ifeq ($(ENABLE_CLOOG), 1)
  REQUIRED_PACKAGES += library/isl
  REQUIRED_PACKAGES += developer/cloog
endif

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpc
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker

