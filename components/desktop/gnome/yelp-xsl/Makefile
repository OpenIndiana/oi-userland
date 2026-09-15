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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE = meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         yelp-xsl
COMPONENT_VERSION=      49.0
COMPONENT_VERSION_MAJOR=$(word 1,$(subst ., ,$(HUMAN_VERSION)))
COMPONENT_SUMMARY=      The GNOME Help Browser
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:59d43a8f8fe67b784f14f9a04dd4a7a092a7f4a64a65e71b90fe02a47a50fbec
COMPONENT_ARCHIVE_URL=  \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_FMRI=         library/gnome/yelp-xsl
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Documentation
COMPONENT_LICENSE=      BSD-3-Clause AND GPL-2.0-or-later AND LGPL-2.1-or-later
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# configure expects GNU make in PATH
PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += -Ddita=true

# Auto-generated dependencies
