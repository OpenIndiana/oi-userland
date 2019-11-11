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
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		clang-90
LLVM_NAME=		llvm
CLANG_NAME=		cfe

COMPONENT_VERSION=	9.0.0
COMPONENT_MAJOR_VERSION= \
	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\.[0-9]\+\).*/\1/')
COMPONENT_PROJECT_URL=	http://llvm.org/
COMPONENT_FMRI=		developer/clang-90
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_SUMMARY=	LLVM tools and Clang compiler
COMPONENT_SRC=		$(LLVM_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:d6a0565cf21f22e9b4353b2eb92622e8365000a9e90a16b09b56f8157eabfe84
COMPONENT_ARCHIVE_URL=  http://releases.llvm.org/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.TXT

COMPONENT_ARCHIVE_1=    $(CLANG_NAME)-$(COMPONENT_VERSION).src.tar.xz
COMPONENT_ARCHIVE_HASH_1= sha256:7ba81eef7c22ca5da688fdf9d88c20934d2d6b40bfe150ffd338900890aa4610
COMPONENT_ARCHIVE_URL_1=  http://releases.llvm.org/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

PYTHON_VERSION = 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

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
    '-e "s/^Testing Time: .*$$/Test results:/" ' \
    '-e "/^Test results:/,/Unexpected Failures:/p" ' \
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
#CMAKE_OPTIONS += -DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_BUILD_LLVM_DYLIB=ON
CMAKE_OPTIONS += -DLLVM_INSTALL_UTILS=ON
CMAKE_OPTIONS += -DLLVM_ENABLE_RTTI=ON
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE="$(PYTHON)"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
