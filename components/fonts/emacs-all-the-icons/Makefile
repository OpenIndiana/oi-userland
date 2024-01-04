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
# Copyright (c) 2024, Andreas Wacknitz
#
BUILD_STYLE= archive 
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=  		all-the-icons
COMPONENT_VERSION=		5.0.0
COMPONENT_SUMMARY=		Fonts from the emacs all-the-icons package
COMPONENT_SRC=			$(COMPONENT_NAME).el-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/domtronn/all-the-icons.el
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:72ac4544ba715e082e1150adce50f9ad80b9d350585acd45ee080ac4e91caa57
COMPONENT_LICENSE=     	SIL Open Font License 1.1, MIT, Apache 2.0

FONT_TYPE = TTF
include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR = fonts
COMPONENT_FONT_FILES += *.ttf
COMPONENT_FONTCONF_FILES =

# Auto-generated dependencies
