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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	barman
COMPONENT_VERSION= 	1.2.3
COMPONENT_SUMMARY= 	An administration tool for disaster recovery of PostgreSQL servers 
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3ea69770345c886111054aa37d5eb2dad7a191eef131c14f8db5e7517cfb03d7
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/pgbarman/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pgbarman.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
        ($(MV) $(PROTO_DIR)/usr/bin/barman $(PROTO_DIR)/usr/bin/barman-$(PYTHON_VERSION))

build: $(BUILD_32)

install: $(INSTALL_32)
