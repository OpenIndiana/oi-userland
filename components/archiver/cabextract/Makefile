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
# Copyright 2011, EveryCity Ltd. All rights reserved.
# Copyright 2013, Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cabextract
COMPONENT_VERSION=	1.6
COMPONENT_SUMMARY=	cabextract - extract Microsoft cabinet files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cee661b56555350d26943c5e127fc75dd290b7f75689d5ebc1f04957c4af55fb
COMPONENT_PROJECT_URL=	http://www.cabextract.org.uk/
COMPONENT_ARCHIVE_URL=	http://www.cabextract.org.uk/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	archiver/cabextract
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64=/usr/bin

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTSI)

REQUIRED_PACKAGES += system/library
