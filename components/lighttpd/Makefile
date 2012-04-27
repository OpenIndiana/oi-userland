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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lighttpd
COMPONENT_VERSION=	1.4.23
COMPONENT_PROJECT_URL=	http://www.lighttpd.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8555db22ed7d429160701555611d8cd5eff42fc7e6e3ad3b050279c9b2145469
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)

LIGHTTPD_INSTALLDIR=/usr/lighttpd/1.4

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# libtool linking will fail unless we re-create configure.
COMPONENT_PREP_ACTION = ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

# lighttpd is logging using __FILE__ macro. Cloning will make this happen
# using just source file names (without full absolute paths).
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX= /usr/lighttpd/1.4
CONFIGURE_MANDIR= $(CONFIGURE_PREFIX)/man

CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-lua
CONFIGURE_OPTIONS +=	--with-openssl
CONFIGURE_OPTIONS +=	--with-pcre
CONFIGURE_OPTIONS +=	--with-mysql=/usr/mysql/bin/mysql_config
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
