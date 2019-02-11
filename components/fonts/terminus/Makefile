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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminus-font
COMPONENT_VERSION=	4.47
COMPONENT_PROJECT_URL=	https://terminus-font.sourceforge.net/
COMPONENT_SUMMARY=	Terminus Font
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:0f1b205888e4e26a94878f746b8566a65c3e3742b33cf9a4e6517646d5651297
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/terminus-font/files/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		system/font/terminus
COMPONENT_LICENSE_FILE=	terminus.license
COMPONENT_LICENSE=	OFL
COMPONENT_CLASSIFICATION=	System/Fonts

CONFIGURE_DEFAULT_DIRS=	no

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS =  --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --x11dir=$(CONFIGURE_PREFIX)/share/fonts/X11/terminus

COMPONENT_BUILD_TARGETS = pcf
COMPONENT_INSTALL_TARGETS = install-pcf

COMPONENT_PRE_CONFIGURE_ACTION=$(CLONEY) $(SOURCE_DIR) $(@D)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES+= x11/bdftopcf
