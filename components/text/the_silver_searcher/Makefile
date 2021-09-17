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
# Copyright (c) 2021 Andreas Wacknitz
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		the_silver_searcher
COMPONENT_VERSION=	2.2.0
COMPONENT_PROJECT_URL=	https://geoff.greer.fm/ag/
COMPONENT_SUMMARY=	A code searching tool similar to ack, with a focus on speed.
COMPONENT_FMRI=         text/the_silver_searcher
COMPONENT_CLASSIFICATION=       Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d9621a878542f3733b5c6e71c849b9d1a830ed77cb1a1f6c2ea441d4b0643170
COMPONENT_ARCHIVE_URL=	https://geoff.greer.fm/ag/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Apache-2.0

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
