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
# Copyright 2016 Denys Rtveliashvili.  All rights reserved.
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=			32_and_64
BUILD_STYLE=		justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		http-parser
COMPONENT_VERSION=	2.9.4
COMPONENT_FMRI=		library/http-parser
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	https://github.com/nodejs/http-parser
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:467b9e30fd0979ee301065e70f637d525c28193449e1b13fbcb1b1fab3ad224f
COMPONENT_ARCHIVE_URL=	https://github.com/nodejs/http-parser/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=      A parser for HTTP messages written in C

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS= test

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CC_BITS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LD_BITS)"
COMPONENT_BUILD_ENV.32 += LIBDIR="$(USRLIBDIR)"
COMPONENT_BUILD_ENV.64 += LIBDIR="$(USRLIBDIR64)"

COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += LDFLAGS="$(LD_BITS)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CC_BITS)"
COMPONENT_INSTALL_ENV += PREFIX="$(USRDIR)"
COMPONENT_INSTALL_ENV.32 += LIBDIR="$(USRLIBDIR)"
COMPONENT_INSTALL_ENV.64 += LIBDIR="$(USRLIBDIR64)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
