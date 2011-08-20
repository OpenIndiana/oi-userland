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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.5.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:4fdd2d709b15e993f32dbf81412f48dc377e32be
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

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

CONFIGURE_OPTIONS += --enable-languages="c,c++,fortran,objc" \
	--enable-shared \
	--with-gmp-include=/usr/include/gmp \
	--with-mpfr-include=/usr/include/mpfr \
	--prefix=$(CONFIGURE_PREFIX) \
	--mandir=$(CONFIGURE_MANDIR) \
	--infodir=$(CONFIGURE_PREFIX)/share/info \
	--libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 

COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)

COMPONENT_BUILD_TARGETS=bootstrap

build:		$(BUILD_32)

install:	$(INSTALL_32) 

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
