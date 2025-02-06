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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2011 EveryCity Ltd. All rights reserved.
# Copyright 2013 Aurelien Larcher. All rights reserved.
#

#
# Rules and Macros for building open source software that uses the CMake utility
# from Kitware (http://www.cmake.org) to configure the build. 
# This file implements the same rules as configure.mk and thus uses GNU Make
# to build the components with support of multiple version (32/64 bit).
#
# To use these rules, set BUILD_STYLE to cmake and include
# $(WS_MAKE_RULES)/common.mk in your Makefile.
#
# Any additional pre/post configure, build, or install actions can be specified
# in your make file by setting them in on of the following macros:
#	COMPONENT_PRE_CONFIGURE_ACTION, COMPONENT_POST_CONFIGURE_ACTION
#	COMPONENT_PRE_BUILD_ACTION, COMPONENT_POST_BUILD_ACTION
#	COMPONENT_PRE_INSTALL_ACTION, COMPONENT_POST_INSTALL_ACTION
#	COMPONENT_PRE_TEST_ACTION, COMPONENT_POST_TEST_ACTION
#
# If component specific make targets need to be used for build or install, they
# can be specified in
#	COMPONENT_BUILD_TARGETS, COMPONENT_INSTALL_TARGETS
#	COMPONENT_TEST_TARGETS
#

CMAKE_PREFIX =	/usr

#
# Define path the same way as configure.mk
# Ref: http://www.cmake.org/cmake/help/v2.8.12/cmake.html#module:GNUInstallDirs
#

ifeq ($(strip $(PREFERRED_BITS)),64)
CMAKE_BINDIR.32 =	bin/$(MACH32)
CMAKE_BINDIR.64 =	bin
CMAKE_SBINDIR.32 =	sbin/$(MACH32)
CMAKE_SBINDIR.64 =	sbin
else
CMAKE_BINDIR.32 =	bin
CMAKE_BINDIR.64 =	bin/$(MACH64)
CMAKE_SBINDIR.32 =	sbin
CMAKE_SBINDIR.64 =	sbin/$(MACH64)
endif
CMAKE_LIBDIR.32 =	lib
CMAKE_LIBDIR.64 =	lib/$(MACH64)
# If the component prefers 64-bit binaries, then ensure builds deliver 64-bit
# binaries to the standard directories and 32-bit binaries to the non-standard
# location.  This allows simplification of package manifests and makes it
# easier to deliver the 64-bit binaries as the default.
ifeq ($(strip $(PREFERRED_BITS)),64)
CMAKE_LIBEXECDIR.32 =	libexec/$(MACH32)
CMAKE_LIBEXECDIR.64 =	libexec
else
CMAKE_LIBEXECDIR.32 =	libexec
CMAKE_LIBEXECDIR.64 =	libexec/$(MACH64)
endif
CMAKE_INCLUDEDIR =	include
CMAKE_DATAROOTDIR =	share
CMAKE_DATADIR =		$(CMAKE_DATAROOTDIR)
CMAKE_INFODIR =		$(CMAKE_DATAROOTDIR)/info
CMAKE_LOCALEDIR =	$(CMAKE_DATAROOTDIR)/locale
CMAKE_MANDIR =		$(CMAKE_DATAROOTDIR)/man
CMAKE_DOCDIR =		$(CMAKE_DATAROOTDIR)/doc

CMAKE_ENV = CONFIG_SHELL="$(CONFIG_SHELL)"
CMAKE_ENV += CC="$(CC)"
CMAKE_ENV += CXX="$(CXX)"
CMAKE_ENV += F77="$(F77)"
CMAKE_ENV += FC="$(FC)"
CMAKE_ENV += CFLAGS="$(CFLAGS)"
CMAKE_ENV += CXXFLAGS="$(CXXFLAGS)"
CMAKE_ENV += FFLAGS="$(F77FLAGS)"
CMAKE_ENV += FCFLAGS="$(FCFLAGS)"
CMAKE_ENV += LDFLAGS="$(LDFLAGS)"
CMAKE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CMAKE_ENV += PATH="$(PATH)"

# Rewrite absolute source-code paths into relative for ccache, so that any
# workspace with a shared CCACHE_DIR can benefit when compiling a component
ifneq ($(strip $(CCACHE)),)
CMAKE_ENV += CCACHE="$(CCACHE)"
CMAKE_ENV += CC_gcc_32="$(CC_gcc_32)"
CMAKE_ENV += CC_gcc_64="$(CC_gcc_32)"
CMAKE_ENV += CXX_gcc_32="$(CXX_gcc_64)"
CMAKE_ENV += CXX_gcc_64="$(CXX_gcc_64)"
CMAKE_ENV.$(BITS) += CCACHE_BASEDIR="$(BUILD_DIR_$(BITS))"

ifneq ($(strip $(CCACHE_DIR)),)
CMAKE_ENV += CCACHE_DIR="$(CCACHE_DIR)"
endif

ifneq ($(strip $(CCACHE_LOGFILE)),)
CMAKE_ENV += CCACHE_LOGFILE="$(CCACHE_LOGFILE)"
endif

endif

CMAKE_DEFAULT_DIRS?=yes

CMAKE_OPTIONS += -DCMAKE_C_COMPILER:STRING="$(CC)"
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER:STRING="$(CXX)"
CMAKE_OPTIONS += -DCMAKE_Fortran_COMPILER:STRING="$(FC)"
CMAKE_OPTIONS += -DCMAKE_C_FLAGS:STRING="$(CFLAGS)"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS:STRING="$(CXXFLAGS)"
CMAKE_OPTIONS += -DCMAKE_Fortran_FLAGS:STRING="$(FCFLAGS)"

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX:PATH=$(CMAKE_PREFIX)
ifeq ($(CMAKE_DEFAULT_DIRS),yes)
CMAKE_OPTIONS += -DCMAKE_INSTALL_BINDIR:PATH=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBDIR:PATH=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS += -DCMAKE_INSTALL_SBINDIR:PATH=$(CMAKE_SBINDIR.$(BITS))
CMAKE_OPTIONS += -DCMAKE_INSTALL_DATAROOTDIR:PATH=$(CMAKE_DATAROOTDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_DATADIR:PATH=$(CMAKE_DATAROOTDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_INFODIR:PATH=$(CMAKE_INFODIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_LOCALEDIR:PATH=$(CMAKE_LOCALEDIR)
CMAKE_OPTIONS += -DCMAKE_INSTALL_MANDIR:PATH=$(CMAKE_MANDIR)

CMAKE_OPTIONS += -DLIBEXEC_INSTALL_DIR="$(CMAKE_PREFIX)/$(CMAKE_LIBEXECDIR.$(BITS))"

# Some components use LIB_INSTALL_DIR or CMAKE_INSTALL_LIBDIR, as-is,
# others forcibly ignore it and set
# based on CMAKE_INSTALL_PREFIX.  Those usually instead offer a LIB_SUFFIX
# variable that we can generally use to accomplish the same result.  Setting
# them both shouldn't harm anything.
CMAKE_OPTIONS += -DLIB_INSTALL_DIR="$(CMAKE_PREFIX)/$(CMAKE_LIBDIR.$(BITS))"
CMAKE_OPTIONS.64 += -DCMAKE_LIBRARY_ARCHITECTURE=$(MACH64)
CMAKE_OPTIONS.64 += -DLIB_SUFFIX="/$(MACH64)"
endif
CMAKE_OPTIONS += $(CMAKE_OPTIONS.$(BITS))

COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)

$(BUILD_DIR_32)/.configured:	BITS=32
$(BUILD_DIR_64)/.configured:	BITS=64

CMAKE_ENV += $(CMAKE_ENV.$(BITS))

COMPONENT_TEST_CMD=ctest
COMPONENT_TEST_TARGETS=

# configure the unpacked source for building 32 and 64 bit version
CMAKE =	cmake

# provide test transforms for ctest
# drop timing
CMAKE_TEST_TRANSFORMS += "-e 's/ *[0-9]\{1,\}\.[0-9]\{1,\} sec\$$//'"
CMAKE_TEST_TRANSFORMS += "-e '/^Total Test time/d'"
# drop Start lines
CMAKE_TEST_TRANSFORMS += "-e '/^ *Start/d'"
# drop test numbers
CMAKE_TEST_TRANSFORMS += "-e 's/^ *[0-9]\{1,\}\/[0-9]\{1,\} Test *\#[0-9]\{1,\}:/Test/'"

USE_DEFAULT_TEST_TRANSFORMS?=no
ifeq ($(strip $(USE_DEFAULT_TEST_TRANSFORMS)),yes)
COMPONENT_TEST_TRANSFORMS += $(CMAKE_TEST_TRANSFORMS)
endif

# Configure
CLONEY_MODE = none
COMPONENT_PRE_CONFIGURE_ACTION += $(COMPONENT_PRE_CMAKE_ACTION)
CONFIGURE_ENV += $(CMAKE_ENV)
COMPONENT_CONFIGURE_ACTION ?= \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(CONFIGURE_ENV) \
		$(CMAKE) $(CMAKE_OPTIONS) $(SOURCE_DIR)
COMPONENT_POST_CONFIGURE_ACTION += $(COMPONENT_POST_CMAKE_ACTION)

# Build
COMPONENT_BUILD_CMD = $(CMAKE) --build .
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_CMAKE_ARGS)

# Install
COMPONENT_INSTALL_ACTION = \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(if $(strip $(CMAKE_COMPONENTS)), \
		$(CMAKE_COMPONENTS:%=$(ENV) $(COMPONENT_INSTALL_ENV) \
			$(CMAKE) --install . --component % $(COMPONENT_INSTALL_ARGS) ;) \
		, \
		$(ENV) $(COMPONENT_INSTALL_ENV) \
			$(CMAKE) --install . $(COMPONENT_INSTALL_ARGS) \
	)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Use common rules
USE_COMMON_RULES = yes
