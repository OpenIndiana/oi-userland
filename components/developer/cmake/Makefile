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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2016, 2022 Andreas Wacknitz <a.wacknitz@gmx.de>
#
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cmake
COMPONENT_MAJOR_VERSION=3.26
COMPONENT_VERSION=      $(COMPONENT_MAJOR_VERSION).4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      A cross-platform, open-source make system
COMPONENT_DESCRIPTION= \
CMake is a family of tools designed to build, test and package software. \
It is used to control the software compilation process using simple platform \
and compiler-independent configuration files. \
CMake generates native makefiles and workspaces that can be used in the \
workspaces that can be used in the compiler environment of your choice.
COMPONENT_PROJECT_URL=  https://www.cmake.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:313b6880c291bd4fe31c0aa51d6e62659282a521e695f30d5cc0d25abbd5c208
COMPONENT_ARCHIVE_URL=	https://www.cmake.org/files/v$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/build/cmake
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE=      BSD, MIT, GPLv2, Curl, PD

include $(WS_MAKE_RULES)/common.mk

# Pass cmake "major" version number to the publish phase to hopefully reduce
# the amount of change needed between each update.
PKG_MACROS += CMAKE_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS=

LDFLAGS += $($(COMPILER)_NORUNPATH)

CONFIGURE_ENV += MAKE="$(GMAKE)"

# Remove undesriable /opt/csw lines from the Modules/*.cmake files.
COMPONENT_PREP_ACTION += \
	cd $(COMPONENT_SRC)/Modules; $(GNU_GREP) -l '/opt/csw' *.cmake | \
	/usr/bin/xargs -I \{\} $(GSED) -i -e '/^[ ]*\/opt\/csw/d' \{\}

# Remove files polluting the generated manifest
COMPONENT_PRE_INSTALL_ACTION = \
	$(FIND) $(SOURCE_DIR) -name '*.~1~' -exec $(RM) {} \;

# The default -O3 is *MUCH* too aggressive and will break things,
# not just in CMake but everywhere.
# CMake sets its own Language Standard flags in the Makefile it
# generates for itself. The Userland default Language Standard flags
# contradict cmake.
gcc_OPT = -O2

CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--datadir=/share/cmake-$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS +=	--docdir=/share/doc/cmake-$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS += 	--mandir=/share/man

# Use system-installed third-party libraries, rather than the private
# copies in the cmake source.
CONFIGURE_OPTIONS +=   --system-bzip2
CONFIGURE_OPTIONS +=   --system-curl
CONFIGURE_OPTIONS +=   --system-expat
CONFIGURE_OPTIONS +=   --system-jsoncpp
CONFIGURE_OPTIONS +=   --system-libarchive
CONFIGURE_OPTIONS +=   --system-liblzma
CONFIGURE_OPTIONS +=   --system-libuv
CONFIGURE_OPTIONS +=   --system-nghttp2
CONFIGURE_OPTIONS +=   --system-zlib
CONFIGURE_OPTIONS +=   --system-zstd

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	FC="$(FC)"
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV +=	CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV +=	FCFLAGS="$(FCFLAGS)"
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"
COMPONENT_BUILD_TARGETS =	all

#ASLR_MODE = $(ASLR_ENABLE)

# Need C and C++ compiler locations for cmake tests
COMPONENT_TEST_ENV += LANG=C
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CXX="$(CXX)"
COMPONENT_TEST_ENV += FC="$(FC)"
COMPONENT_TEST_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_TEST_ENV += FCFLAGS="$(FCFLAGS)"
COMPONENT_TEST_ENV += LDFLAGS="$(LDFLAGS)"
# Disable term colors to avoid test failures (actual and expected output mismatch).
COMPONENT_TEST_ENV += CLICOLOR=0

# Most Fortran tests fail because -m64 they do not pass compiler flags as they should.
# Results output is different on Intel vs. SPARC.
# The tests should run by a user with default privileges. Otherwise some tests will fail.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec//"' \
	'-e "s/\][0-9][0-9]*\.[0-9][0-9]* sec/\]/"' \
	'-e "/bin/ctest/d"' \
	'-e "/Test project/d"' \
	'-e "/^[mM]ake/d"' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/jsoncpp
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libuv
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
