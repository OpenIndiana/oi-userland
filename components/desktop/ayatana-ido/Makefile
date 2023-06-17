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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ayatana-ido
COMPONENT_VERSION=      0.10.0
COMPONENT_PROJECT_URL=  https://github.com/AyatanaIndicators/ayatana-ido
COMPONENT_SUMMARY=      Application Indicators are a GTK implementation of the StatusNotifierItem Specification (SNI)
COMPONENT_FMRI=         desktop/library/ayatana-ido
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d6ec310572de38c6b5c4ca9ff0979366a3c783af14bb47113cab5da7d5946fa7
COMPONENT_ARCHIVE_URL=  https://github.com/AyatanaIndicators/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += CC="$(CC)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
