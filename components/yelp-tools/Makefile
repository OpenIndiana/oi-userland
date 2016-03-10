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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp-tools
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Tools that help you create, edit, manage, and publish your Mallard or DocBook documentation
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c6c1d65f802397267cdc47aafd5398c4b60766e0a7ad2190426af6c0d0716932
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	test/yelp-tools
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	yelp-tools.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
