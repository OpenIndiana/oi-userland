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
# Copyright (c) 2017, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Aurelien Larcher
#
BUILD_STYLE= archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		arphic-uming
COMPONENT_VERSION=	0.2.20080216.1
# Version was bumped at OI /dev times
IPS_COMPONENT_VERSION=  0.5.11
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=	CJK Unicode TrueType font Ming style
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/CJKUnifonts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  http://archive.debian.org/debian/pool/main/t/ttf-$(COMPONENT_NAME)/ttf-$(COMPONENT_NAME)_$(COMPONENT_VERSION).orig.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8038a6db9e832456d5da5559aff8d15130243be1091bf24f3243503a6f1bda98
# Archive does not contain any top directory
UNPACK_ARGS= -r $(COMPONENT_SRC)
COMPONENT_LICENSE=      ARPHIC PUBLIC LICENSE

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     =
COMPONENT_FONT_FILES      += fonts.alias
COMPONENT_FONT_FILES      += uming.ttc
COMPONENT_FONTCONF_SRC_DIR =

# Copy content of provided fonts.alias
COMPONENT_POST_BUILD_ACTION= \
    ( cat $(COMPONENT_DIR)/fonts.alias > $(@D)/fonts.alias )

