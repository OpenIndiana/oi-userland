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
# Copyright 2016 Aurelien Larcher
#
BUILD_STYLE = archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= wqy-zenhei
COMPONENT_VERSION= 0.9.46
COMPONENT_SUMMARY= The WenQuanYi (Spring of Letters) Zenhei TrueType font
COMPONENT_PROJECT_URL= https://sourceforge.net/projects/wqy/
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-$(COMPONENT_VERSION)-May.tar.bz2
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/wqy/files/wqy-zenhei-snapshot/$(COMPONENT_VERSION)-May/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= sha256:00e75d03af47fa3bf79a0fba2da93711c6c89a9313c8873ab1145a5fa3f845d0
COMPONENT_LICENSE= GPLv2

FONT_TYPE= TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR=
COMPONENT_FONT_FILES += *.ttc

COMPONENT_FONTCONF_SRC_DIR =

# Auto-generated dependencies
