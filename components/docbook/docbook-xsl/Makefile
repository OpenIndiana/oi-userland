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

COMPONENT_NAME= docbook-xsl
COMPONENT_VERSION= 1.69.1
COMPONENT_SUBVERSION= 5.1
COMPONENT_SUMMARY= Norman Walsh's XSL stylesheets for DocBook XML
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:917adc1dc5e2fadbcf434d9e5a8d4fc1cc5211bb3acffbb77e0a6b74d4a3f033
COMPONENT_ARCHIVE_URL= \
  http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=http://docbook.sourceforge.net/

COMPONENT_ARCHIVE_1=    docbook-xsl-doc-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:a23fc5730aec3c19a520d9fd2249097c729a049074ff455a4e88832b70009611
COMPONENT_ARCHIVE_URL_1= http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE_1)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

# we don't use $(USERLAND_UNPACK) because it can't unpack files to existing directory
COMPONENT_POST_UNPACK_ACTION += /usr/gnu/bin/tar xzf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)

COMPONENT_PREP_ACTION +=(cp $(COMPONENT_DIR)/files/docbook-style-xsl.Makefile $(@D)/Makefile)

COMPONENT_INSTALL_ARGS = DESTDIR=$(PROTO_DIR)/usr/share/sgml/docbook/xsl-stylesheets-$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTO_DIR)/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)
