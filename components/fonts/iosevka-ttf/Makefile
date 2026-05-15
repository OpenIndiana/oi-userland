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
# Copyright 2021, 2026 Andreas Wacknitz
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				iosevka-ttf
COMPONENT_SUMMARY=			Monospaced font with programming ligatures
COMPONENT_VERSION= 			34.5.0
COMPONENT_PROJECT_URL= 		https://github.com/be5invis/Iosevka
COMPONENT_SRC_NAME=			PkgTTF-Iosevka
COMPONENT_SRC=				$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=		$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:bbc253ac3c00d2e4e0715677a739a0529064a2decc6f85c6739446c998cf1500
COMPONENT_FMRI=				system/font/truetype/iosevka
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_LICENSE=			SIL Open Font License 1.1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# doesn't extract into its own directory, so pass -r dir to the unpack target
UNPACK_ARGS +=-r $(COMPONENT_SRC)

FONT_TTF_DIR= /usr/share/fonts/TrueType
THIS_FONT_DIR= $(FONT_TTF_DIR)/iosevka

COMPONENT_BUILD_ACTION= ( cd $(@D); mkfontscale ; mkfontdir )

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
	$(INSTALL) -c -m 0444 *.ttf fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR);

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale

# Auto-generated dependencies
