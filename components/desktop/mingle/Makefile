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
# Copyright (c) 2024 Geoff Weiss
#

BUILD_BITS= 64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mingle
COMPONENT_VERSION=      0.15
COMPONENT_SUMMARY=      Simple GTK4-Libadwaita app to play with Google's Emoji Kitchen
COMPONENT_PROJECT_URL=  https://github.com/halfmexican/mingle
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:deb96f228449be55de31d60fc2ac4095bdc798f7d4e7999a26872c3fb52fbf53
COMPONENT_ARCHIVE_URL=  https://github.com/halfmexican/mingle/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         font/editor/mingle
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += developer/blueprint-compiler

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += system/library
