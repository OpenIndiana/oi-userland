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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		http-parser
COMPONENT_VERSION=	2.6.2
COMPONENT_REVISION=     3
COMPONENT_FMRI=		library/http-parser
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	https://github.com/nodejs/http-parser
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:80fffc3b64ef6968cecdd4b299a96986007dff4bd12ae6c58cbcb506959b90ad
COMPONENT_ARCHIVE_URL=	https://github.com/nodejs/http-parser/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=      A parser for HTTP messages written in C

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_TARGETS= test

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CC_BITS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LD_BITS)"

COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ENV += PREFIX="$(PROTOUSRDIR)"
COMPONENT_INSTALL_ENV.32 += LIBDIR="$(PROTOUSRLIBDIR)"
COMPONENT_INSTALL_ENV.64 += LIBDIR="$(PROTOUSRLIBDIR64)"
COMPONENT_INSTALL_ENV += LDFLAGS="$(LD_BITS)"
COMPONENT_INSTALL_ENV += CFLAGS="$(CC_BITS)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
