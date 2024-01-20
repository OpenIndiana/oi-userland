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

BUILD_STYLE = meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp-tools
COMPONENT_VERSION=	42.1
COMPONENT_VERSION_MAJOR=$(word 1,$(subst ., ,$(HUMAN_VERSION)))
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Yelp Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:3e496a4020d4145b99fd508a25fa09336a503a4e8900028421e72c6a4b11f905
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/gnome/$(COMPONENT_NAME)

TEST_TARGET =	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PYTHON_SCRIPTS += usr/bin/yelp-build
PYTHON_SCRIPTS += usr/bin/yelp-new
PYTHON_SCRIPTS += usr/bin/yelp-check

# Build dependencies
REQUIRED_PACKAGES += text/itstool
REQUIRED_PACKAGES += library/gnome/yelp-xsl

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/lxml
PYTHON_REQUIRED_PACKAGES += runtime/python
