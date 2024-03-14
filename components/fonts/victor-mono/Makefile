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

COMPONENT_NAME=				victor-mono
COMPONENT_SUMMARY=			Victor Mono is an open-source monospaced font with optional semi-connected cursive italics and programming symbol ligatures.
# We already had 1.52 and cannot go back. Thus, we are using HUMAN_VERSION for the "real" version number
COMPONENT_VERSION= 			1.55
HUMAN_VERSION=				1.5.5
COMPONENT_PROJECT_URL= 		https://rubjo.github.io/victor-mono/
COMPONENT_SRC_NAME=			VictorMonoAll
COMPONENT_SRC=				$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=		https://rubjo.github.io/victor-mono/$(COMPONENT_SRC_NAME).zip
COMPONENT_ARCHIVE_HASH= 	sha256:34288e16ca4834efc721aaf0c6f4ef3d86a85a5a791769787b50853ec21afd3b
COMPONENT_LICENSE=			SIL Open Font License, Version 1.1
COMPONENT_LICENSE_FILE=		LICENSE.txt

FONT_TYPE = TTF

UNPACK_ARGS= -r $(COMPONENT_SRC)

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     =
COMPONENT_FONT_FILES      += TTF/*.ttf
COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

