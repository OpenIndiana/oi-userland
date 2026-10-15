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
# Copyright 2024-2026 Friedrich Kink
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes


include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clang
COMPONENT_VERSION=	23.1.0
CLANG_VERSION=		$(firstword $(subst ., ,$(COMPONENT_VERSION)))
COMPONENT_SUMMARY=	LLVM tools and Clang compiler
COMPONENT_PROJECT_URL=	https://llvm.org/
COMPONENT_SRC=		llvm-project-llvmorg-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d8657b2a7291e518407bf13c4b41c85ef2cded2d4354097a2f451644dfc817b0
COMPONENT_ARCHIVE_URL=  https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		$(CLANG_DEVELOPER_PKG)
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.TXT

COMPONENT_FMRI.clang-runtime =		$(CLANG_RUNTIME_PKG)

LLVM_NAME= llvm
CLANG_NAME= clang

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lm -fPIC
#  -M /usr/lib/ld/map.pagealign will cause linker errors 
LD_OPTIONS = -M /usr/lib/ld/map.noexstk -M /usr/lib/ld/map.noexdata -Bdirect -z ignore
CXXFLAGS += -std=c++2b

CMAKE_PREFIX = $(CLANG_PREFIX)

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
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CFLAGS)"
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCLANG_DEFAULT_LINKER="/usr/bin/ld"
CMAKE_OPTIONS += -DLLVM_PARALLEL_LINK_JOBS=1
CMAKE_OPTIONS += -DLLVM_ENABLE_PROJECTS=clang
CMAKE_OPTIONS += -DLLVM_ENABLE_EH=ON
CMAKE_OPTIONS += -DLLVM_ENABLE_RTTI=ON
CMAKE_OPTIONS += -DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_INCLUDE_BENCHMARKS=OFF
CMAKE_OPTIONS += -DLLVM_INSTALL_UTILS=ON
CMAKE_OPTIONS += -DCLANG_DEFAULT_RTLIB=libgcc
CMAKE_OPTIONS += -DCLANG_DEFAULT_CXX_STDLIB=libstdc++
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE="$(PYTHON)"

COMPONENT_TEST_CMD = $(GMAKE)
COMPONENT_TEST_ARGS = $(COMPONENT_BUILD_GMAKE_ARGS)
COMPONENT_TEST_TARGETS = check-all
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# see recipe https://clang.llvm.org/get_started.html
# especially $(SOURCE_DIR)/llvm the llvm part is important
COMPONENT_CONFIGURE_ACTION = \
        cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(CONFIGURE_ENV) \
                $(CMAKE) $(CMAKE_OPTIONS) $(SOURCE_DIR)/llvm

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
