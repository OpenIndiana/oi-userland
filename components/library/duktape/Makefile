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

# Duktape: small embeddable JavaScript engine.  Here it is polkit's rules
# engine (polkit -Djs_engine=duktape), so polkit needs no mozjs.
# Upstream ships a plain Makefile for the shared library; no configure.

BUILD_BITS=		64
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
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

# Upstream has no test suite in the distribution tarball.
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# The upstream Makefile builds in the source tree: build in a copy.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Makefile.sharedlibrary: libduktape.so.207.20700 (+ a -g variant,
# libduktaped, which we drop) and duktape.pc.  duktape.c uses libm
# (floor, fmod, pow, ...): link it in so users need not add -lm.
DUK_MAKE_ARGS =		-f Makefile.sharedlibrary
DUK_MAKE_ARGS +=	CC="$(CC)"
DUK_MAKE_ARGS +=	CFLAGS="$(CFLAGS)"
DUK_MAKE_ARGS +=	LDFLAGS="$(LDFLAGS) -lm"
DUK_MAKE_ARGS +=	INSTALL_PREFIX=$(USRDIR)
DUK_MAKE_ARGS +=	LIBDIR=/lib/$(MACH64)

COMPONENT_BUILD_ARGS +=		$(DUK_MAKE_ARGS)
COMPONENT_BUILD_TARGETS =	libduktape.so.207.20700 duktape.pc
COMPONENT_INSTALL_ARGS +=	$(DUK_MAKE_ARGS)

COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTOUSRLIBDIR64)/libduktaped.* ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
