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
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		the_silver_searcher
COMPONENT_VERSION=	0.31.0
COMPONENT_PROJECT_URL=	http://geoff.greer.fm/ag/
COMPONENT_SUMMARY=	A code searching tool similar to ack, with a focus on speed.
COMPONENT_FMRI=         text/the_silver_searcher
COMPONENT_CLASSIFICATION=       Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2b556d61a702d04e2638532aba08bccf178523b6a38464a25305563581823271
COMPONENT_ARCHIVE_URL=	http://geoff.greer.fm/ag/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	ASL-2
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
