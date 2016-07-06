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
COMPONENT_VERSION=	0.1
COMPONENT_SUMMARY=	fast, standalone, language-agnostic WebSocket server RFC6455 compliant
COMPONENT_PROJECT_URL=	http://gwsocket.io/
COMPONENT_FMRI=		web/gwsocket
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/allinurl/gwsocket/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:26894e568898d416c41440b14fd1482d2a0774471ebf9677a2a429a0da0f5961
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION= \
	(cd $(SOURCE_DIR) && autoreconf -vif)

LDFLAGS+= -lsocket
LDFLAGS+= -lnsl

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += system/library
