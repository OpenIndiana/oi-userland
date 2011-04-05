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

COMPONENT_NAME=		cvs
COMPONENT_VERSION=	1.12.13
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:93a8dacc6ff0e723a130835713235863f1f5ada9
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/non-gnu/cvs/source/feature/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=	--with-external-zlib
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

build:		$(BUILD_32)

install:	$(INSTALL_32)
	sed -f solarisman-stability $(COMPONENT_SRC)/doc/cvs.1 > \
				   $(PROTOUSRSHAREMAN1DIR)/cvs.1
	sed -f solarisman-stability $(COMPONENT_SRC)/man/cvs.5 > \
				   $(PROTOUSRSHAREMAN5DIR)/cvs.5

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

# "check" is not working yet.  It's asking for a password.
test: build
	@cd $(BUILD_DIR_32); PATH=/usr/gnu/bin:$(PATH) $(MAKE) localcheck

include ../../make-rules/depend.mk
