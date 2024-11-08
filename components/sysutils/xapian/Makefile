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
# Copyright 2024, Friedich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xapian
COMPONENT_VERSION=	1.4.26
COMPONENT_FMRI=		library/xapian
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	Xapian is an Open Source Search Engine Library
COMPONENT_SRC=		$(COMPONENT_NAME)-core-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:9e6a7903806966d16ce220b49377c9c8fad667c8f0ffcb23a3442946269363a7  
COMPONENT_PROJECT_URL=	https://xapian.org
COMPONENT_ARCHIVE_URL=	https://oligarchy.co.uk/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk


CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --enable-64bit-docid
CONFIGURE_OPTIONS += --enable-64bit-termcount
CONFIGURE_OPTIONS += --enable-64bit-termpos

COMPONENT_TEST_ARGS += -k
COMPONENT_TEST_TRANSFORMS = \
        '-n ' \
        '-e "/^PASS:/p" ' \
        '-e "/^FAIL:/p" ' \
        '-e "/^XFAIL:/p" ' \
        '-e "/^Running test:/p" ' \
        '-e "/\.\/apitest/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
