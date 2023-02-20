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

COMPONENT_NAME=         libayatana-appindicator
COMPONENT_VERSION=      0.5.92
COMPONENT_PROJECT_URL=  https://github.com/AyatanaIndicators/libayatana-appindicator
COMPONENT_SUMMARY=      Ayatana Application Indicators shared library
COMPONENT_FMRI=         desktop/library/libayatana-appindicator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:adedcf160dae7547971d475b42062cab278d54ec075537e6958ffdbf2d996857
COMPONENT_ARCHIVE_URL=  https://github.com/AyatanaIndicators/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv3

# Building tests causes the whole build to fail as it expects the headers to be installed already.
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DENABLE_BINDINGS_MONO=Off

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/library/libayatana-indicator
REQUIRED_PACKAGES += desktop/library/libdbusmenu
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
