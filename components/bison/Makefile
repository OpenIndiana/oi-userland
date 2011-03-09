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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bison
COMPONENT_VERSION=	2.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:4df84c2c5971946111ff1982fb830b3c78d7c57e
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/bison/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_LIBDIR.32 =   $(SFWLIB)
CONFIGURE_LIBDIR.64 =   $(SFWLIB)/$(MACH64)

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

SFWPROGS=	bison

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32) $(BUILD_64)

install:	build $(INSTALL_32) $(PROTOSFWLINKS)
	cd $(PROTOSFWLIB); rm -f liby.so; ln -s liby.so.1 liby.so
	$(INSTALL) -D $(BUILD_DIR_64)/lib/liby.so.1 $(PROTOSFWLIB64)/liby.so.1
	cd $(PROTOSFWLIB64); rm -f liby.so; ln -s liby.so.1 liby.so

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

include ../../make-rules/depend.mk
