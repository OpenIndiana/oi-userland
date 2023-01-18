#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Till Wegmueller
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libArcus
COMPONENT_VERSION= 2.7.0
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= Communication library between internal components for Ultimaker software 
COMPONENT_PROJECT_URL= https://github.com/Ultimaker/libArcus
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/Ultimaker/libArcus/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:18905c627291858ec97f69b2e730d8ce847dd76813150fa6658aaece2d1485fb
COMPONENT_FMRI= library/arcus
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPL
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_PYTHON=OFF
CMAKE_OPTIONS += -DCMAKE_CXX_STANDARD_LIBRARIES="-lsocket -lnsl" 

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += system/library
