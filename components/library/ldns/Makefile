#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# Copyright (c) 2016, Adam Stevko <adam.stevko@gmail.com>
# Copyright (c) 2021, Andreas Wacknitz

BUILD_BITS= 32_and_64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ldns
COMPONENT_VERSION=	1.7.1
COMPONENT_SUMMARY=	ldns is a library to simplify DNS programming
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8ac84c16bdca60e710eea75782356f3ac3b55680d40e1530d7cea474ac208229
COMPONENT_PROJECT_URL=	https://www.nlnetlabs.nl/projects/ldns/
COMPONENT_ARCHIVE_URL=	https://www.nlnetlabs.nl/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_FMRI=		library/dns/ldns
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	ldns.license

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for tests without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=    --with-examples
CONFIGURE_OPTIONS +=    --with-drill
CONFIGURE_OPTIONS +=	--disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
