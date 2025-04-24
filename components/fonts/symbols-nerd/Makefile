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
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	symbols-nerd
COMPONENT_VERSION= 3.4.0
COMPONENT_SUMMARY= Just the Nerd Font Icons. I.e Symbol font only
COMPONENT_DESCRIPTION= The emacs package nerd-icons can make use of the mono font
COMPONENT_PROJECT_URL= https://www.nerdfonts.com
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_URL=	https://github.com/ryanoasis/nerd-fonts/releases/download/v$(COMPONENT_VERSION)/NerdFontsSymbolsOnly.tar.xz
COMPONENT_ARCHIVE_HASH= sha256:7f8c090da3b0eaa7108646bf34cbbb6ed13d5358a72460522108b06c7ecd716a
COMPONENT_FMRI=		system/font/truetype/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE	

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     =
COMPONENT_FONT_FILES      += *.ttf
COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   = 10-nerd-font-symbols.conf

# doesn't extract into its own directory, so pass -r dir to the unpack target
UNPACK_ARGS += -r $(COMPONENT_SRC)

# Auto-generated dependencies
