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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE= meson
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgdata
COMPONENT_MJR_VERSION= 0.18
COMPONENT_MNR_VERSION= 1
COMPONENT_REVISION= 1
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY= libgdata is a collection library providing GObject-based interfaces and classes for commonly used data structures
COMPONENT_PROJECT_URL= https://www.gnome.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:dd8592eeb6512ad0a8cf5c8be8c72e76f74bfe6b23e4dd93f0756ee0716804c7
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/libgdata
COMPONENT_CLASSIFICATION = Development/GNOME and GTK+
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE= LGPLv2.1

# All 32 bit tests fail because of missing TLS support:
TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_ENV += PATH="$(PATH)"
COMPONENT_INSTALL_ENV += PATH="$(PATH)"

#CONFIGURE_OPTIONS += -Dinstalled_tests=true
#CONFIGURE_OPTIONS += -Dgtk_doc=true
#CONFIGURE_OPTIONS += -Dman=true
# We don't have goa:
CONFIGURE_OPTIONS += -Dgoa=disabled
# introspection needs linux compatible ld:
CONFIGURE_OPTIONS += -Dintrospection=false

COMPONENT_TEST_TRANSFORMS += '-e "s/      [0-9]*.[0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/GLib-Net-WARNING/d" ' \
        '-e "/OK/p" ' \
        '-e "/Fail/p" ' \
        '-e "/Pass/p" ' \
        '-e "/Ok/p" ' \
        '-e "/ok/p" '

# for the tests
unexport SHELLOPTS

# Build dependencies
REQUIRED_PACKAGES += library/uhttpmock

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
