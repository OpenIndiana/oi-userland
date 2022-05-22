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

COMPONENT_NAME=  		roboto
COMPONENT_VERSION=		2.138
COMPONENT_SUMMARY=		Google’s signature family of fonts, the default font on Android and Chrome OS	
COMPONENT_DESCRIPTION=	Has optimized outlines, no hinting, and glyphs U+20E3, U+2191, and U+2193 (comb. keycap, up/down arrows) removed.
COMPONENT_SRC_BASE=  	$(COMPONENT_NAME)-android
COMPONENT_SRC=			$(COMPONENT_SRC_BASE)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).zip
COMPONENT_PROJECT_URL=	https://github.com/googlefonts/roboto
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_SRC_BASE).zip
COMPONENT_ARCHIVE_HASH=	sha256:c825453253f590cfe62557733e7173f9a421fff103b00f57d33c4ad28ae53baf
COMPONENT_LICENSE=     	Apache 2.0
COMPONENT_LICENSE_FILE=	LICENSE

# Archive does not contain any top directory
UNPACK_ARGS = -r $(COMPONENT_SRC)
FONT_TYPE = TTF
include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES += *.ttf
COMPONENT_FONTCONF_FILES =

# Auto-generated dependencies
