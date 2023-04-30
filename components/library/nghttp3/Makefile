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
# Copyright 2023 Friedrich Kink
#
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nghttp3
COMPONENT_VERSION=	0.11.0
COMPONENT_SUMMARY=	This library implements RFC 9114 HTTP/3. It does not support server push.
COMPONENT_PROJECT_URL=	https://nghttp2.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:dcd85fc092eab8e08021c286d87e40eb3539bbd133b437fcd70c2b9ff460a09f
COMPONENT_ARCHIVE_URL=	https://github.com/ngtcp2/nghttp3/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/nghttp3
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--disable-static

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/cunit

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
