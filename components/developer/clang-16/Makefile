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
# Copyright 2016 Aurelien Larcher.  All rights reserved.
# Copyright 2019 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2019 Till Wegmüller
# Copyright 2022 Klaus Ziegler
# Copyright 2023 Friedrich Kink
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clang
COMPONENT_VERSION=	16.0.6
CLANG_VERSION=		$(firstword $(subst ., ,$(COMPONENT_VERSION)))
COMPONENT_SUMMARY=	LLVM $(CLANG_VERSION) tools and Clang $(CLANG_VERSION) compiler
COMPONENT_PROJECT_URL=	https://llvm.org/
COMPONENT_SRC=		$(LLVM_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e91db44d1b3bb1c33fcea9a7d1f2423b883eaa9163d3d56ca2aa6d2f0711bc29
COMPONENT_ARCHIVE_URL=  https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		$(CLANG_DEVELOPER_PKG)
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.TXT

COMPONENT_FMRI.clang-runtime =		$(CLANG_RUNTIME_PKG)

LLVM_NAME= llvm
CLANG_NAME= clang

COMPONENT_ARCHIVE_1=    $(CLANG_NAME)-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_1= sha256:1186b6e6eefeadd09912ed73b3729e85b59f043724bb2818a95a2ec024571840
COMPONENT_ARCHIVE_URL_1=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2=    cmake-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_2= sha256:39d342a4161095d2f28fb1253e4585978ac50521117da666e2b1f6f28b62f514
COMPONENT_ARCHIVE_URL_2=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3=    third-party-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_3= sha256:15f5b9aeeba938530af977d5f9205612737a091a7f0f6c8075df8723b7713f70
COMPONENT_ARCHIVE_URL_3=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_3)

include $(WS_MAKE_RULES)/common.mk

CMAKE_PREFIX = $(CLANG_PREFIX)

COMPONENT_POST_UNPACK_ACTION += \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
	$(MV) $(CLANG_NAME)-$(COMPONENT_VERSION).src $(COMPONENT_SRC)/tools/clang && \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) && \
	$(MV) cmake-$(COMPONENT_VERSION).src/Modules $(COMPONENT_SRC)/cmake/ && \
  $(RM) -r cmake-$(COMPONENT_VERSION).src && \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3) && \
        $(MKDIR) $(COMPONENT_SRC)/third-party && \
	$(MV) third-party-$(COMPONENT_VERSION).src/unittest $(COMPONENT_SRC)/third-party && \
	$(MV) third-party-$(COMPONENT_VERSION).src/benchmark $(COMPONENT_SRC)/third-party && \
  $(RM) -r third-party-$(COMPONENT_VERSION).src

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D); )

COMPONENT_POST_INSTALL_ACTION =  \
        for file in `echo $(PROTO_DIR)/$(CMAKE_PREFIX)/bin/*`; do \
                /usr/bin/elfedit -e 'dyn:runpath $(GCC_LIBDIR):$(CMAKE_PREFIX)/lib' $$file ; \
        done && \
        for file in \
                `ggrep -rlh '^\#!*/usr/bin/env python' $(PROTO_DIR)/$(CMAKE_PREFIX)`; do \
          sed -i -e 's:\#!/usr/bin/env.*:\#!$(PYTHON):' $$file; \
        done

CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DGCC_INSTALL_PREFIX=$(GCC_ROOT)
CMAKE_OPTIONS += -DCMAKE_CXX_LINK_FLAGS="-L$(GCC_LIBDIR) -Wl,-rpath,$(GCC_LIBDIR)"
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCLANG_DEFAULT_LINKER="/usr/bin/ld"
CMAKE_OPTIONS += -DLLVM_ENABLE_EH=ON
CMAKE_OPTIONS += -DLLVM_ENABLE_RTTI=ON
CMAKE_OPTIONS += -DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_INCLUDE_BENCHMARKS=OFF
CMAKE_OPTIONS += -DLLVM_INSTALL_UTILS=ON
CMAKE_OPTIONS += -DCLANG_DEFAULT_RTLIB=libgcc
CMAKE_OPTIONS += -DCLANG_DEFAULT_CXX_STDLIB=libstdc++
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE="$(PYTHON)"
CMAKE_OPTIONS += -DCMAKE_MODULE_PATH="$(SOURCE_DIR)/$(COMPONENT_SRC)/cmake/Modules"

COMPONENT_TEST_CMD = $(GMAKE)
COMPONENT_TEST_ARGS = $(COMPONENT_BUILD_GMAKE_ARGS)
COMPONENT_TEST_TARGETS = check-all
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# Do not change the order of these regexp transforms.
COMPONENT_TEST_TRANSFORMS += \
    '-e "/^Testing Time: .*$$/d" ' \
    '-e "/^make.*$$/d" ' \
    '-e "/^Failed Tests /,/Unexpected Passed:/p" ' \
    '-e "" ' \
    '-e "/.*/d" '

TESTSUITE_MAKE = $(GMAKE)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
