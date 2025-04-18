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
# Copyright 2025 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         minetest_game
COMPONENT_VERSION=      2025.2.18
COMPONENT_COMMIT=	d38b8e665723d90d2f3c73e26d2b00066451760d
COMPONENT_PROJECT_URL=  https://github.com/luanti-org/minetest_game
COMPONENT_SUMMARY=      The main game for the Luanti game engine
COMPONENT_FMRI=         games/minetest_game
COMPONENT_SRC=          minetest_game-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:b92a11fe1d28c255cfec830f8d31fbd048362366d05b2daa554fe9e696826d14
COMPONENT_ARCHIVE_URL=	https://github.com/luanti-org/minetest_game/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_CLASSIFICATION=       Applications/Games
COMPONENT_LICENSE=      LGPL 2.1, CC-BY-SA 3.0
COMPONENT_LICENSE_FILE=	LICENSE.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_DIR_64)/.built:
	$(MKDIR) $(BUILD_DIR_64)
	$(TOUCH) $(@)

$(INSTALL_64):
	$(MKDIR) $(PROTOUSRSHAREDIR)/luanti/games/$(COMPONENT_NAME)
	$(CP) -r $(SOURCE_DIR)/* $(PROTOUSRSHAREDIR)/luanti/games/$(COMPONENT_NAME)
	$(TOUCH) $(@)

build:          $(BUILD_64) prep

install:        $(INSTALL_64) build

# Auto-generated dependencies
