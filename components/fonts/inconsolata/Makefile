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
# Copyright (c) 2022, Andreas Wacknitz
#
BUILD_STYLE= archive 
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=  		Inconsolata
COMPONENT_VERSION=		3.0.0
HUMAN_VERSION=			3.000
COMPONENT_SUMMARY=		Open-source monospace font for code listings, originally by raphlinus
COMPONENT_SRC_BASE=  	$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_SRC_BASE)-v$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).zip
COMPONENT_PROJECT_URL=	https://github.com/googlefonts/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(HUMAN_VERSION)/fonts_ttf.zip
COMPONENT_ARCHIVE_HASH=	sha256:626e8ee07501dbb544b50aa59ac2e4b9ec86b810670158a59c7a3cbaf475548a
COMPONENT_LICENSE=     	SIL Open Font License, Version 1.1

# Archive has no appropriate top-level folder
UNPACK_ARGS = -r $(COMPONENT_SRC)
FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR = fonts/ttf
COMPONENT_FONT_FILES += *.ttf
COMPONENT_FONTCONF_FILES =

# Auto-generated dependencies
