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

COMPONENT_NAME=         dejavu
COMPONENT_VERSION=      2.37
COMPONENT_REVISION=     3
COMPONENT_SUMMARY=      The DejaVu fonts
COMPONENT_PROJECT_URL=  https://dejavu-fonts.github.io/
COMPONENT_SRC_NAME=     dejavu-fonts-ttf
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/dejavu/files/dejavu/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:fa9ca4d13871dd122f61258a80d01751d603b4d3ee14095d65453b4e846e17d7
COMPONENT_LICENSE=      Bitstream Vera Fonts License

FONT_TYPE = TTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_FILES += *.ttf

