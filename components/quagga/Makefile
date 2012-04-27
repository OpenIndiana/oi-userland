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
# Copyright (c) 2006, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		quagga
COMPONENT_VERSION=	0.99.19
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.quagga.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc5052d285af6e7aac42984741e74261637c57c4a02032bf05de7a5ea3a1afe0
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
PATCH_LEVEL = 0

# without this we bus error on sparc. Until the code in all of Quagga
# does not have any misaligned code we will need the following flag.
studio_ALIGN.sparc.32=  -xmemalign=8i

# These options are carried over from the SFW consolidation. Using -xO4 was
# explicitly commented out, but no reason was documented.

studio_OPT = -xO3

LDFLAGS +=-lumem
CFGLOCALSTATEDIR=/system/volatile/quagga
CFGSYSCONFDIR=  $(ETCDIR)/quagga

CFLAGS += -xspace -Xa
CFLAGS += -g -xdebugformat=dwarf -O
CFLAGS += -errtags=yes -xc99=%all
CFLAGS += -erroff=E_TRAILING_COMMA_IN_ENUM
CFLAGS += -erroff=E_STATEMENT_NOT_REACHED
CFLAGS += -erroff=E_EMPTY_TRANSLATION_UNIT

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--with-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-opaque-lsa
CONFIGURE_OPTIONS +=	--localstatedir=$(CFGLOCALSTATEDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(CFGSYSCONFDIR)
CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--enable-isisd
CONFIGURE_OPTIONS +=	--enable-trill
CONFIGURE_OPTIONS +=	--disable-watchquagga
CONFIGURE_OPTIONS +=	--enable-ospf6d
CONFIGURE_OPTIONS +=	--enable-ripngd
CONFIGURE_OPTIONS +=	--enable-user=root
CONFIGURE_OPTIONS +=	--enable-group=root
CONFIGURE_OPTIONS +=	--enable-solaris

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

build:		$(BUILD_32)
install:	$(INSTALL_32)
test:	$(NO_TESTS)

include ../../make-rules/depend.mk
