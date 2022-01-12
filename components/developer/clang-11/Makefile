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
#

BUILD_BITS=		64
BUILD_STYLE=		cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clang-11
LLVM_NAME=		llvm
CLANG_NAME=		clang

COMPONENT_VERSION=	11.0.0
COMPONENT_MAJOR_VERSION= \
	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\.[0-9]\+\).*/\1/')
COMPONENT_PROJECT_URL=	http://llvm.org/
COMPONENT_FMRI=		developer/clang-11
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_SUMMARY=	LLVM tools and Clang compiler
COMPONENT_SRC=		$(LLVM_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:913f68c898dfb4a03b397c5e11c6a2f39d0f22ed7665c9cefa87a34423a72469
COMPONENT_ARCHIVE_URL=  https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.TXT

COMPONENT_ARCHIVE_1=    $(CLANG_NAME)-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_1= sha256:0f96acace1e8326b39f220ba19e055ba99b0ab21c2475042dbc6a482649c5209
COMPONENT_ARCHIVE_URL_1=  https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

PYTHON_VERSION = 3.9

COMPONENT_BUILD_ARGS=	-j12

include $(WS_MAKE_RULES)/common.mk

CMAKE_PREFIX= /usr/clang/$(COMPONENT_MAJOR_VERSION)

PKG_MACROS += GCC_VERSION=$(GCC_VERSION)

COMPONENT_POST_UNPACK_ACTION += \
  $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
	mv $(CLANG_NAME)-$(COMPONENT_VERSION).src $(COMPONENT_SRC)/tools/clang

COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

COMPONENT_POST_INSTALL_ACTION =  \
	for file in `echo $(PROTO_DIR)/$(CMAKE_PREFIX)/bin/*`; do \
		elfedit -e 'dyn:runpath $(GCC_LIBDIR):$(CMAKE_PREFIX)/lib' $$file ; \
	done && \
	for file in \
		`ggrep -rlh '^\#!*/usr/bin/env python' $(PROTO_DIR)/$(CMAKE_PREFIX)`; do \
	  sed -i -e 's,^\#!*/usr/bin/env python,\#!$(PYTHON),' $$file; \
	done

COMPONENT_TEST_CMD = $(GMAKE)
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

CMAKE_OPTIONS += -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DGCC_INSTALL_PREFIX=$(GCC_ROOT)
CMAKE_OPTIONS += -DCMAKE_CXX_LINK_FLAGS="$(LDFLAGS)" # -L$(GCC_LIBDIR) -Wl,-rpath,$(GCC_LIBDIR)"
CMAKE_OPTIONS += -DLLVM_ENABLE_ASSERTIONS=ON
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCLANG_DEFAULT_LINKER="/usr/bin/ld"
CMAKE_OPTIONS += -DLLVM_BUILD_TESTS:BOOL=ON
CMAKE_OPTIONS += -DLLVM_INCLUDE_TESTS:BOOL=ON
CMAKE_OPTIONS += -DLLVM_BUILD_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_INSTALL_UTILS=ON
CMAKE_OPTIONS += -DLLVM_ENABLE_RTTI=ON
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE="$(PYTHON)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
