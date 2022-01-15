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
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=             64
BUILD_STYLE=            configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		c_icap_modules
COMPONENT_VERSION=	0.5.5
COMPONENT_SUMMARY=	An antivirus services for the c-icap ICAP server
COMPONENT_FMRI= 	antivirus/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6a42f1fdd8c35ad38d29f7d3c10f925471977f217086352e146cf95e45f2b5b5
COMPONENT_PROJECT_URL=	http://c-icap.sourceforge.net/
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/c-icap/files/c-icap-modules/0.5.x/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += antivirus/c_icap
REQUIRED_PACKAGES += antivirus/clamav-core
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += system/library
