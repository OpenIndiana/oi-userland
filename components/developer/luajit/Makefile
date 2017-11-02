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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= luajit
COMPONENT_VERSION= 2.0.5
COMPONENT_SUMMARY= LuaJIT - Just-In-Time Compiler (JIT) for the Lua programming language 
COMPONENT_PROJECT_URL= http://luajit.org/
COMPONENT_FMRI= developer/luajit
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC_NAME=	LuaJIT
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= http://luajit.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:874b1f8297c697821f561f9b73b57ffd419ed8f4278c82e05b48806d30c1e979
COMPONENT_LICENSE= MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+= -fPIC

COMPONENT_BUILD_ARGS+= PREFIX=$(USRDIR) 
COMPONENT_BUILD_ARGS+= CC=$(CC) 
COMPONENT_BUILD_ARGS+= CFLAGS="$(CFLAGS)" 
COMPONENT_BUILD_ARGS+= LDFLAGS="$(LDFLAGS)" 
COMPONENT_BUILD_ARGS+= MULTIBIN=bin/$(ARCHLIBSUBDIR)
COMPONENT_BUILD_ARGS+= MULTILIB=lib/$(ARCHLIBSUBDIR)

COMPONENT_INSTALL_ARGS+= PREFIX=$(USRDIR) 
COMPONENT_INSTALL_ARGS+= DESTDIR=$(PROTO_DIR) 
COMPONENT_INSTALL_ARGS+= MULTIBIN=bin/$(ARCHLIBSUBDIR)
COMPONENT_INSTALL_ARGS+= MULTILIB=lib/$(ARCHLIBSUBDIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += runtime/lua
