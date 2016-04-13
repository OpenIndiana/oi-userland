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

COMPONENT_NAME= openoffice-dmake
COMPONENT_VERSION= 4.12.2
COMPONENT_SUMMARY= dmake for OpenOffice build
COMPONENT_SRC= dmake-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2fcbf389a9baaec25a973bd0d9e338069ad427b17d2adc7dc023efb034e96057
COMPONENT_ARCHIVE_URL= \
  http://dmake.apache-extras.org.codespot.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://code.google.com/a/apache-extras.org/p/dmake/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_PREFIX = /opt/openoffice

build: $(BUILD_32)

install: $(INSTALL_32)
