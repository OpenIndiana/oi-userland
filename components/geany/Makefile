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
# Copyright 2016 Predrag Zečević.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= geany
COMPONENT_VERSION= 1.28
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/geany
COMPONENT_SUMMARY= A fast and lightweight IDE
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:f73a3708f1a26e9bf72da564d5037d6f7fedca2e0d6175db0681c2b672100a5a
COMPONENT_ARCHIVE_URL= http://download.geany.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.geany.org/Main/HomePage
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS    += --enable-the-force

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
