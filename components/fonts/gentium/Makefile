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
#
BUILD_STYLE = archive 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=  	gentium
COMPONENT_VERSION=      1.102
COMPONENT_VERSION=      1
COMPONENT_SUMMARY=      Gentium Basic extended Unicode fonts
COMPONENT_SRC=  	GentiumBasic_1102
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_PROJECT_URL=  https://software.sil.org/gentium/
COMPONENT_DOWNLOAD_URL= https://software.sil.org/downloads/r/gentium/
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:2f1a2c5491d7305dffd3520c6375d2f3e14931ee35c6d8ae1e8f098bf1a7b3cc
COMPONENT_LICENSE=      SIL OPEN FONT LICENSE Version 1.1

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

