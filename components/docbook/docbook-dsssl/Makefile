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
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= docbook-dsssl
COMPONENT_VERSION= 1.79
COMPONENT_REVISION =	2
COMPONENT_SUMMARY= Norman Walsh's modular stylesheets for DocBook
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:d5a199024a5fe0862bfaff9e3533817cd8d08bddf3cdfb5bfe6088cbb2cd62b3
COMPONENT_ARCHIVE_URL= \
  http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=http://docbook.sourceforge.net/
COMPONENT_FMRI=			data/docbook/dsssl
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=		docbook-dsssl

TEST_TARGET = $(NO_TESTS)

include $(WS_TOP)/make-rules/common.mk

COMPONENT_PREP_ACTION +=(cp $(COMPONENT_DIR)/files/docbook-style-dsssl.Makefile $(@D)/Makefile)

COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTOUSRSHAREDIR)/sgml/docbook/dsssl-stylesheets-$(COMPONENT_VERSION)
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRSHAREDIR)/sgml/docbook

COMPONENT_POST_INSTALL_ACTION += \
	$(SYMLINK) dsssl-stylesheets-$(HUMAN_VERSION) $(PROTOUSRSHAREDIR)/sgml/docbook/dsssl-stylesheets ;

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
