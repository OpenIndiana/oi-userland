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

COMPONENT_NAME= 	pgpool-II
COMPONENT_VERSION= 	3.3.1
COMPONENT_SUMMARY= 	pgpool-II middle ware
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:214e0fe96f8f2b3568ee6937318d254cb69e614ed5acd7e342bc6f34996dce7e
COMPONENT_ARCHIVE_URL= \
  http://www.pgpool.net/download.php?f=$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pgpool.net/

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_OPTIONS	+=	--sysconfdir=/etc/pgpool-II

build: $(BUILD_32)

install: $(INSTALL_32)
