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

COMPONENT_NAME= 	Pyrex
COMPONENT_VERSION= 	0.9.9
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	A language for writing Python extension modules
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:5f87df06831d0b3412eb4bc9d3fc2ee7bfae1b913d7da8c23ab2bf5699fb6b50
COMPONENT_ARCHIVE_URL= \
  http://www.cosc.canterbury.ac.nz/greg.ewing/python/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32)

install: $(INSTALL_32)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; $(MV)  pyrexc pyrexc-$(PYTHON_VERSION); )

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
