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
COMPONENT_VERSION=	1.0
COMPONENT_REVISION= 2
COMPONENT_PROJECT_URL=	https://github.com/OpenIndiana/openindiana-backgrounds
COMPONENT_SUMMARY=	Selection of OpenIndiana backgrounds for the desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:41ba81106998b4e322463590a21b0cd96300703bef07901f40461132bb884adc
COMPONENT_ARCHIVE_URL= \
  https://github.com/OpenIndiana/openindiana-backgrounds/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=	gnome/theme/background/os-backgrounds
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= (cd $(@D); sh autogen.sh)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated contents below.  Please manually verify and remove this comment
