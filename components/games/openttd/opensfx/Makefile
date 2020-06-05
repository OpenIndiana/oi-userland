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
# Copyright 2016 Jim Klimov <jimklimov@gmail.com>
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		opensfx
COMPONENT_VERSION=	0.2.3
COMPONENT_PROJECT_URL=	http://dev.openttdcoop.org/projects/$(COMPONENT_NAME)
COMPONENT_FMRI=		games/openttd/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-all.zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:6831b651b3dc8b494026f7277989a1d757961b67c17b75d3c2e097451f75af02
COMPONENT_ARCHIVE_URL=	https://binaries.openttd.org/extra/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	Opensource sound set for OpenTTD
COMPONENT_CLASSIFICATION="Applications/Games"

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_PREFIX=/usr

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

OPENTTD_SHARE_DIR=$(CONFIGURE_PREFIX)/share/openttd
PKG_OPTIONS +=	-D OPENTTD_SHARE_DIR="$(OPENTTD_SHARE_DIR)"
PKG_OPTIONS +=	-D COMPONENT_SRC="$(COMPONENT_SRC)"

build: prep
install: build
