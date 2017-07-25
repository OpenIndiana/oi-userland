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
COMPONENT_VERSION=       3.3.4
COMPONENT_FMRI=          library/eigen3
COMPONENT_SUMMARY=       A C++ template library for linear algebra.
COMPONENT_PROJECT_URL=   http://eigen.tuxfamily.org/index.php 
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_NAME)-5a0156e40feb
COMPONENT_ARCHIVE=       $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=  sha256:4286e8f1fabbd74f7ec6ef8ef31c9dbc6102b9248a8f8327b04f5b68da5b05e1
COMPONENT_ARCHIVE_URL=   http://bitbucket.org/$(COMPONENT_NAME)/$(COMPONENT_NAME)/get/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       MPL2
COMPONENT_LICENSE_FILE=  COPYING.MPL2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk



build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TEST)
