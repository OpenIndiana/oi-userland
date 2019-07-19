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

COMPONENT_NAME=        freefont
COMPONENT_VERSION=     20120503
IPS_COMPONENT_VERSION= 0.$(COMPONENT_VERSION)
COMPONENT_REVISION=    2
COMPONENT_PROJECT_URL= https://savannah.gnu.org/projects/freefont/
COMPONENT_SUMMARY=     Free UCS TrueType Fonts
COMPONENT_SRC=         freefont-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_NAME)-ttf-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:7c85baf1bf82a1a1845d1322112bc6ca982221b484e3b3925022e25b5cae89af
COMPONENT_ARCHIVE_URL= http://ftp.gnu.org/gnu/freefont/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=     GPLv3

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_PREP_ACTION =    ( cp $(COMPONENT_DIR)/files/Makefile $(@D))

