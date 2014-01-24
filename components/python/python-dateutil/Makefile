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

COMPONENT_NAME= 	python-dateutil
COMPONENT_VERSION= 	1.5
COMPONENT_SUMMARY= 	Extensions to standard Python datetime module
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:6f197348b46fb8cdf9f3fcfc2a7d5a97da95db3e2e8667cf657216274fe1b009
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/p/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)#md5=0dcb1de5e5cad69490a3b6ab63f0cfa5
COMPONENT_PROJECT_URL = https://pypi.python.org/python-dateutil/$(COMPONENT_VERSION)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32)

install: $(INSTALL_32)
