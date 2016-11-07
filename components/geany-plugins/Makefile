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

COMPONENT_NAME= geany-plugins
COMPONENT_VERSION= 1.28
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/geany/plugins
COMPONENT_SUMMARY= Plugins for Geany editor
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:918f644053ea205fdf0f2185ac3b8e21339764e0e761a38583f2dda7de7fdb97
COMPONENT_ARCHIVE_URL= http://plugins.geany.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://plugins.geany.org/
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -std=gnu99
CFLAGS += -D_FILE_OFFSET_BITS=64
CFLAGS += -D_XOPEN_SOURCE=600

# These 2 plugins fail to be compiled
CONFIGURE_OPTIONS    += --disable-debugger --disable-scope

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
