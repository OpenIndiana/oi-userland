#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2017, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Aurelien Larcher
#
BUILD_STYLE = archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=        unfonts-ko-extra
COMPONENT_VERSION=     1.0.2-080608
IPS_COMPONENT_VERSION= 1.0.2
COMPONENT_REVISION=    1
COMPONENT_SUMMARY=     Un-Fonts Korean TrueType fonts (extra)
COMPONENT_PROJECT_URL= https://kldp.net/unfonts/
COMPONENT_SRC=         un-fonts
COMPONENT_SRC_NAME=    un-fonts-extra
COMPONENT_ARCHIVE=     2608-$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://kldp.net/unfonts/release/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:32a56acc06f264653bd151ec48c0811d07c198c2561e9f2efa8845e45b6b7407
COMPONENT_LICENSE=     GPLv2

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

