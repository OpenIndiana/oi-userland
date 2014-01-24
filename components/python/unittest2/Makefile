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

COMPONENT_NAME= 	unittest2
COMPONENT_VERSION= 	0.5.1
COMPONENT_SUMMARY= 	unittest2 is a backport of the new features added to the unittest testing framework in Python 2.7
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:aa5de8cdf654d843379c97bd1ee240e86356d3355a97b147a6f3f4d149247a71
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/u/unittest2/$(COMPONENT_ARCHIVE)#md5=a0af5cac92bbbfa0c3b0e99571390e0f
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/unittest2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32)

install: $(INSTALL_32)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; for i in unit2; do $(MV) $$i $$i-$(PYTHON_VERSION); done)
