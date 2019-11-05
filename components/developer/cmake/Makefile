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
# Copyright 2016 Andreas Wacknitz <a.wacknitz@gmx.de>
#
PREFERRED_BITS=64

# parfait seems to hang on libcmsysTestDynload.so.bc, so for
# now we have to disable it.
PARFAIT_BUILD=no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cmake
COMPONENT_MAJOR_VERSION=3.15
COMPONENT_VERSION=      $(COMPONENT_MAJOR_VERSION).1
COMPONENT_PROJECT_URL=  https://www.cmake.org/
COMPONENT_FMRI=         developer/build/cmake
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_SUMMARY=      A cross-platform, open-source make system
COMPONENT_DESCRIPTION= \
CMake is a family of tools designed to build, test and package software. \
It is used to control the software compilation process using simple platform \
and compiler-independent configuration files. \
CMake generates native makefiles and workspaces that can be used in the \
workspaces that can be used in the compiler environment of your choice.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:18dec548d8f8b04d53c60f9cedcebaa6762f8425339d1e2c889c383d3ccdd7f7
COMPONENT_ARCHIVE_URL= \
  https://www.cmake.org/files/v$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD, MIT, GPLv2, Curl, PD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS=

LDFLAGS +=	$($(COMPILER)_NORUNPATH)

CONFIGURE_ENV +=	MAKE="$(GMAKE)"

# Remove undesriable /opt/csw lines from the Modules/*.cmake files.
COMPONENT_PREP_ACTION += \
	cd $(COMPONENT_SRC)/Modules; $(GNU_GREP) -l '/opt/csw' *.cmake | \
	/usr/bin/xargs -I \{\} $(GSED) -i -e '/^[ ]*\/opt\/csw/d' \{\}

# Remove files polluting the generated manifest
COMPONENT_PRE_INSTALL_ACTION = \
	$(FIND) $(SOURCE_DIR) -name '*.~1~' -exec $(RM) {} \;

CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--datadir=/share/cmake-$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS +=	--docdir=/share/doc/cmake-$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS += 	--mandir=/share/man

# Use system-installed third-party libraries, rather than the private
# copies in the cmake source.
CONFIGURE_OPTIONS +=	--system-curl
CONFIGURE_OPTIONS +=	--system-expat
CONFIGURE_OPTIONS +=	--system-zlib
CONFIGURE_OPTIONS +=	--system-bzip2
CONFIGURE_OPTIONS +=	--system-libarchive
CONFIGURE_OPTIONS += 	--system-liblzma

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	FC="$(FC)"
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV +=	CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV +=	FCFLAGS="$(FCFLAGS)"
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"
COMPONENT_BUILD_TARGETS =	all

# Pass cmake "major" version number to the publish phase to hopefully reduce
# the amount of change needed between each update.
PKG_MACROS+= CMAKE_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

ASLR_MODE = $(ASLR_ENABLE)

# Need C and C++ compiler locations for cmake tests
COMPONENT_TEST_ENV += LANG=C
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CXX="$(CXX)"
COMPONENT_TEST_ENV += FC="$(FC)"
COMPONENT_TEST_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_TEST_ENV += FCFLAGS="$(FCFLAGS)"
COMPONENT_TEST_ENV += LDFLAGS="$(LDFLAGS)"

# Results output is different on Intel vs. SPARC.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# Most Fortran tests fail because -m64 they do not pass compiler flags as they should.
# The following tests FAILED:
#         39 - FortranOnly (Failed)
#         40 - VSGNUFortran (Failed)
#         83 - Module.CheckIPOSupported-Fortran (Failed)
#        237 - Fortran (Failed)
#        238 - FortranModules (Failed)
#        267 - CMakeOnly.CompilerIdFortran (Failed)
#        434 - RunCMake.CompilerLauncher (Failed)

COMPONENT_TEST_TARGETS =	test

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec/ SEC sec/"' \
	'-e "s/\][0-9][0-9]*\.[0-9][0-9]* sec/\]SEC sec/"' \
	'-e "/bin/ctest/d"' \
	'-e "/Test project/d"' \
	'-e "/^[mM]ake/d"' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
