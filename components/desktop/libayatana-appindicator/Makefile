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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libayatana-appindicator
COMPONENT_VERSION=      0.5.93
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Ayatana Application Indicators shared library
COMPONENT_PROJECT_URL=  https://github.com/AyatanaIndicators/libayatana-appindicator
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:cbefed7a918a227bf71286246e237fcd3a9c8499b3eaac4897811a869409edf0
COMPONENT_ARCHIVE_URL=  https://github.com/AyatanaIndicators/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         desktop/library/libayatana-appindicator
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv3, LGPLv2.1, GPLv3

include $(WS_MAKE_RULES)/common.mk

# Building tests expects the headers to be installed already. This is a crude workaround which uses an already installed version.
CFLAGS += -I/usr/include/libayatana-appindicator3-0.1

CMAKE_OPTIONS += -DENABLE_TESTS=ON
CMAKE_OPTIONS += -DENABLE_BINDINGS_MONO=Off

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/library/libayatana-indicator
REQUIRED_PACKAGES += desktop/library/libdbusmenu
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
