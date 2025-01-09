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
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gwsocket
COMPONENT_VERSION=	0.4
COMPONENT_SUMMARY=	fast, standalone, language-agnostic WebSocket server RFC6455 compliant
COMPONENT_PROJECT_URL=	https://gwsocket.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/allinurl/gwsocket/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:328f1d5a141568a5093cef1167bc77d2a0b763ccb4b05d068049f87eaa73d32b
COMPONENT_FMRI=		web/gwsocket
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( cd $(SOURCE_DIR) && autoreconf -vif )

LDFLAGS += -lsocket
LDFLAGS += -lnsl

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
