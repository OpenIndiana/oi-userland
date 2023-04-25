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
# Copyright (c) 2023, Geoff Weiss
#
BUILD_STYLE= archive 
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=  		noto-emoji
COMPONENT_VERSION=		2.38
HUMAN_VERSION=			2.038
COMPONENT_SUMMARY=		Open source emoji library that provides standard Unicode emoji support
COMPONENT_SRC=			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).zip
COMPONENT_PROJECT_URL=	https://github.com/googlefonts/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/v$(HUMAN_VERSION).zip
COMPONENT_ARCHIVE_HASH=	sha256:fb54e3e4af6201a8da7c26a480059eaa01197a3f1d036e3b911a60162cd727a6
COMPONENT_LICENSE=     	SIL Open Font License 1.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

FONT_TYPE = TTF
include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR = fonts
COMPONENT_FONT_FILES += NotoColorEmoji.ttf
COMPONENT_FONTCONF_FILES =

# Auto-generated dependencies
