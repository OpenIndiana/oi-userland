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

COMPONENT_NAME=         libayatana-indicator
COMPONENT_VERSION=      0.9.3
COMPONENT_PROJECT_URL=  https://github.com/AyatanaIndicators/libayatana-indicator
COMPONENT_SUMMARY=      Ayatana Indicators shared library
COMPONENT_FMRI=         desktop/library/libayatana-indicator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:09c5456fcb430b6ee0626fafdf99a32eb8746b267d56ab2bd4c8a8dd6ca731da
COMPONENT_ARCHIVE_URL=  https://github.com/AyatanaIndicators/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      GPLv3

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DENABLE_TESTS=On

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]* sec/X.XX sec/" '

# Manually added test dependency
REQUIRED_PACKAGES += developer/dbus-test-runner

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/library/ayatana-ido
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
