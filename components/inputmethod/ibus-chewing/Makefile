#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Jiwon Na
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ibus-chewing
COMPONENT_VERSION=        2.1.7
COMPONENT_SUMMARY=        ibus-chewing - The Chewing engine for IBus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-Source
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:8c3e0a787902c0b647cf2724bc7bc27053f1fbde3572d04b98bd1a335ae542b4
COMPONENT_ARCHIVE_URL=    https://github.com/chewing/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/ibus/chewing
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPL v2
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/chewing/ibus-chewing

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

#To prevent git describe --dirty
COMPONENT_PREP_ACTION= ( sed -i 's/find_package(Git)/\#find_package(Git)/g'  $(SOURCE_DIR)/CMakeLists.txt) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/input-method/library/libchewing
REQUIRED_PACKAGES += system/library
