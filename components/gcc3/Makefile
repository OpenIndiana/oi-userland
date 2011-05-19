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
COMPONENT_VERSION=	3.4.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
# unfortunately we have our own "special" tarball and not the community version, so use that.
COMPONENT_ARCHIVE_HASH=	sha1:f7a27d5aeb07748eb6e924abfcfcf469c378b13e
COMPONENT_ARCHIVE_URL=	http://static.opensolaris.org/tarball/userland/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PARCH =		$(MACH:i386=i386-pc)
GNU_ARCH =	$(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=	GNU_ARCH="$(GNU_ARCH)"

# we build gcc with gcc
COMPILER =	gcc

# CC_BITS may get in the way
CC_BITS=

CONFIGURE_PREFIX =	/usr/sfw

# we need to override CONFIGURE_OPTIONS because GCC uses a configure that
# can't deal with CC as an argument
CONFIGURE_OPTIONS =	 --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	 --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	 --infodir=$(CONFIGURE_PREFIX)/share/info
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS +=	--enable-languages='c,c++,f77,objc'
CONFIGURE_OPTIONS +=	--enable-shared
# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/ccs/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/gnu/bin/as
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_ENV += 	CC="$(CC)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"

COMPONENT_BUILD_ENV += STAGE1_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CFLAGS_FOR_TARGET="$(CFLAGS)"
COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_TARGETS = bootstrap

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: $(TEST_32)

include ../../make-rules/depend.mk
