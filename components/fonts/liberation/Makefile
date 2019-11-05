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
# Copyright 2016-2019 Aurelien Larcher
#
BUILD_STYLE = archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        liberation
COMPONENT_VERSION=      2.00.5
IPS_COMPONENT_VERSION=  2.0.5
COMPONENT_SUMMARY=      The Liberation fonts
COMPONENT_PROJECT_URL=  https://pagure.io/liberation-fonts/
COMPONENT_SRC=          $(COMPONENT_NAME)-fonts-ttf-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://github.com/liberationfonts/liberation-fonts/files/2926169/$(COMPONENT_ARCHIVE).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:f14ff0a0be87b5aeb672e669363b5a699db76feb1144b06798261c0fdcd2b24d
COMPONENT_LICENSE=      SIL Open Font License Version 1.1

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR = 
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR = 
COMPONENT_FONTCONF_FILES   =

