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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	twemoji
COMPONENT_VERSION= 13.1.0
COMPONENT_SUMMARY= A color and B&W emoji SVG-in-OpenType font by Twitter with support for ZWJ, skin tone modifiers and country flags.
COMPONENT_PROJECT_URL= https://twemoji.twitter.com
COMPONENT_FMRI=		system/font/emoji/twemoji
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC=		TwitterColorEmoji-SVGinOT-Linux-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/eosrei/twemoji-color-font/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:57c0d651400af872c33dcab78b33ecd7be0f7d49da49e2c1c83a59c215085f94
COMPONENT_LICENSE=	Creative Commons Attribution 4.0 International
COMPONENT_LICENSE_FILE=	twemoji.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/twemoji

COMPONENT_BUILD_ACTION= cd $(@D) ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
    rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
	$(INSTALL) -c -m 0444 *.ttf fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR);

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale