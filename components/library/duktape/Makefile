#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		duktape
COMPONENT_VERSION=	2.7.0
COMPONENT_PROJECT_URL=	https://duktape.org/
COMPONENT_SUMMARY=	Duktape - embeddable JavaScript engine
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:90f8d2fa8b5567c6899830ddef2c03f3c27960b11aca222fa17aa7ac613c2890
COMPONENT_ARCHIVE_URL=	https://github.com/svaarala/duktape/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/duktape
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE.txt

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# duktape.c uses libm
LDFLAGS +=		-lm

DUK_MAKE_ARGS =		-f Makefile.sharedlibrary
DUK_MAKE_ARGS +=	INSTALL_PREFIX=$(USRDIR)
# LIBDIR needs to be relative to INSTALL_PREFIX
DUK_MAKE_ARGS +=	LIBDIR=$(USRLIBDIR.$(BITS):$(USRDIR)%=%)

COMPONENT_BUILD_ARGS +=		$(DUK_MAKE_ARGS)
COMPONENT_INSTALL_ARGS +=	$(DUK_MAKE_ARGS)

# We do not need the debug variant of the library
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTOUSRLIBDIR.$(BITS))/libduktaped.* ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
