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

# The translator is tied to one LLVM major version and installs next to it.
CLANG_VERSION=		21

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		spirv-llvm-translator
COMPONENT_VERSION=	21.1.11
COMPONENT_SUMMARY=	Bi-directional translator between LLVM IR and SPIR-V (LLVM $(CLANG_VERSION))
COMPONENT_PROJECT_URL=	https://github.com/KhronosGroup/SPIRV-LLVM-Translator
COMPONENT_SRC=		SPIRV-LLVM-Translator-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4bf07afc97d655bd235ca4da5ef220a55350e8d4907cc54aae7e40c5dc4cdbe1
# The SPIR-V headers revision pinned by spirv-headers-tag.conf; it is newer
# than x11/library/spirv-headers and is only used at build time.
SPIRV_HEADERS_COMMIT=	575b6512579ebde466ed3dfc04e413439d14d95d
COMPONENT_SRC_1=	SPIRV-Headers-$(SPIRV_HEADERS_COMMIT)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1=	https://github.com/KhronosGroup/SPIRV-Headers/archive/$(SPIRV_HEADERS_COMMIT).tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha256:775ee89eb77d067df3f5736e2b4bb2f5f3e39ead915f11f3d366139dcb42209d
COMPONENT_FMRI=		developer/spirv-llvm-translator-$(CLANG_VERSION)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	NCSA
COMPONENT_LICENSE_FILE=	LICENSE.TXT

# The lit tests need FileCheck and the LLVM test utilities from a build tree.
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CMAKE_PREFIX=		$(CLANG_PREFIX)
CMAKE_BINDIR.64=	bin
CMAKE_LIBDIR.64=	lib

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DLLVM_DIR=$(CLANG_LIBDIR)/cmake/llvm
CMAKE_OPTIONS += -DLLVM_EXTERNAL_SPIRV_HEADERS_SOURCE_DIR=$(SOURCE_DIR_1)
CMAKE_OPTIONS += -DLLVM_SPIRV_INCLUDE_TESTS=OFF
CMAKE_OPTIONS += -DCCACHE_ALLOWED=OFF

COMPONENT_POST_INSTALL_ACTION += \
	$(ELFEDIT) -e 'dyn:runpath $(GCC_LIBDIR):$(CLANG_LIBDIR)' \
	    $(PROTO_DIR)$(CLANG_BINDIR)/llvm-spirv

# Build dependencies
REQUIRED_PACKAGES += $(CLANG_DEVELOPER_PKG)
# Auto-generated dependencies
REQUIRED_PACKAGES += $(CLANG_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
