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

COMPONENT_NAME=		libgit2
COMPONENT_VERSION=	0.23.4
COMPONENT_FMRI=		library/libgit2
COMPONENT_CLASSIFICATION=Development/Source Code Management
COMPONENT_PROJECT_URL=	https://libgit2.github.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1b974f525b7dd10028e4473e2efce991d56e200dae5c0c7bdd98ad11e55eb879
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPLv2 with Linking Exception
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Portable implementation of the Git core methods provided as a library

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS +=	-DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS +=	-DBIN_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DLIB_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DCMAKE_BUILD_TYPE=Release
COMPONENT_TEST_CMD =    ctest
COMPONENT_TEST_ARGS =   -V
COMPONENT_TEST_TARGETS = ""

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/http-parser
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
