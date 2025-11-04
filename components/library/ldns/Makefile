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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ldns
COMPONENT_VERSION=      1.8.4
COMPONENT_SUMMARY=		The goal of ldns is to simplify DNS programming in C
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:838b907594baaff1cd767e95466a7745998ae64bc74be038dccc62e2de2e4247
COMPONENT_PROJECT_URL=  https://www.nlnetlabs.nl/projects/ldns/
COMPONENT_ARCHIVE_URL=  https://www.nlnetlabs.nl/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/dns/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=		BSD
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(OPENSSL_INCDIR)
CFLAGS += $(XPG7MODE)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

# Missing files in build dir for tests without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --with-examples
CONFIGURE_OPTIONS += --with-drill
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
