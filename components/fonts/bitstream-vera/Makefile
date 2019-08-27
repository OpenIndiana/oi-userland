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

COMPONENT_NAME=         bitstream-vera
COMPONENT_VERSION=      1.10
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      The Bitstream Vera fonts
COMPONENT_PROJECT_URL=  https://dejavu-fonts.org/
COMPONENT_SRC_NAME=     ttf-bitstream-vera
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/ttf-bitstream-vera/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:db5b27df7bbb318036ebdb75acd3e98f1bd6eb6608fb70a67d478cd243d178dc
COMPONENT_LICENSE=      Bitstream Vera Fonts License

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR =
COMPONENT_FONT_FILES  += *.ttf

COMPONENT_FONTCONF_SRC_DIR =

