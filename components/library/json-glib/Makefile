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
# Copyright (c) 2022 Niklas Poslovski
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= json-glib
COMPONENT_MJR_VERSION= 1.8
COMPONENT_MNR_VERSION= 0
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL= https://live.gnome.org/JsonGlib
COMPONENT_SUMMARY= JSON parser library for GLib
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:97ef5eb92ca811039ad50a65f06633f1aae64792789307be7170795d8b319454
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/json-glib
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk
PATH= $(PATH.gnu)

CONFIGURE_OPTIONS.32 += -Dintrospection=disabled

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]*s/X.XXs/" '

# Build dependencies
REQUIRED_PACKAGES += data/docbook/xsl
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/libxslt

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
