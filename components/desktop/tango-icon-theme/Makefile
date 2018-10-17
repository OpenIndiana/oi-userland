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

COMPONENT_NAME=         tango-icon-theme
COMPONENT_VERSION=      0.8.90
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=  http://tango.freedesktop.org/
COMPONENT_SUMMARY=      Tango icon theme
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:e94004fa9aa6a7250ac4db6180e96f9c147db617c0d8e7fc8c9e2c42924e990c
COMPONENT_ARCHIVE_URL=  http://tango.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_FMRI=	gnome/theme/tango-icon-theme
COMPONENT_LICENSE=	PublicDomain
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

