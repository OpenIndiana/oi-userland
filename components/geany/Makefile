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
# Copyright 2015 Predrag Zecevic.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= geany
COMPONENT_VERSION= 1.26
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/geany
COMPONENT_SUMMARY= A fast and lightweight IDE
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:e38530e87c577e1e9806be3b40e08fb9ee321eb1abc6361ddacdad89c825f90d
COMPONENT_ARCHIVE_URL= http://download.geany.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.geany.org/Main/HomePage
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin


CONFIGURE_OPTIONS    += --enable-the-force


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

