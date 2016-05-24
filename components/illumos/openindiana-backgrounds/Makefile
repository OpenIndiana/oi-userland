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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openindiana-backgrounds
COMPONENT_VERSION=	0.1.1
IPS_COMPONENT_VERSION=	1.0
COMPONENT_PROJECT_URL=	http://openindiana.org
COMPONENT_SUMMARY=	Selection of OpenIndiana backgrounds for the GNOME desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:3435a7a2ab1506629b2b9ee65232f66ea9b03d355006773b9abb65a316811a97
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	gnome/theme/background/os-backgrounds
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
