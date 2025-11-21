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
# Copyright 2024,2025 Friedrich Kink
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clang
COMPONENT_VERSION=	21.1.6
CLANG_VERSION=		$(firstword $(subst ., ,$(COMPONENT_VERSION)))
COMPONENT_SUMMARY=	LLVM tools and Clang compiler
COMPONENT_PROJECT_URL=	https://llvm.org/
COMPONENT_SRC=		$(LLVM_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:908bce97be0275943414b45af2e2b20e8f6d5d9266fdc120bd59f096ebc547ad
COMPONENT_ARCHIVE_URL=  https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		$(CLANG_DEVELOPER_PKG)
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.TXT

COMPONENT_FMRI.clang-runtime =		$(CLANG_RUNTIME_PKG)

LLVM_NAME= llvm
CLANG_NAME= clang

COMPONENT_ARCHIVE_1=    $(CLANG_NAME)-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_1=	sha256:348ace5d715c4caa6fb89b4c6fe07c21650e10b2fac37d8b0db75c0b11be9011
COMPONENT_ARCHIVE_URL_1=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2=    cmake-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_2=	sha256:e364f135fa14c343d70cac96f577f44e8e20bf026682f647f8c3c5687a0bebd1
COMPONENT_ARCHIVE_URL_2=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_2)

COMPONENT_ARCHIVE_3=    third-party-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_3=	sha256:8d09dc219cdb3da7dafd2161836aacdd6e02c1a113498ab5f37688599406dc8a
COMPONENT_ARCHIVE_URL_3=https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_3)

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lm

CMAKE_PREFIX = $(CLANG_PREFIX)

COMPONENT_POST_UNPACK_ACTION += \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
	$(MV) $(CLANG_NAME)-$(COMPONENT_VERSION).src $(COMPONENT_SRC)/tools/clang && \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_2) && \
	$(MV) cmake-$(COMPONENT_VERSION).src/Modules $(COMPONENT_SRC)/cmake/ && \
  $(RM) -r cmake-$(COMPONENT_VERSION).src && \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_3) && \
        $(MKDIR) $(COMPONENT_SRC)/third-party && \
	$(MV) third-party-$(COMPONENT_VERSION).src/* $(COMPONENT_SRC)/third-party && \
	$(RM) -r third-party-$(COMPONENT_VERSION).src

# all *.exports files seem to be considered as mapfile (-Wl,-Mbla.exports) but there is not any
# logic in those files which would qualify them as mapfiles so I just nulled them
# according to documentation of mapfiles they serve anyway only as optimization to the link process
# and all generated code is supposed to work without this optimization
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D); \
          find $(COMPONENT_SRC) -name \*.exports -exec cp /dev/null {} \; ; )

COMPONENT_POST_INSTALL_ACTION =  \
        for file in `echo $(PROTO_DIR)/$(CMAKE_PREFIX)/bin/*`; do \
                $(ELFEDIT) -e 'dyn:runpath $(GCC_LIBDIR):$(CMAKE_PREFIX)/lib' $$file ; \
        done && \
        for file in \
                `ggrep -rlh '^\#!*/usr/bin/env python' $(PROTO_DIR)/$(CMAKE_PREFIX)`; do \
          sed -i -e 's:\#!/usr/bin/env.*:\#!$(PYTHON):' $$file; \
        done ;

# Change all of the symlinks of the *.def header files in the prtotype area
# that link to the source directory to be actual files
COMPONENT_POST_INSTALL_ACTION +=  \
        gfind $(PROTO_DIR)/usr/clang/$(CLANG_VERSION)/include -type l -name \*.def -exec sh -c 'for i in "$$@"; do gcp --preserve --remove-destination "$$(readlink -f "$$i")" "$$i"; done' sh {} + ;

# Change all of the symlinks of the *.inc header files in the prtotype area
# that link to the source directory to be actual files
COMPONENT_POST_INSTALL_ACTION +=  \
        gfind $(PROTO_DIR)/usr/clang/$(CLANG_VERSION)/include -type l -name \*.inc -exec sh -c 'for i in "$$@"; do gcp --preserve --remove-destination "$$(readlink -f "$$i")" "$$i"; done' sh {} + ;

# Change all of the symlinks of the *.h header files in the prtotype area
# that link to the source directory to be actual files
COMPONENT_POST_INSTALL_ACTION +=  \
        gfind $(PROTO_DIR)/usr/clang/$(CLANG_VERSION)/include -type l -name \*.h -exec sh -c 'for i in "$$@"; do gcp --preserve --remove-destination "$$(readlink -f "$$i")" "$$i"; done' sh {} + ;

CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DCMAKE_CXX_LINK_FLAGS="-L$(GCC_LIBDIR) -Wl,-rpath,$(GCC_LIBDIR)"
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCLANG_DEFAULT_LINKER="/usr/bin/ld"
CMAKE_OPTIONS += -DLLVM_PARALLEL_LINK_JOBS=1
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

# Python modules are installed in non-default locations so make sure pkgdepend
# is able to find them
PKGDEPEND_RUNPATH += $(CLANG_LIBDIR)
PKGDEPEND_RUNPATH += $(CLANG_PREFIX)/share/scan-view/

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += runtime/python
