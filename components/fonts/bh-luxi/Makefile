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

COMPONENT_NAME=        bh-luxi
COMPONENT_VERSION=     1.0.3
COMPONENT_REVISION=    1
COMPONENT_SUMMARY=     The Luxi fonts
COMPONENT_PROJECT_URL= https://www.x.org/
COMPONENT_SRC_NAME=    font-bh-ttf
COMPONENT_SRC=         $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  htps://www.x.org/releases/individual/font/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:c583b4b968ffae6ea30d5b74041afeac83126682c490a9624b770d60d0e63d59
COMPONENT_LICENSE=     Luxi fonts license

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES += *.ttf

COMPONENT_FONTCONF_SRC_DIR =

