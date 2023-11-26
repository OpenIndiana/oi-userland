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
# Copyright 2017 Gary Mills
# Copyright 2016 Till Wegmueller
# Copyright 2023 Friedrich Kink
#

BUILD_BITS =    NO_ARCH

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp-xsl
COMPONENT_VERSION=	3.38.3
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Yelp Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:193b6abd4697b7b421e98c36d4d3135da0b0fdb51aa53e602ed368dd84d1fd03
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.38/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/gnome/$(COMPONENT_NAME)

TEST_TARGET =   $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/$(COMPONENT_NAME)

# Build dependencies
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
