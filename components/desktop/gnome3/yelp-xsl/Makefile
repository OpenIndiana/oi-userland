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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp-xsl
COMPONENT_VERSION=	42.1
COMPONENT_VERSION_MAJOR=$(word 1,$(subst ., ,$(HUMAN_VERSION)))
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Yelp Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:238be150b1653080ce139971330fd36d3a26595e0d6a040a2c030bf3d2005bcd
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-2.0-only AND LGPL-2.1-only AND BSD-3-Clause
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/gnome/$(COMPONENT_NAME)

TEST_TARGET =   $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+=	--localstatedir=$(VARDIR)/lib
CONFIGURE_OPTIONS+=	--libexecdir=$(USRLIBDIR)/$(COMPONENT_NAME)

# Build dependencies
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
