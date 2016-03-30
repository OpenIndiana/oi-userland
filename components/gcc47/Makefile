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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.7.3
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
COMPONENT_ARCHIVE_HASH= \
    sha256:34a273937eb63ee710784b65bcf9fb3cfcd79d02848f80c75f8254abd14c79c8
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/gnu-compiler

TPNO=			14467

include $(WS_MAKE_RULES)/gnu-component.mk

# The GNU compiler wants the GNU utilities.
PATH=$(GNUBIN):$(USRBINDIR):/usr/perl5/bin

PARCH =         $(MACH:i386=i386-pc)
GNU_ARCH =      $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=   GNU_ARCH="$(GNU_ARCH)"

VERSION_NUMBERS = $(subst ., ,$(COMPONENT_VERSION))
GCC_VERSION=$(word 1,$(VERSION_NUMBERS)).$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_VERSION=$(GCC_VERSION)
PKG_MACROS +=	GCC_V=$(word 1,$(VERSION_NUMBERS))$(word 2,$(VERSION_NUMBERS))
PKG_MACROS +=	GCC_BASEDIR=usr/gcc/$(GCC_VERSION)

# Make sure to pass -m32/64 any time the installed GCC is used
CC += $(CC_BITS)
CXX += $(CC_BITS)

# This product bootstraps itself.  The gcc flags are not the same
# as Studio flags. -O2 means different things for the two compilers
CFLAGS=-g -O2 
CXXFLAGS=-g -O2 

# direct binding cause various testsuite failures
LD_B_DIRECT=

# /usr/lib/ld/map.noexdata destroys Intel
LD_MAP_NOEXDATA.i386=

# /usr/lib/ld/map.noexbss  destroys SPARC
LD_MAP_NOEXBSS.sparc=

# for some reason the fixincludes target fails with bash on Solaris.
CONFIG_SHELL = /bin/sh
MAKESHELL = /bin/sh
COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_ENV += MAKESHELL=$(MAKESHELL)

CONFIGURE_PREFIX =	/usr/gcc/4.7
CONFIGURE_INFODIR =	$(CONFIGURE_PREFIX)/share/info

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,fortran,objc"
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--with-gmp-include=$(USRINCDIR)/gmp
CONFIGURE_OPTIONS +=	--with-mpfr-include=$(USRINCDIR)/mpfr
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=$(LD)
CONFIGURE_OPTIONS +=	--with-isl=no
CONFIGURE_OPTIONS +=	--with-cloog=no

CONFIGURE_ENV     += PYTHON="$(PYTHON)"

# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=$(USRBINDIR)/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=$(GNUBIN)/as

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

# To ensure that all tests that are expected to pass actually
# pass, we have to increase the stacksize limit to at least
# 16MB. Otherwise we'll get spurious failures in the test
# harness (gcc.c-torture/compile/limits-exprparen.c and others).
# With the soft stacksize limit set to 16384 we get reasonably good
# test results.
COMPONENT_PRE_TEST_ACTION = ulimit -Ss 16384
COMPONENT_TEST_ARGS = -k -i
COMPONENT_TEST_TARGETS = check check-target


REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpc
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
