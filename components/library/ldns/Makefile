#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# Copyright (c) 2016, Adam Stevko <adam.stevko@gmail.com>

BUILD_STYLE=configure
BUILD_BITS=32_and_64
USE_OPENSSL11=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ldns
COMPONENT_VERSION=      1.6.17
COMPONENT_REVISION=     2
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8b88e059452118e8949a2752a55ce59bc71fa5bc414103e17f5b6b06f9bcc8cd
COMPONENT_PROJECT_URL=  http://www.nlnetlabs.nl/projects/ldns/
COMPONENT_ARCHIVE_URL=  http://www.nlnetlabs.nl/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for tests without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=    --with-examples
CONFIGURE_OPTIONS +=    --with-drill
CONFIGURE_OPTIONS +=	--disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
