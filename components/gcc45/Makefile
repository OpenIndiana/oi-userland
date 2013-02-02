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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.5.2
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:07b880faf29f3f9d9c0953717002ac29f5d061427797d2487a7c9c169e6395b3
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-compiler

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/perl5/bin

PARCH =         $(MACH:i386=i386-pc)
GNU_ARCH =      $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=   GNU_ARCH="$(GNU_ARCH)"

# This product bootstraps itself.  The gcc flags are not the same
# as Studio flags. -O2 means different things for the two compilers
CFLAGS=-g -O2 
CFLAGS_FOR_BUILD=$(CFLAGS)

# CC_BITS may get in the way
CC_BITS=

CONFIG_SHELL = /bin/sh

CONFIGURE_PREFIX = /usr/gcc/4.5

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_PREFIX)/share/info
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,fortran,objc"
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--with-gmp-include=/usr/include/gmp
CONFIGURE_OPTIONS +=	--with-mpfr-include=/usr/include/mpfr
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=/usr/bin/ld

# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/gnu/bin/as
CONFIGURE_OPTIONS +=    $(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# Keep ASLR disabled (the default) for gcc 4.5; build often core dumps with ASLR

COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)

COMPONENT_BUILD_TARGETS=bootstrap

build:		$(BUILD_32)

install:	$(INSTALL_32) 

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
