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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jansson
COMPONENT_VERSION=	2.14.1
COMPONENT_SUMMARY=	C library for encoding, decoding and manipulating JSON data
COMPONENT_PROJECT_URL=	https://www.digip.org/jansson
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/akheron/jansson/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:2521cd51a9641d7a4e457f7215a4cd5bb176f690bc11715ddeec483e85d9e2b3
COMPONENT_FMRI=		library/jansson
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/jansson
CONFIGURE_OPTIONS += --disable-static

# The test/suites/api/check-exports uses nm and expects it to be the GNU kind.
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
