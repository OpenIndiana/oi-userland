#! /usr/bin/sh
#
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
# Copyright 2014 Andrzej Szeszo.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		evince
COMPONENT_VERSION=	2.30.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:daddd9720bf8fc0156d9a4a5a85485c232393896376707cf7fcedfcbc515732f
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnome.org/pub/GNOME/sources/evince/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Evince
COMPONENT_AUTOGEN_MANIFEST=	yes
COMPONENT_FMRI=		desktop/pdf-viewer/evince
COMPONENT_SUMMARY=	GNOME PDF document viewer
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION += \
    cd $(@D); autoreconf --install --force

# For GNU gettext
CONFIGURE_ENV += PATH=/usr/gnu/bin:$(PATH)

build:		$(BUILD_32)

install:	$(INSTALL_32)
