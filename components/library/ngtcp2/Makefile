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

COMPONENT_NAME=		ngtcp2
COMPONENT_VERSION=	1.0.1
COMPONENT_SUMMARY=	ngtcp2 project is an effort to implement RFC9000 QUIC protocol
COMPONENT_PROJECT_URL=	https://ngtcp2.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:21c898fa5543d3f2dc203fd0a300a8a7cb70fec21ad7f7a3ec6e119ba4850451
COMPONENT_ARCHIVE_URL=	https://github.com/ngtcp2/ngtcp2/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/ngtcp2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# for some reason SPARC needs libsocket, to compile the examples directory.
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_ENV += LIBS="-lsocket"
endif

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-gnutls

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/cunit
# According to the documentation the following packages are needed to build the examples:
REQUIRED_PACKAGES += library/libev
REQUIRED_PACKAGES += library/nghttp3

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library
