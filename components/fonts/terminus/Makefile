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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2019 Michal Nowak
#
BUILD_BITS=			32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminus-font
COMPONENT_VERSION_MAJOR=4.49
COMPONENT_VERSION_MINOR=1
COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_PROJECT_URL=	https://terminus-font.sourceforge.net/
COMPONENT_SUMMARY=	Terminus Font
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:d961c1b781627bf417f9b340693d64fc219e0113ad3a3af1a3424c7aa373ef79
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/terminus-font/files/$(COMPONENT_NAME)-$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		system/font/terminus
COMPONENT_LICENSE_FILE=	terminus.license
COMPONENT_LICENSE=	OFL
COMPONENT_CLASSIFICATION=	System/Fonts

CONFIGURE_DEFAULT_DIRS=	no

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS =  --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --x11dir=$(CONFIGURE_PREFIX)/share/fonts/X11/terminus

COMPONENT_BUILD_TARGETS = pcf
COMPONENT_INSTALL_TARGETS = install-pcf

COMPONENT_PRE_CONFIGURE_ACTION=$(CLONEY) $(SOURCE_DIR) $(@D)

# Build dependencies
REQUIRED_PACKAGES+= x11/bdftopcf
