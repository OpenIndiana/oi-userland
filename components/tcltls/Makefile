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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tls
COMPONENT_VERSION=	1.6
COMPONENT_PROJECT_URL=	http://tls.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:adec50143a9ad634a671d24f7c7bbf2455487eb5f12d290f41797c32a98b93f3
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/tls/files/tls/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))
CONFIGURE_ENV.64 +=	MACH64DIR="$(MACH64)"

CONFIGURE_OPTIONS +=	--with-tclinclude=/usr/include
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -KPIC -xstrconst"
CONFIGURE_OPTIONS +=	--with-tcl=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS.64 += --enable-64bit

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
