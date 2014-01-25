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
# Copyright 2013 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	Pyro4
COMPONENT_VERSION= 	4.22
COMPONENT_IPS_NAME= 	pyro4
COMPONENT_FMRI= 	library/python-2/$(COMPONENT_IPS_NAME)
COMPONENT_SUMMARY= 	Distributed object middleware for Python (RPC)
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:d8f611f384edbd240006d8c0f56135e74199ab88e9416cfc78cf5472f1ff337d
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/P/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pythonhosted.org/Pyro4/
COMPONENT_LICENSE_FILE=	$(COMPONENT_IPS_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

