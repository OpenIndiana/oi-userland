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

COMPONENT_NAME=		gutenprint
COMPONENT_VERSION=	5.2.7
COMPONENT_PROJECT_URL=	http://www.gutenprint.org/software/gutenprint/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:114c899227e3ebb0753c1db503e6a5c1afaa4b1f1235fdfe02fb6bbd533beed1
COMPONENT_ARCHIVE_URL=	http://voxel.dl.sourceforge.net/project/gimp-print/gutenprint-5.2/5.2.7/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	 --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=    --enable-escputil
CONFIGURE_OPTIONS +=    --without-gimp2
CONFIGURE_OPTIONS +=    --enable-cups-1_2-enhancements
CONFIGURE_OPTIONS +=    --enable-shared
CONFIGURE_OPTIONS +=    --disable-static-genppd
CONFIGURE_OPTIONS +=    --enable-simplified-cups-ppds
CONFIGURE_OPTIONS +=    --without-foomatic
CONFIGURE_OPTIONS +=    --without-foomatic3
CONFIGURE_OPTIONS +=    --without-readline
CONFIGURE_OPTIONS +=    --disable-static

COMPONENT_BUILD_TARGETS = all

build:		$(BUILD_32)

install:	$(INSTALL_32)

# the tests mostly pass, but it can't find several drivers for ppd files
test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)


include ../../make-rules/depend.mk
