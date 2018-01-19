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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= docbook-dsssl
COMPONENT_VERSION= 1.79
COMPONENT_SUMMARY= Norman Walsh's modular stylesheets for DocBook
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:d5a199024a5fe0862bfaff9e3533817cd8d08bddf3cdfb5bfe6088cbb2cd62b3
COMPONENT_ARCHIVE_URL= \
  http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=http://docbook.sourceforge.net/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION +=(cp $(COMPONENT_DIR)/files/docbook-style-dsssl.Makefile $(@D)/Makefile)

COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTO_DIR)/usr/share/sgml/docbook/dsssl-stylesheets-$(COMPONENT_VERSION)
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTO_DIR)/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
