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

COMPONENT_NAME=	wqy-zenhei-ttf
COMPONENT_VERSION= 0.9.45
COMPONENT_SUMMARY= The WenQuanYi (Spring of Letters) Zenhei TrueType font
COMPONENT_PROJECT_URL= https://sourceforge.net/projects/wqy/
COMPONENT_FMRI=		system/font/truetype/wqy-zenhei
COMPONENT_CLASSIFICATION=	System/Fonts
COMPONENT_SRC_NAME= wqy-zenhei
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	\
	https://sourceforge.net/projects/wqy/files/wqy-zenhei/0.9.45%20%28Fighting-state%20RC1%29/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:e4b7e306475bf9427d1757578f0e4528930c84c44eaa3f167d4c42f110ee75d6
COMPONENT_LICENSE= GPLv2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

FONT_CONF_DIR=/etc/fonts/conf.avail
FONT_TTF_DIR=/usr/share/fonts/TrueType
THIS_FONT_DIR=$(FONT_TTF_DIR)/wqy

COMPONENT_BUILD_ACTION= cd $(@D) ; mkfontscale ; mkfontdir

COMPONENT_INSTALL_ACTION= cd $(@D) && \
	rm -rf $(PROTO_DIR)$(THIS_FONT_DIR) && mkdir -p $(PROTO_DIR)$(THIS_FONT_DIR) && \
		$(INSTALL) -c -m 0444 *.ttc fonts.dir fonts.scale $(PROTO_DIR)$(THIS_FONT_DIR); \
	rm -rf $(PROTO_DIR)$(FONT_CONF_DIR) && mkdir -p $(PROTO_DIR)$(FONT_CONF_DIR) && \
		$(INSTALL) -c -m 0444 *.conf $(PROTO_DIR)$(FONT_CONF_DIR)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES+= x11/mkfontdir
REQUIRED_PACKAGES+= x11/mkfontscale
