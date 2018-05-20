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

COMPONENT_NAME=	dejavu-fonts-ttf
COMPONENT_VERSION= 2.37
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= The DejaVu fonts
COMPONENT_PROJECT_URL= https://dejavu-fonts.github.io/
COMPONENT_FMRI=		system/font/truetype/dejavu
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	\
	http://sourceforge.net/projects/dejavu/files/dejavu/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:fa9ca4d13871dd122f61258a80d01751d603b4d3ee14095d65453b4e846e17d7
COMPONENT_LICENSE=	Bitstream Vera Fonts License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

FONT_CONF_DIR=/etc/fonts/conf.avail
FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/dejavu

COMPONENT_BUILD_ACTION= cd $(@D)/ttf ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 ttf/*.ttf ttf/fonts.dir ttf/fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR); \
	rm -rf $(PROTO_DIR)$(FONT_CONF_DIR) && mkdir -p $(PROTO_DIR)$(FONT_CONF_DIR) && \
		$(INSTALL) -c -m 0444 fontconfig/*.conf $(PROTO_DIR)$(FONT_CONF_DIR)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
