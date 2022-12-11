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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE= archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= twemoji
COMPONENT_VERSION= 14.0.2
COMPONENT_SUMMARY= A color and B&W emoji SVG-in-OpenType font by Twitter with support for ZWJ, skin tone modifiers and country flags.
COMPONENT_PROJECT_URL= https://twemoji.twitter.com
COMPONENT_SRC= TwitterColorEmoji-SVGinOT-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL= https://github.com/13rac1/twemoji-color-font/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:8e2c6cb768b5a578b1dacb8f70d3b91e782a8098821484af77cf322ac499f28a
COMPONENT_FMRI= system/font/emoji/twemoji
COMPONENT_CLASSIFICATION= System/Fonts
COMPONENT_LICENSE=	Creative Commons Attribution 4.0 International
COMPONENT_LICENSE_FILE=	LICENSE-CC-BY.txt

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_FILES += *.ttf
COMPONENT_FONT_SRC_DIR=
COMPONENT_FONTCONF_SRC_DIR=                                                                                                         
COMPONENT_FONTCONF_FILES=

# Auto-generated dependencies
