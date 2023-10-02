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

COMPONENT_NAME=	        hubot-sans
COMPONENT_VERSION=      1.0.1
COMPONENT_SUMMARY=      Hubot Sans is Mona Sans’s robotic sidekick. \
						The typeface is designed with more geometric accents to lend a technical and idiosyncratic feel
COMPONENT_PROJECT_URL=  https://github.com/github/hubot-sans
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:60a4a121ba1f6bd3cde08e760c0871ae6ad17acccf10f8ad47821745e6428d1d
COMPONENT_LICENSE=      SIL Open Font License Version 1.1
COMPONENT_LICENSE_FILE=	LICENSE

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR= fonts/ttf
COMPONENT_FONT_FILES += *.ttf

COMPONENT_FONTCONF_SRC_DIR= 
COMPONENT_FONTCONF_FILES=

# Auto-generated dependencies
