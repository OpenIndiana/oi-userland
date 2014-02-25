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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
export PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.8.2
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:2ea77114344a06c45dd5791275311e91d306545aa5ec9db31d24174f6965e880
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/gnu-compiler

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPILER=gcc

# The GNU compiler wants the GNU utilities.
PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

PARCH =         $(MACH:i386=i386-pc)
GNU_ARCH =      $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=   GNU_ARCH="$(GNU_ARCH)"

VERSION_NUMBERS = $(subst ., ,$(COMPONENT_VERSION))
GCC_VERSION=$(word 1,$(VERSION_NUMBERS)).$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_VERSION=$(GCC_VERSION)
PKG_MACROS +=	GCC_V=$(word 1,$(VERSION_NUMBERS))$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_BASEDIR=usr/gcc/$(GCC_VERSION)

CFLAGS.i386 = -mtune=opteron -march=opteron
CFLAGS.sparc = -mtune=ultrasparc -mcpu=ultrasparc -mno-unaligned-doubles
CFLAGS = -g -O2 
CFLAGS += $(CFLAGS.$(MACH))
CXXFLAGS = -g -O2
CXXFLAGS += $(CFLAGS.$(MACH))

# direct binding causes various testsuite failures
LD_B_DIRECT=

# /usr/lib/ld/map.noexdata destroys Intel
LD_MAP_NOEXDATA.i386=

# /usr/lib/ld/map.noexbss  destroys SPARC
ifeq ($(MACH),sparc)
LD_MAP_NOEXBSS=
endif


# for some reason the fixincludes target fails with bash on Solaris.
CONFIG_SHELL = /bin/sh
MAKESHELL = /bin/sh
COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_ENV += MAKESHELL=$(MAKESHELL)

CONFIGURE_PREFIX = /usr/gcc/4.8

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_PREFIX)/share/info
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,fortran,objc"
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--with-gmp-include=/usr/include/gmp
CONFIGURE_OPTIONS +=	--with-mpfr-include=/usr/include/mpfr
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=/usr/bin/ld

CONFIGURE_ENV     += PYTHON="$(PYTHON)"

# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/gnu/bin/as
CONFIGURE_OPTIONS +=    $(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"

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

test:	$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

