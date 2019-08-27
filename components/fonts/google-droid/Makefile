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
# Copyright (c) 2009, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Aurelien Larcher
#
BUILD_STYLE= archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		google-droid
COMPONENT_VERSION=	20141010
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	CJK Unicode TrueType font Ming style
COMPONENT_PROJECT_URL=	https://www.droidfonts.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/slackbuildsdirectlinks/files/google-droid-fonts/platform_frameworks_base-5.x-20141010-fonts.tar.xz 
COMPONENT_ARCHIVE_HASH= \
  sha256:85cddae7e486f1c2c4fe2aed6dbaf3d9b80a36ed046b17cdf3fb25c4f2fc7f0c
# Archive does not contain any top directory
UNPACK_ARGS= -r $(COMPONENT_SRC)
COMPONENT_LICENSE=      Apache License 2.0

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     = platform_frameworks_base-5.x-fonts/fonts
COMPONENT_FONT_FILES      += *.ttf
COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

