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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgbadger
COMPONENT_VERSION= 	4.0
COMPONENT_SUMMARY= 	pgBadger PostgreSQL log analyzer
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a1a90828a4f0fd49be93142d8a2fb0b24360c65b4feb322c0cd5b2d6eab30c78
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/pgbadger/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://dalibo.github.io/pgbadger/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

# Using makemaker.mk here is an overkill,
# because we don't need versioned  pgbadger
COMPONENT_PRE_BUILD_ACTION = ( cd $(BUILD_DIR_32) && $(PERL) Makefile.PL )

PKG_PROTO_DIRS += $(BUILD_DIR_32)

build: $(BUILD_32)

install: $(INSTALL_32)
