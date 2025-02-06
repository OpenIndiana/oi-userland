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
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libayatana-indicator
COMPONENT_VERSION=      0.9.4
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      Ayatana Indicators shared library
COMPONENT_PROJECT_URL=  https://github.com/AyatanaIndicators/libayatana-indicator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a18d3c682e29afd77db24366f8475b26bda22b0e16ff569a2ec71cd6eb4eac95
COMPONENT_ARCHIVE_URL=  https://github.com/AyatanaIndicators/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         desktop/library/libayatana-indicator
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# /usr/libexec needed to make dbus-daemon program available for tests
PATH = $(PATH.illumos):/usr/libexec

CMAKE_OPTIONS += -DENABLE_TESTS=On

# Testing needs an X server
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:1
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Test dependencies
TEST_REQUIRED_PACKAGES += gnome/theme/hicolor-icon-theme
TEST_REQUIRED_PACKAGES += x11/server/xvfb

# Manually added test dependency
TEST_REQUIRED_PACKAGES += developer/dbus-test-runner

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/library/ayatana-ido
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
