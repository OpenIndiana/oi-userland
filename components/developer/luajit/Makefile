#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Aurelien Larcher
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64_and_32
BUILD_STYLE= justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= luajit
COMPONENT_VERSION= 2.1.ROLLING
HUMAN_VERSION= 2.1.0
COMPONENT_SUMMARY= LuaJIT - Just-In-Time Compiler (JIT) for the Lua programming language 
COMPONENT_PROJECT_URL= http://luajit.org/
COMPONENT_FMRI= developer/luajit
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC_NAME=	LuaJIT
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/$(COMPONENT_SRC_NAME)/$(COMPONENT_SRC_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:31d7a4853df4c548bf91c13d3b690d19663d4c06ae952b62606c8225d0b410ad
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS+= PREFIX=$(USRDIR) 
COMPONENT_BUILD_ARGS+= CC=$(CC) 
COMPONENT_BUILD_ARGS+= CFLAGS="$(CFLAGS)" 
COMPONENT_BUILD_ARGS+= LDFLAGS="$(LDFLAGS)" 
COMPONENT_BUILD_ARGS+= MULTIBIN=bin
COMPONENT_BUILD_ARGS.32+= MULTILIB=lib
COMPONENT_BUILD_ARGS.64+= MULTILIB=lib/$(MACH64)

COMPONENT_INSTALL_ARGS+= PREFIX=$(USRDIR) 
COMPONENT_INSTALL_ARGS+= DESTDIR=$(PROTO_DIR) 
COMPONENT_INSTALL_ARGS+= MULTIBIN=bin
COMPONENT_INSTALL_ARGS.32+= MULTILIB=lib
COMPONENT_INSTALL_ARGS.64+= MULTILIB=lib/$(MACH64)

TEST_TARGET=		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/lua
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
