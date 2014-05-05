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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= pdsh
COMPONENT_VERSION= 2.29
COMPONENT_SUMMARY= Parallel distributed shell
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:57f0903bf782afe00874267b59e0f4adefa79da4c48d0257c5ae2bef02f87fcf
COMPONENT_ARCHIVE_URL= \
  https://pdsh.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://code.google.com/p/pdsh/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# To find ncurses
LDFLAGS += -L/usr/gnu/lib -R/usr/gnu/lib

CONFIGURE_OPTIONS += --with-ssh
CONFIGURE_OPTIONS += --with-rsh
CONFIGURE_OPTIONS += --with-readline
CONFIGURE_OPTIONS += --with-dshgroups

build: $(BUILD_32)

install: $(INSTALL_32)
