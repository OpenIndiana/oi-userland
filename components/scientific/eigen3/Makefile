#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Dariusz Sendkowski
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=          eigen
COMPONENT_VERSION=       3.3.7
COMPONENT_FMRI=          library/eigen3
COMPONENT_SUMMARY=       A C++ template library for linear algebra.
COMPONENT_PROJECT_URL=   http://eigen.tuxfamily.org/index.php 
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_NAME)-323c052e1731
COMPONENT_ARCHIVE=       $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=  sha256:7e84ef87a07702b54ab3306e77cea474f56a40afa1c0ab245bb11725d006d0da
COMPONENT_ARCHIVE_URL=   http://bitbucket.org/$(COMPONENT_NAME)/$(COMPONENT_NAME)/get/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       MPL2
COMPONENT_LICENSE_FILE=  COPYING.MPL2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk



build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TEST)
