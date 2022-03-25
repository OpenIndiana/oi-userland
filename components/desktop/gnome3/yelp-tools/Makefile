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
# Copyright 2016 Till Wegmueller
#

BUILD_BITS =	NO_ARCH

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp-tools
COMPONENT_VERSION=	3.18.0
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Yelp Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c6c1d65f802397267cdc47aafd5398c4b60766e0a7ad2190426af6c0d0716932
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/gnome/$(COMPONENT_NAME)

TEST_TARGET =	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/$(COMPONENT_NAME)

REQUIRED_PACKAGES += text/itstool
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/gnome/yelp-xsl
REGUIRED_PACKAGES += text/gawk

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
