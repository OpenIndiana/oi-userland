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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nzbget
COMPONENT_VERSION=	22.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Binary newsreader supporting NZB files
COMPONENT_PROJECT_URL=	https://nzbget.com
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/nzbgetcom/nzbget/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2bec63a0c5c0fed0779adca488499f890f603dcc8f161ae6bcff62e866b1d24b
COMPONENT_FMRI=		network/nzbget
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPL-2.0 License
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_BUILD_ARGS=	-j50

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += MAKE=$(GMAKE)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
