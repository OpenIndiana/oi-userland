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

USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jansson
COMPONENT_VERSION=	2.15.0
COMPONENT_SUMMARY=	C library for encoding, decoding and manipulating JSON data
COMPONENT_PROJECT_URL=	https://www.digip.org/jansson
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/akheron/jansson/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:070a629590723228dc3b744ae90e965a569efb9c535b3309b52e80e75d8eb3be
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
