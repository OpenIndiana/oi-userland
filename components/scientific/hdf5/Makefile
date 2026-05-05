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
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
# Copyright 2023 (c) Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hdf5
COMPONENT_VERSION=		2.1.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=        HDF5 - Data model, library, and file format for storing and managing data
COMPONENT_PROJECT_URL=    https://www.hdfgroup.org
COMPONENT_SRC=            $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=    https://github.com/HDFGroup/hdf5/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:5849ed7a81be6bc84ff8aa65dd966430adf0daf71e6bcb734b7a37474f92c859
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=           library/c++/hdf5
COMPONENT_LICENSE=        NCSA
COMPONENT_LICENSE_FILE=   LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_STATIC_LIBS=OFF
CMAKE_OPTIONS += -DHDF5_BUILD_CPP_LIB=ON
CMAKE_OPTIONS += -DHDF5_BUILD_HL_LIB=ON
CMAKE_OPTIONS += -DHDF5_BUILD_FORTRAN=ON
CMAKE_OPTIONS += -DHDF5_ENABLE_ZLIB_SUPPORT=ON
CMAKE_OPTIONS += -DHDF5_INSTALL_CMAKE_DIR=lib/cmake/hdf5
CMAKE_OPTIONS += -DHDF5_INSTALL_LIB_DIR=lib/$(MACH64)
CMAKE_OPTIONS += -DHDF5_INSTALL_INCLUDE_DIR=include/hdf5

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GFORTRAN_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
