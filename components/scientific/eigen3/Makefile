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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         eigen
COMPONENT_VERSION=      3.4.0
COMPONENT_SUMMARY=      A C++ template library for linear algebra.
COMPONENT_PROJECT_URL=  https://eigen.tuxfamily.org/index.php
COMPONENT_SRC_BASE=     $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_COMMIT_ID=	3147391d946bb4b6c68edd901f2add6ac1f31f8c
COMPONENT_SRC=			$(COMPONENT_SRC_BASE)-$(COMPONENT_COMMIT_ID)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC_BASE).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:cf6f07443a4bdb382a0ad3a3307faf23ef7e65761ff42ac9b271eb78b3e6e0c8
COMPONENT_ARCHIVE_URL=  https://gitlab.com/libeigen/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_VERSION).tar.bz2
COMPONENT_FMRI=         library/eigen3
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MPL2
COMPONENT_LICENSE_FILE= COPYING.MPL2

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -DEIGEN_MPL2_ONLY

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]*\.[0-9]* sec//"'

# Auto-generated dependencies
