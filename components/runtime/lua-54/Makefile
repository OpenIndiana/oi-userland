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
# Copyright (c) 2020, Andreas Wacknitz
# Copyright (c) 2023, Friedrich Kink
#

BUILD_STYLE=	justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			lua
COMPONENT_MJR_VERSION=	5.4
COMPONENT_MNR_VERSION=	6
COMPONENT_VERSION=		$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=		Lua is a powerful, fast, lightweight, embeddable scripting language.
COMPONENT_PROJECT_URL=	https://www.lua.org/
COMPONENT_FMRI=			runtime/lua-54
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://www.lua.org/ftp/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

LUA_TESTS=              $(COMPONENT_NAME)-$(COMPONENT_VERSION)-tests
COMPONENT_ARCHIVE_1=    $(LUA_TESTS).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:63ed5f5bcfd15dfd2f72e04c2f8c10585bb8de9e558df62b335cb9e5c1a4ef34
COMPONENT_ARCHIVE_URL_1= $(COMPONENT_PROJECT_URL)tests/$(COMPONENT_ARCHIVE_1)

CLEAN_PATHS += $(LUA_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_TARGETS= solaris

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
$(INSTALL_64):  COMPONENT_INSTALL_ARGS += INSTALL_BIN=$(PROTOUSRBINDIR)

$(TEST_64):     install
		(gzip -dc $(USERLAND_ARCHIVES)$(LUA_TESTS).tar.gz | tar xopf -; \
		cd $(LUA_TESTS); $(ENV) LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64) \
		$(PROTOUSRBINDIR)/$(COMPONENT_NAME)$(COMPONENT_MJR_VERSION) -e"_U=true" all.lua)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
