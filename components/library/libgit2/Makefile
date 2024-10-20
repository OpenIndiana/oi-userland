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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgit2
COMPONENT_VERSION=	1.8.2
COMPONENT_SUMMARY=	Portable implementation of the Git core methods provided as a library
COMPONENT_PROJECT_URL=	https://libgit2.github.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:184699f0d9773f96eeeb5cb245ba2304400f5b74671f313240410f594c566a28
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/libgit2
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_LICENSE=	GPLv2 with Linking Exception
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DBIN_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DLIB_INSTALL_DIR=/usr/$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
