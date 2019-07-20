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
# Copyright 2016 Alexander Pyhalov
#
BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         baekmuk
COMPONENT_VERSION=      2.2
COMPONENT_REVISION=     2
COMPONENT_PROJECT_URL=  http://kldp.net/projects/baekmuk/
COMPONENT_SUMMARY=      Baekmuk family Korean TrueType fonts
COMPONENT_SRC_NAME=     baekmuk-ttf
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:08ab7dffb55d5887cc942ce370f5e33b756a55fbb4eaf0b90f244070e8d51882
COMPONENT_ARCHIVE_URL=	\
    http://dlc.openindiana.org/oi-userland/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_PREP_ACTION =	( cp $(COMPONENT_DIR)/files/Makefile $(@D) )

COMPONENT_FONT_FILES += *.ttf

