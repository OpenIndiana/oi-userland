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
# Copyright 2020 Andreas Wacknitz
#

BUILD_STYLE = archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				jetbrains-mono
COMPONENT_SUMMARY=			A typeface for developers
COMPONENT_VERSION= 			1.0.4
COMPONENT_PROJECT_URL= 		https://www.jetbrains.com/lp/mono/
COMPONENT_SRC_NAME=			JetBrainsMono
COMPONENT_SRC=				$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=		https://github.com/JetBrains/JetBrainsMono/releases/download/v${COMPONENT_VERSION}/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= 	sha256:737acc16715dbf911e833dd80fa27c49b2264c11800b0202f91b8745afa34a04
COMPONENT_LICENSE=			Apache 2.0
COMPONENT_LICENSE_FILE=		license.txt

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     =
COMPONENT_FONT_FILES      += ttf/*.ttf
COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

