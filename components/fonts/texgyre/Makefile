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
# Copyright 2018 Aurelien Larcher
#
BUILD_STYLE= archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texgyre
COMPONENT_VERSION=	2.501
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	The TeX Gyre (TG) Collection of Fonts
COMPONENT_PROJECT_URL=	http://www.gust.org.pl/projects/e-foundry/tex-gyre
COMPONENT_SRC=		tg2_501otf
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_URL= \
  http://www.gust.org.pl/projects/e-foundry/tex-gyre/whole/$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:d7f8be5317bec4e644cf16c5abf876abeeb83c43dbec0ccb4eee4516b73b1bbe
COMPONENT_LICENSE=      GUST Font License

FONT_TYPE= OTF

include $(WS_MAKE_RULES)/font.mk

COMPONENT_FONT_SRC_DIR     =
COMPONENT_FONT_FILES      += *.otf
COMPONENT_FONTCONF_SRC_DIR =
COMPONENT_FONTCONF_FILES   =

