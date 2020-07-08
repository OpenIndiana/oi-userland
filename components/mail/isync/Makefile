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
# Copyright 2020, Andreas Wacknitz <a.wacknitz@gmx.de>
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			isync
COMPONENT_VERSION=		1.3.2
COMPONENT_FMRI=			mail/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL=	https://$(COMPONENT_NAME).sourceforge.net
COMPONENT_SUMMARY=		isync is a command line application which synchronizes mailboxes
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:9106d1428c912f421a659a22c3c4dbe9fe110f3f4da1498038e6ebf8d284e805
COMPONENT_ARCHIVE_URL= \
	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
