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

COMPONENT_NAME=		goaccess
COMPONENT_VERSION=	1.0.2
COMPONENT_SUMMARY=	GoAccess is an open source real-time web log analyzer and interactive viewer that runs in a terminal in *nix systems or through your browser.
COMPONENT_PROJECT_URL=	https://goaccess.io/
COMPONENT_FMRI=		web/goaccess
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://tar.goaccess.io/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:58a83e201f29f0127b89032fbd40677558a643f6141b8c8413afd1e182f104f1
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION= \
	$(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS+= --enable-geoip

CFLAGS+= -std=gnu99

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += database/geoip
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
