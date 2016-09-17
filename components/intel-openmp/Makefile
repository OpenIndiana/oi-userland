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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

export PARFAIT_BUILD=no

BUILD_BITS = 64_and_32
COMPILER = gcc

include ../../make-rules/shared-macros.mk

# We are using GCC 4.9 with LLVM, use it here too for the time being.
# Switch to GCC 5.3 if/when LLVM can.
GCC_ROOT=/usr/gcc/4.9

COMPONENT_NAME        = libomp
COMPONENT_VERSION     = 20151009
COMPONENT_SRC         = $(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE     = $(COMPONENT_SRC)_oss.tgz
COMPONENT_ARCHIVE_HASH= \
         sha256:d4254420d0081c6844eb05237bab5e731e669a429a9c1c87e2e0221ccf0de6ac
COMPONENT_ARCHIVE_URL = http://www.openmprtl.org/sites/default/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.openmprtl.org/
COMPONENT_BUGDB       = library/intel-openmp

TPNO = 27154

BUILD_STYLE = justmake

# Uses an ON header file with S12-only features.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

export PATH=/usr/gnu/bin:$(GCC_ROOT)/bin:/usr/bin:/usr/perl5/5.22/bin

PATCH_LEVEL := 0
DEBUG_BUILD := 0

# This component uses cmake to generate Makefiles and thus does not
# run any configure script
CMAKE = /usr/bin/cmake
CMAKE_PREFIX = /usr

CMAKE_BINDIR.32     = bin/$(MACH32)
CMAKE_BINDIR.64     = bin
CMAKE_LIBDIR.32     = lib
CMAKE_LIBDIR.64     = lib/$(MACH64)

ISA_CFLAGS.i386	= -fno-omit-frame-pointer -march=opteron -mtune=opteron
ISA_CFLAGS.sparc = -mptr$(BITS) -mtune=ultrasparc3 -mcpu=ultrasparc3
ISA_CFLAGS.sparc += -mvis2 -mhard-float -mno-unaligned-doubles
ISA_CFLAGS.sparc += -mimpure-text
ISA_CFLAGS = $(ISA_CFLAGS.$(MACH))

OMP_STATS = off
OFLAG = -O2
GFLAG =
DFLAG = -DNDEBUG

ifeq ($(DEBUG_BUILD),1)
  OMP_STATS = on
  OFLAG = -O0
  GFLAG = -g3
  DFLAG =
endif

# Because of the weird way in which libiomp wants to build itself,
# we can't pass a -std=<N> on compile line. This is done internally
# by the cmake configuration files.
# The Userland default flags for GCC are broken.
CFLAGS = -m$(BITS) $(OFLAG) $(GFLAG) $(ISA_CFLAGS) -Wall
CFLAGS += -fkeep-static-consts -fno-strict-aliasing

CXXFLAGS = -m$(BITS) $(OFLAG) $(GFLAG) $(ISA_CFLAGS) -Wall
CXXFLAGS += -fkeep-static-consts -fno-strict-aliasing
CXXFLAGS += -Wl,-z -Wl,relax=comdat

CPPFLAGS = -D__EXTENSIONS__=1 -DKMP_GOMP_COMPAT=1
CPPFLAGS += -DKMP_TDATA_GTID=1
LDFLAGS += -z ignore -z relax=comdat

LIBIOMP_RUNPATH_32	= /usr/gcc/4.9/lib
LIBIOMP_RUNPATH_64	= /usr/gcc/4.9/lib/$(MACH64)
LIBIOMP_RUNPATH	= $(LIBIOMP_RUNPATH_$(BITS))

CFLAGS		+= -Wl,-R -Wl,$(LIBIOMP_RUNPATH)
CXXFLAGS	+= -Wl,-R -Wl,$(LIBIOMP_RUNPATH)
LDFLAGS		+= -R$(LIBIOMP_RUNPATH)
LD_OPTIONS	= -z ignore -z relax=comdat

CMAKE_OPTIONS = -DCMAKE_C_COMPILER=$(CC)
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER=$(CXX)
CMAKE_OPTIONS += -DCFLAGS="$(CPPFLAGS) $(CFLAGS)"
CMAKE_OPTIONS += -DCXXFLAGS="$(CPPFLAGS) $(CXXFLAGS)"
CMAKE_OPTIONS += -DLDFLAGS="$(LDFLAGS)"
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(CMAKE_PREFIX)
CMAKE_OPTIONS += -DINSTALL_LIBDIR:PATH=$(CMAKE_LIBDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBDIR:PATH=$(CMAKE_LIBDIR)
CMAKE_OPTIONS += -DCMAKE_MAKE_PROGRAM=$(GMAKE)
CMAKE_OPTIONS += -DCMAKE_SHARED_LIBRARY_SUFFIX=".so.5"

CMAKE_OPTIONS += -DCMAKE_C_FLAGS_RELEASE:STRING="$(OFLAG) $(GFLAG) $(DFLAG)"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS_RELEASE:STRING="$(OFLAG) $(GFLAG) $(DFLAG)"

CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=1
CMAKE_OPTIONS += -DCOMPILER_SUPPORTS_QUAD_PRECISION=true
CMAKE_OPTIONS += -DDEBUG_BUILD=false
CMAKE_OPTIONS += -DLIBOMP_OMPT_SUPPORT=on

CMAKE_OPTIONS += -DLIBOMP_USE_ADAPTIVE_LOCKS=true
CMAKE_OPTIONS += -DLIBOMP_STATS=$(OMP_STATS)
CMAKE_OPTIONS += -DLIBOMP_FORTRAN_MODULES=true
CMAKE_OPTIONS += -DLIBOMP_VERSION=5
CMAKE_OPTIONS += -DLIBOMP_OMP_VERSION=41
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=release

COMPONENT_BUILD_ENV += LD_OPTIONS="$(LD_OPTIONS)"

# THe tarball extracts to 'libomp_oss' which doesn't match
# the name constructed in $(COMPONENT_SRC). We fix that here.
COMPONENT_POST_UNPACK_ACTION = \
      $(MV) libomp_oss $(COMPONENT_SRC)

COMPONENT_PRE_BUILD_ACTION += cd $(@D);
COMPONENT_PRE_BUILD_ACTION += echo Running cmake with $(CMAKE_OPTIONS) ;
COMPONENT_PRE_BUILD_ACTION += /usr/bin/env - $(COMPONENT_BUILD_ENV) \
			      $(CMAKE) $(CMAKE_OPTIONS) . ;

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# There are no tests for this version of the Intel OpenMP Library
# OpenMP tests will be integrated in ${WS_TOP}/components/bots.
test: $(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += developer/gcc-4/gcc-common-49
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/gcc/gcc-runtime-49
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime-49
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime-49
REQUIRED_PACKAGES += system/library/math
