#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2021 Klaus Ziegler
#

BUILD_BITS= 64
BUILD_STYLE= cmake
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libzip
COMPONENT_VERSION=	1.10.1
COMPONENT_SUMMARY=	A C library for reading, creating, and modifying zip archives
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://libzip.org/
COMPONENT_ARCHIVE_HASH=	sha256:dc3c8d5b4c8bbd09626864f6bcf93de701540f761d76b85d7c7d710f4bd90318
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=		library/libzip
COMPONENT_LICENSE=	BSD 3-clause
COMPONENT_LICENSE_FILE=	LICENSE

# We are lackaing nihtest (INSTALL.md mentions the test prerequisites):
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9. ]*sec//g"'

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/cmake/libzip ; \
	$(CP) files/* $(PROTOUSRLIBDIR)/cmake/libzip ; \
	sed -e "s@MACH64_1@$(MACH64_1)@g" $(PROTOUSRLIBDIR)/cmake/libzip/libzip-targets-noconfig.cmake > /tmp/libzip.$$ ; \
	$(MV) /tmp/libzip.$$ $(PROTOUSRLIBDIR)/cmake/libzip/libzip-targets-noconfig.cmake

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
