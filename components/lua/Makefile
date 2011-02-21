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

COMPONENT_NAME=		lua
COMPONENT_VERSION=	5.1.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:2b11c8e60306efb7f0734b747588f57995493db7
COMPONENT_ARCHIVE_URL=	http://www.lua.org/ftp/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

CFLAGS +=-KPIC -D_FILE_OFFSET_BITS=64 

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_TARGETS += CC="$(CC)"
COMPONENT_BUILD_TARGETS += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_TARGETS += INSTALL_TOP=$(PROTOUSRDIR)

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32_and_64)

	
install:	build $(INSTALL_32)
		$(MKDIR) $(PROTOUSRDIR)/lib/pkgconfig
		$(CP) $(SOURCE_DIR)/etc/lua.pc $(PROTOUSRDIR)/lib/pkgconfig
		$(MKDIR) $(PROTOUSRLIBDIR64) 
		$(INSTALL) $(BUILD_DIR_64)/src/liblua.so $(PROTOUSRLIBDIR64)
		
test:  build
	@cd $(BUILD_DIR_32); $(MAKE) check
	@cd $(BUILD_DIR_64); $(MAKE) check

		
BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk

