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

COMPONENT_NAME=		screen
COMPONENT_VERSION=	4.0.3
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/screen/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:78f0d5b1496084a5902586304d4a73954b2bfe33ea13edceecf21615c39e6c77
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/screen/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=	--enable-colors256
CONFIGURE_OPTIONS +=	--with-sys-screenrc=/etc/screenrc
CONFIGURE_OPTIONS +=	--disable-socket-dir
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

PROTOTERMINFODIR=$(PROTOUSRSHAREDIR)/lib/terminfo

$(PROTOTERMINFODIR):
	$(MKDIR) $@

$(INSTALL_32):	$(PROTOTERMINFODIR)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
