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
# Copyright 2026 Till Wegmueller
#

BUILD_STYLE=		cmake
BUILD_BITS=		64

# libclc is built with, and installs next to, one LLVM major version.
CLANG_VERSION=		21

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libclc
COMPONENT_VERSION=	21.1.8
COMPONENT_SUMMARY=	OpenCL C library for Mesa's SPIR-V targets (LLVM $(CLANG_VERSION))
COMPONENT_PROJECT_URL=	https://libclc.llvm.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:6c2677362a53531c35edf482bdc9171ea0471ca0a1e9138ac9b5a1782925616f
COMPONENT_FMRI=		developer/libclc-$(CLANG_VERSION)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	Apache-2.0 WITH LLVM-exception
COMPONENT_LICENSE_FILE=	LICENSE.TXT

# libclc has no test suite for the SPIR-V targets.
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CMAKE_PREFIX=		$(CLANG_PREFIX)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DLLVM_DIR=$(CLANG_LIBDIR)/cmake/llvm
CMAKE_OPTIONS += -DLLVM_SPIRV=$(CLANG_BINDIR)/llvm-spirv
# Mesa (mesa_clc) uses only the SPIR-V libraries.
CMAKE_OPTIONS += -DLIBCLC_TARGETS_TO_BUILD="spirv-mesa3d-;spirv64-mesa3d-"

# Build dependencies
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
REQUIRED_PACKAGES += developer/spirv-llvm-translator-$(CLANG_VERSION)

# libclc delivers only SPIR-V data files, so pkgdepend finds no dependencies.
# Auto-generated dependencies
