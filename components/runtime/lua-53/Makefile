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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016. Adam Stevko. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			lua
COMPONENT_VERSION=		5.3.2
COMPONENT_SUMMARY=		Lua is a powerful, fast, lightweight, embeddable scripting language.
COMPONENT_PROJECT_URL=		https://www.lua.org/
COMPONENT_FMRI=			runtime/lua-53
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://www.lua.org/ftp/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:c740c7bb23a936944e1cc63b7c3c5351a8976d7867c5252c8854f7b2af9da68f
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=		$(COMPONENT_NAME).license

LUA_TESTS=              $(COMPONENT_NAME)-$(COMPONENT_VERSION)-tests
COMPONENT_ARCHIVE_1=    $(LUA_TESTS).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:56909863a3713dee3709b3dbd0c868237e4f5c9ea1744f5bf0ba8bafa6c4ed32
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)tests/$(COMPONENT_ARCHIVE_1)

CLEAN_PATHS += $(LUA_TESTS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# This is because lua uses $(CC) to build it's shared libraries.
CC +=           $(CC_BITS)

CFLAGS +=       $(CC_PIC) $(CPP_LARGEFILES)

# Original patch from userland-gate used LD_OPTIONS_SO and LD_OPTIONS directly in the src/Makefile
# of Lua SOURCE_DIR. This caused that gcc picked wrong linking flags and liblua.so would not be
# created. Till there is a better way, let's stick to this.
MYLDFLAGS= $(shell echo $(LD_OPTIONS_SO) $(LD_OPTIONS) | $(GSED) -e 's/^/-Wl,/g' -e 's/ /,'/g)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += MYCFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += MYLDFLAGS="$(MYLDFLAGS)"
COMPONENT_INSTALL_ARGS += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ARGS += INSTALL_TOP=$(PROTOUSRDIR)
$(INSTALL_64):  COMPONENT_INSTALL_ARGS += INSTALL_LIB=$(PROTOUSRLIBDIR64)
$(INSTALL_64):  COMPONENT_INSTALL_ARGS += INSTALL_BIN=$(PROTOUSRBINDIR64)

$(BUILD_DIR)/lua-64.pc:         files/lua-64.pc
		/bin/sed -e "s#MACH64#$(MACH64)#g" < $< > $@

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64) $(BUILD_DIR)/lua-64.pc

test:           install
		(gzip -dc $(USERLAND_ARCHIVES)$(LUA_TESTS).tar.gz | tar xopf -; \
		cd $(LUA_TESTS); $(ENV) LD_LIBRARY_PATH=$(PROTOUSRLIBDIR) \
		$(PROTOUSRBINDIR)/$(COMPONENT_NAME) -e"_U=true" all.lua; \
		$(ENV) LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64) \
		$(PROTOUSRBINDIR64)/$(COMPONENT_NAME) -e"_U=true" all.lua)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
