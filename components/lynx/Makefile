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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lynx
COMPONENT_VERSION=	2.8.7
COMPONENT_PROJECT_URL=	http://lynx.isc.org/
COMPONENT_SRC=		$(COMPONENT_NAME)2-8-7
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:301bda96ad3cd5032805e8d5315a42061a11e472e3d3a7baee3a2879517ef627
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_NAME)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/lynx

TPNO=			9373

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Needed to successfully find lynx.pot.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS +=	-I/usr/include/ncurses

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-nls
CONFIGURE_OPTIONS +=	--enable-japanese-utf8
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/lynx
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-screen=ncurses

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
