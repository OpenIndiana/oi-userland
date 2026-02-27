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
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE= archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        mona-sans
COMPONENT_VERSION=      2.0.8
COMPONENT_SUMMARY=      Mona Sans is a variable font inspired by industrial-era grotesques
COMPONENT_PROJECT_URL=  https://github.com/github/mona-sans
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4e1366e20fb5c03182a6e78ec5b70540b224ed47e7527ad65a5e5c1316ea167f
COMPONENT_LICENSE=      SIL Open Font License Version 1.1
COMPONENT_LICENSE_FILE=	LICENSE

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR= fonts/static/ttf
COMPONENT_FONT_FILES += *.ttf

COMPONENT_FONTCONF_SRC_DIR= 
COMPONENT_FONTCONF_FILES=

# Auto-generated dependencies
