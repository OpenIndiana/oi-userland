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

COMPONENT_NAME=	bitstream-vera-ttf
COMPONENT_VERSION= 1.10
COMPONENT_SUMMARY= The Bitstream Vera fonts
COMPONENT_PROJECT_URL= http://dejavu-fonts.org/
COMPONENT_FMRI=		system/font/truetype/bitstream-vera
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC_NAME= ttf-bitstream-vera
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	\
	http://ftp.gnome.org/pub/GNOME/sources/ttf-bitstream-vera/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:db5b27df7bbb318036ebdb75acd3e98f1bd6eb6608fb70a67d478cd243d178dc
COMPONENT_LICENSE=	Bitstream Vera Fonts License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/bitstream-vera

COMPONENT_BUILD_ACTION= cd $(@D) ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 *.ttf fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR);

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
