#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Marcel Telka
#

USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			fakeroot
COMPONENT_VERSION=		1.31
COMPONENT_SUMMARY=		Tool for simulating superuser privileges
COMPONENT_PROJECT_URL=		https://tracker.debian.org/pkg/fakeroot
COMPONENT_FMRI=			developer/fakeroot
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		http://deb.debian.org/debian/pool/main/f/$(COMPONENT_NAME)/$(COMPONENT_NAME)_$(COMPONENT_VERSION).orig.tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:63886d41e11c56c7170b9d9331cca086421b350d257338ef14daad98f77e202f
COMPONENT_LICENSE=		GPL-3.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU tools
PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
