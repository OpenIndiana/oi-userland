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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
# Copyright 2022 Friedrich Kink
#

BUILD_STYLE=	justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		docbook-xsl
COMPONENT_VERSION=	1.79.2
COMPONENT_SUBVERSION=	5.1
COMPONENT_FMRI=		data/docbook/xsl
COMPONENT_SUMMARY=	Norman Walsh's XSL stylesheets for DocBook XML
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:316524ea444e53208a2fb90eeb676af755da96e1417835ba5f5eb719c81fa371
COMPONENT_ARCHIVE_URL= \
  https://github.com/docbook/xslt10-stylesheets/releases/download/release/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://docbook.org/
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	docbook-xsl

COMPONENT_VERSION_1=	1.79.1
COMPONENT_ARCHIVE_1=    docbook-xsl-doc-$(COMPONENT_VERSION_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1= sha256:aabaebeb35f6ca77a9c1fa23e2c4e704dcefc5b47af03f8b6ead7103cd5d1155
COMPONENT_ARCHIVE_URL_1= \
  http://sourceforge.net/projects/docbook/files/docbook-xsl-doc/$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

# we don't use $(USERLAND_UNPACK) because it can't unpack files to existing directory
COMPONENT_POST_UNPACK_ACTION += /usr/gnu/bin/tar xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)

COMPONENT_PREP_ACTION +=(cp $(COMPONENT_DIR)/files/docbook-style-xsl.Makefile $(@D)/Makefile)

COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTO_DIR)/usr/share/sgml/docbook/xsl-stylesheets-$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTO_DIR)/usr/bin

# Auto-generated dependencies
