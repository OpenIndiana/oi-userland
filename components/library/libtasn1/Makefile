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
# Copyright 2015 Alexander Pyhalov
# Copyright 2025 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libtasn1
COMPONENT_VERSION= 4.20.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Tiny ASN.1 library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:92e0e3bd4c02d4aeee76036b2ddd83f0c732ba4cda5cb71d583272b23587a76c
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libtasn1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnu.org/software/libtasn1/
COMPONENT_FMRI= library/libtasn1
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = Library is LGPLv2.1, binaries are GPLv3

COMPONENT_FMRI.$(COMPONENT_NAME)-32 = 		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# Remove info/dir
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
