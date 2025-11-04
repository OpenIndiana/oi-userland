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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2023 Andreas Wacknitz
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         desktop-file-utils
COMPONENT_VERSION=      0.28
COMPONENT_SUMMARY=      A few command line utilities for working with desktop entries
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/desktop-file-utils/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:4401d4e231d842c2de8242395a74a395ca468cd96f5f610d822df33594898a70
COMPONENT_ARCHIVE_URL=  https://www.freedesktop.org/software/desktop-file-utils/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/desktop/desktop-file-utils
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Scripts
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_INSTALL_ACTION= ($(RM) $(PROTOUSRBINDIR)/desktop-file-edit)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
