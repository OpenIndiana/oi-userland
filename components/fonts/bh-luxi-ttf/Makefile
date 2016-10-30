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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	bh-luxi-ttf
COMPONENT_VERSION= 1.0.3
COMPONENT_SUMMARY= The Luxi fonts
COMPONENT_PROJECT_URL= http://www.x.org/
COMPONENT_FMRI=	system/font/truetype/bh-luxi
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC_NAME= font-bh-ttf
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	\
	https://www.x.org/releases/individual/font/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:c583b4b968ffae6ea30d5b74041afeac83126682c490a9624b770d60d0e63d59
COMPONENT_LICENSE= Luxi fonts license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

FONT_CONF_DIR=/etc/fonts/conf.avail
FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/bh-luxi

COMPONENT_BUILD_ACTION= cd $(@D) ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 *.ttf fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR); \
  rm -rf $(PROTO_DIR)$(FONT_CONF_DIR) && mkdir -p $(PROTO_DIR)$(FONT_CONF_DIR) && \
    $(INSTALL) -c -m 0444 *.conf $(PROTO_DIR)$(FONT_CONF_DIR)


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
