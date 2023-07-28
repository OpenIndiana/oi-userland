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
# Copyright 2023 Niklas Poslovski
#
#USE_DEFAULT_TEST_TRANSFORMS=	yes
BUILD_STYLE=		cmake
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgit2
COMPONENT_VERSION=	1.7.0
COMPONENT_SUMMARY=	Portable implementation of the Git core methods provided as a library
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_PROJECT_URL=	https://libgit2.github.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d9d0f84a86bf98b73e68997f5c1543cc5067d0ca9c7a5acaba3e8d117ecefef3
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/libgit2
COMPONENT_LICENSE=	GPLv2 with Linking Exception
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS +=	-DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS +=	-DBIN_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DLIB_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS +=	-DCMAKE_BUILD_TYPE=Release

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
