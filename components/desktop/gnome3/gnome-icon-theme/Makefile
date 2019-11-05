##
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
# Copyright (c) 2014 Ken Mays
# Copyright (c) 2018 Michal Nowak
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnome-icon-theme
COMPONENT_VERSION=      3.12.0
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_SUMMARY=      GNOME Icon Themes 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:359e720b9202d3aba8d477752c4cd11eced368182281d51ffd64c8572b4e503a
COMPONENT_ARCHIVE_URL=  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.12/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/theme/gnome-icon-theme

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/desktop/xdg/icon-naming-utils
