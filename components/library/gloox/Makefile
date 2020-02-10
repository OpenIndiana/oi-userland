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
# Copyright 2020 Jim Klimov
#

BUILD_BITS =			64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gloox
COMPONENT_VERSION=		1.0.23
COMPONENT_SUMMARY=		$(COMPONENT_NAME) - Jabber/XMPP client library, written in clean ANSI C++
COMPONENT_PROJECT_URL=	https://camaya.net/$(COMPONENT_NAME)/
# PR TODO: Taxonomy
COMPONENT_FMRI=			library/libgloox
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
	https://camaya.net/download/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:97cb6a0c07e320ffa4a7c66e8ab06b2361086271dc87ed2398befef4e8435f8a
COMPONENT_LICENSE=		GPLv3
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D); autoreconf --install --force )

CONFIGURE_OPTIONS += --enable-mdns

# For now drop this: self-tests say
#    GnuTLS error: No or insufficient priorities were set.
# and probably production code would not connect either.
#REQUIRED_PACKAGES += library/gnutls-3
CONFIGURE_OPTIONS += --without-gnutls

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-$(GCC_VERSION)-runtime
REQUIRED_PACKAGES += system/library/g++-$(GCC_VERSION)-runtime
