#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
export PARFAIT_BUILD=no
COMPILER=gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		llvm
COMPONENT_VERSION=	3.6.2
COMPONENT_PROJECT_URL=	http://llvm.org/
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_BUGDB=	utility/llvm

COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SRC_NAME=	$(COMPONENT_SRC).src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f60dc158bfda6822de167e87275848969f0558b3134892ff54fced87e4667b94
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			24358

COMPONENT_NAME_1 =	clang
COMPONENT_SRC_1 =	cfe-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.xz
COMPONENT_ARCHIVE_HASH_1 = \
	sha256:ae9180466a23acb426d12444d866b266ff2289b266064d362462e44f8d4699f3
COMPONENT_ARCHIVE_URL_1 = $(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

COMPONENT_POST_UNPACK_ACTION = \
       ( $(MV) $(COMPONENT_SRC_NAME) $(COMPONENT_SRC) )

COMPONENT_POST_UNPACK_ACTION_1 = \
	 ( $(RM) -rf $(COMPONENT_SRC)/tools/$(COMPONENT_NAME_1) ; \
	 $(CP) -rp $(COMPONENT_SRC_1) \
	    $(COMPONENT_SRC)/tools/$(COMPONENT_NAME_1) )

COMPONENT_PRE_CONFIGURE_ACTION = \
	 ( cd $(SOURCE_DIR) ; \
	 $(CHMOD) 0755 ./autoconf/AutoRegen.sh ; \
	 ./autoconf/AutoRegen.sh )

COMPONENT_POST_BUILD_ACTION = \
      if test -d $(COMPONENT_DIR)/cxa_finalize ; then \
      $(GMAKE) -C $(COMPONENT_DIR)/cxa_finalize build ; \
      fi

COMPONENT_POST_INSTALL_ACTION = \
	if test -d $(COMPONENT_DIR)/cxa_finalize ; then \
	$(GMAKE) -C $(COMPONENT_DIR)/cxa_finalize install ; \
	fi;

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL := 0
DEBUG_BUILD := 0
GCC_VERSION := 4.9

# We need GCC version 4.9, and not another version.
CC=/usr/gcc/$(GCC_VERSION)/bin/gcc
CXX=/usr/gcc/$(GCC_VERSION)/bin/g++

# We need the specific C++ runtime that clang/llvm was built and
# linked with, and not some random and incompatible stuff from
# /usr/lib.
LLVM_RUNPATH_32 = /usr/gcc/$(GCC_VERSION)/lib
LLVM_RUNPATH_64 = /usr/gcc/$(GCC_VERSION)/lib/$(MACH64)
LLVM_RUNPATH = $(LLVM_RUNPATH_$(BITS))

# -O0 for now. Ideally we want -O2.
OFLAG="-O0"
GFLAG=""

ifeq ($(DEBUG_BUILD), 1)
  OFLAG="-O0"
  GFLAG="-g3"
endif

export PATH=/usr/gnu/bin:/usr/xpg4/bin:/usr/bin:/usr/perl5/5.16/bin

# Because LLVM's install target doesn't install everything that
# needs to be installed.
EXTRA_INSTALL_BITS=llvm-lto arcmt-test c-arcmt-test c-index-test diagtool
LLVM_BINDIR=$(BUILD_DIR_64)/Release/bin

ifeq ($(DEBUG_BUILD), 1)
  LLVM_BINDIR=$(BUILD_DIR_64)/Debug+Asserts+Checks/bin
endif

COMPONENT_POST_INSTALL_ACTION += \
	list1='$(EXTRA_INSTALL_BITS)' ; for f in $$list1 ; do \
	    $(INSTALL) --mode=755 $(LLVM_BINDIR)/$$f $(PROTOUSRBINDIR)/$$f ; \
	done;

# No ASLR for compilers.
ASLR_MODE = $(ASLR_DISABLE)

# GCC options used:
# -ftree-vectorize | -fno-tree-vectorize:
# Enable/disable loop vectorization in optimizations. For details:
# https://gcc.gnu.org/projects/tree-ssa/vectorization.html
# Disabled in debug builds, will be enabled in production/optimized
# builds at some point in the future..
#
# -ftree-slp-vectorize | -fno-tree-slp-vectorize:
# Enable/disable Basic Block tree vectorization.
# Less aggressive vectorization than -ftree-vectorize, but useful
# in case -ftree-slp-vectorize misses some vectorization opportunities.
# Documentation at the same URL as above.
# Disabled in debug builds, will be enabled in production/optimized
# builds at some point in the future.
#
# -freorder-blocks | -fno-reorder-blocks
# Enable/disable BasicBlock reordering as an optimization.
# Disabled in debug builds, will be enabled in production/optimized
# builds at some point in the future.
# Documented here:
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#
# -ftoplevel-reorder | -fno-toplevel-reorder
# Another BasiBlock depentent optimization option.
# Disabled in debug builds, will be enabled in production/optimized
# builds at some point in the future.
# Documented here:
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#
# -fstack-protector-all:
# Enable stack smashing (stack corruption) protection and detection.
# This flag should always be used in conjunction with -Wstack-protector.
# -Wstack-protector acts at compile-time, -fstack-protector-all acts
# at runtime. -fstack-protector-all enables linking with libssp.so.
# This flag carries significant runtime overhead, but is very useful.
# Always enabled for now. May be removed in the future.
#
# -g3: Enable macro visibility in GDB. With just -g, debug builds will
# not record the expanded values of macros. With -g3, the values of
# expanded macros will be recorded, and macros will be observable in
# GDB.
#
# -mno-unaligned-doubles:
# Assume that the code does not make use of misaligned doubles on SPARC.
# On SPARC, doubles must align on 8. This flag makes GCC assume that
# there is no misaligned double use in the code, and GCC will not
# attempt to correct such misaligned loads/stores. If, however, there
# is such broken code when using this flag, the program will SIGBUS
# at runtime. This is a very useful debugging flag.
#
# -mhard-float:
# Use hardware floating-point operations when available. Compilers
# generally make very little use of floating-point, but this is
# a valuable/low-cost optimization for those rare cases where
# floating-point operations are used. No-op for quad-floating-point
# and UltraSPARC-1/2/3 because on those ISA's quad-floating-point
# ops are always done in software. But quad-floating-point ops in a
# compiler are virtually non-existent.
#
# -mptr32 | -mptr64:
#  Tell GCC the size of a pointer on SPARC.
#
# -mimpure-text:
# When used in addition to -shared on SPARC, this tells GCC to not pass
# -z text to the linker when linking a shared object.
# There is some suspicious interaction happening here between GCC/GAS
# and the Sun linker. Technically, and in theory, this flag should not
# be needed when compiling -fPIC. However, extensive documented use
# and practice has shown that it is indeed needed. The disadvantage
# of using this flag is that it triggers copy-on-write relocations.
#
# -mno-sse3 -mno-ssse3:
# Do not use SSE3/SSSE3 instructions on Intel. These might not be
# available. Building for Opteron - which implies SSE2 - is adequate
# for performance purposes.

CFLAGS = -m$(BITS) $(GFLAG) $(OFLAG) -pthread -std=c99 -fno-strict-aliasing
CFLAGS += -fno-tree-slp-vectorize -fno-tree-vectorize
CFLAGS += -fno-reorder-blocks -fno-toplevel-reorder
CFLAGS += -Wall -Wcast-align -Wno-long-long -Woverflow
CFLAGS += -Wstack-protector -fdata-sections -fstack-protector-all
CFLAGS += -fkeep-static-consts -ffunction-sections
CFLAGS += -Wl,-z -Wl,relax=common -Wl,-z -Wl,relax=secadj
CFLAGS += -Wl,-z -Wl,relax=transtls -Wl,-R -Wl,$(LLVM_RUNPATH)
CFLAGS.i386 += -mtune=opteron -mno-sse3 -mno-ssse3 -fno-common
CFLAGS.sparc += -mtune=ultrasparc -mcpu=ultrasparc -mvis -mhard-float
CFLAGS.sparc += -mptr$(BITS) -fdata-sections -falign-functions=8
CFLAGS.sparc += -mno-unaligned-doubles -mimpure-text
CFLAGS += $(CFLAGS.$(MACH))

CXXFLAGS = -m$(BITS) $(GFLAG) $(OFLAG) -pthread -fno-strict-aliasing
CXXFLAGS += -fexceptions -frtti -fstack-protector-all
CXXFLAGS += -fno-tree-vectorize -fno-tree-slp-vectorize
CXXFLAGS += -fno-reorder-blocks -fno-toplevel-reorder
CXXFLAGS += -Wall -Wcast-align -Wno-long-long -Woverflow
CXXFLAGS += -Wstack-protector -fkeep-static-consts
CXXFLAGS += -std=c++11 -fdata-sections -ffunction-sections
CXXFLAGS += -Wl,-z -Wl,relax=common -Wl,-z -Wl,relax=secadj
CXXFLAGS += -Wl,-z -Wl,relax=transtls -Wl,-R -Wl,$(LLVM_RUNPATH)
CXXFLAGS.sparc += -mptr$(BITS)
CXXFLAGS += $(CFLAGS.$(MACH))

CPPFLAGS = -D_GNU_SOURCE -DLLVM_SOLARIS -I/usr/gnu/include

ifeq ($(DEBUG_BUILD), 1)
  CPPFLAGS += -D_DEBUG
endif

CPPFLAGS += -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
CPPFLAGS += -D_FILE_OFFSET_BITS=64 -D__EXTENSIONS__=1
CPPFLAGS += -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS
CPPFLAGS += -D__STDC_LIMIT_MACROS -DHAVE_POSIX_MEMALIGN
CPPFLAGS += -D_GLIBCXX_FULLY_DYNAMIC_STRING=1
CPPFLAGS.i386 = -DLLVM_INTEL
CPPFLAGS.sparc = -DLLVM_SPARC
CPPFLAGS += $(CPPFLAGS.$(MACH))

LLVM_LIBDIR_32 = /usr/lib
LLVM_LIBDIR_64 = /usr/lib/$(MACH64)
LLVM_LIBDIR = $(LLVM_LIBDIR_$(BITS))

LLVM_LIBEXECDIR_32 = /usr/libexec
LLVM_LIBEXECDIR_64 = /usr/libexec/$(MACH64)
LLVM_LIBEXECDIR = $(LLVM_LIBEXECDIR_$(BITS))

CONFIGURE_SCRIPT = $(SOURCE_DIR)/configure
CONFIGURE_OPTIONS += CC="$(CC)"
CONFIGURE_OPTIONS += CXX="$(CXX)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS += --libdir=$(LLVM_LIBDIR)
CONFIGURE_OPTIONS += --libexecdir=$(LLVM_LIBEXECDIR)
CONFIGURE_OPTIONS += --sharedstatedir=/tmp
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-compiler-version-checks=yes
CONFIGURE_OPTIONS += --enable-clang-static-analyzer=yes

ifeq ($(DEBUG_BUILD), 1)
  CONFIGURE_OPTIONS += --enable-assertions=yes
  CONFIGURE_OPTIONS += --enable-optimized=no
  CONFIGURE_OPTIONS += --enable-expensive-checks=yes
  CONFIGURE_OPTIONS += --enable-debug-runtime=yes
  CONFIGURE_OPTIONS += --enable-debug-symbols=yes
else
  CONFIGURE_OPTIONS += --enable-assertions=no
  CONFIGURE_OPTIONS += --enable-optimized=yes
  CONFIGURE_OPTIONS += --enable-expensive-checks=no
  CONFIGURE_OPTIONS += --enable-debug-runtime=no
  CONFIGURE_OPTIONS += --enable-debug-symbols=no
endif

CONFIGURE_OPTIONS += --enable-keep-symbols=yes
CONFIGURE_OPTIONS += --enable-jit=yes
CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --disable-doxygen
CONFIGURE_OPTIONS += --enable-threads=yes
CONFIGURE_OPTIONS += --enable-pthreads=yes
CONFIGURE_OPTIONS += --enable-shared=yes
CONFIGURE_OPTIONS += --enable-zlib=yes
CONFIGURE_OPTIONS += --enable-pic=yes
CONFIGURE_OPTIONS += --enable-timestamps
CONFIGURE_OPTIONS += --enable-backtraces
CONFIGURE_OPTIONS += --enable-bindings=auto
CONFIGURE_OPTIONS += --enable-libffi=yes
CONFIGURE_OPTIONS += --enable-terminfo=yes
CONFIGURE_OPTIONS += --enable-ltdl-install=no
CONFIGURE_OPTIONS += --with-python=$(PYTHON)

ifeq ($(MACH),sparc)
  CONFIGURE_OPTIONS += --with-extra-ld-options='-lkstat'
endif
CONFIGURE_OPTIONS += --with-gcc-toolchain=/usr/gcc/$(GCC_VERSION)
CONFIGURE_OPTIONS += --with-optimize-option="$(OFLAG) $(GFLAG)"

# Enable the cross-compiler in 3.8.X.
CONFIGURE_OPTIONS.i386 += --enable-targets="x86"
CONFIGURE_OPTIONS.sparc += --enable-targets="sparc"
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))

# Put this here for now until the gpatch problems are resolved.
COMPONENT_BUILD_ARGS += -j8

# use bash(1) to run the install recipes otherwise clang header installation
# fails
COMPONENT_INSTALL_ARGS += SHELL=/bin/bash

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# There are no master test results yet. TBDL in 3.8.X.
test:
	@echo "Tests not yet implemented (wait for 3.8.X)."

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += developer/gcc-4/gcc-common-49
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime-49
REQUIRED_PACKAGES += system/library/gcc/gcc-gobjcc-runtime-49
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker

