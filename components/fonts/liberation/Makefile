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
# Copyright 2016-2019 Aurelien Larcher
#
BUILD_STYLE = archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        liberation
COMPONENT_VERSION=      2.1.2
COMPONENT_SUMMARY=      The Liberation fonts
COMPONENT_PROJECT_URL=  https://pagure.io/liberation-fonts/
COMPONENT_SRC=          $(COMPONENT_NAME)-fonts-ttf-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
	https://github.com/liberationfonts/liberation-fonts/files/5722233/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:14694930f28391675008c67b18889d1a7dfea74b16adf50394f8057b57eaf8e0
COMPONENT_LICENSE=      SIL Open Font License Version 1.1

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR = 
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR = 
COMPONENT_FONTCONF_FILES   =

# Auto-generated dependencies
