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
BUILD_STYLE = archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=       wqy-zenhei
COMPONENT_VERSION=    0.9.45
COMPONENT_REVISION=   2
COMPONENT_SUMMARY=    The WenQuanYi (Spring of Letters) Zenhei TrueType font
COMPONENT_PROJECT_URL=https://sourceforge.net/projects/wqy/
COMPONENT_SRC=	      $(COMPONENT_NAME)
COMPONENT_ARCHIVE=    $(COMPONENT_SRC)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/wqy/files/wqy-zenhei/0.9.45%20%28Fighting-state%20RC1%29/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:e4b7e306475bf9427d1757578f0e4528930c84c44eaa3f167d4c42f110ee75d6
COMPONENT_LICENSE=    GPLv2

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES  += *.ttc

COMPONENT_FONTCONF_SRC_DIR =

