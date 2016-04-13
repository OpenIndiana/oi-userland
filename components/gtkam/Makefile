#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkam
COMPONENT_VERSION=	0.1.18
# Version was bumped in JDS
GIMP_GTKAM_VERSION=	2.30.0
COMPONENT_PROJECT_URL=	http://libexif.sourceforge.net/
COMPONENT_SUMMARY=	A GTK Digital Camera Viewing Tool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:01aa8afa9e96195355ad39083806708a097a04c885dbc26b3ca881767edabc0c
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/gphoto/files/gtkam/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging
COMPONENT_FMRI = desktop/gtkam
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PKG_MACROS += GIMP_GTKAM_VERSION=$(GIMP_GTKAM_VERSION)

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
