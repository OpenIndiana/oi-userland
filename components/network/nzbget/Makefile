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
# Copyright 2021 erwinlem
#

BUILD_BITS=64
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nzbget
COMPONENT_VERSION=	21.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	Binary newsreader supporting NZB files
COMPONENT_PROJECT_URL=	https://nzbget.net
COMPONENT_FMRI=		network/nzbget
COMPONENT_CLASSIFICATION=
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/nzbget/nzbget/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:4e8fc1beb80dc2af2d6a36a33a33f44dedddd4486002c644f4c4793043072025	
COMPONENT_LICENSE=	GPL-2.0 License
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV +=	MAKE=$(GMAKE)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
