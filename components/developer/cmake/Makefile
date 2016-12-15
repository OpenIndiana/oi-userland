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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2016 Andreas Wacknitz <a.wacknitz@gmx.de>
#

# parfait seems to hang on libcmsysTestDynload.so.bc, so for
# now we have to disable it.
PARFAIT_BUILD=no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cmake
COMPONENT_VERSION=	3.5.2
COMPONENT_REVISION=	1
COMPONENT_LICENSE=	BSD, MIT, GPLv2, Curl, PD
COMPONENT_LICENSE_FILE= cmake.license
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_SUMMARY=A cross-platform, open-source make system
COMPONENT_DESCRIPTION=CMake is a family of tools designed to build, test and package software. \
It is used to control the software compilation process using simple platform and \
compiler-independent configuration files.  CMake generates native makefiles and \
workspaces that can be used in the compiler environment of your choice.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:92d8410d3d981bb881dfff2aed466da55a58d34c7390d50449aa59b32bb5e62a
COMPONENT_ARCHIVE_URL=	http://www.cmake.org/files/v3.5/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.cmake.org/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS=

LDFLAGS +=	$($(COMPILER)_NORUNPATH)

# We need these in the environment, although they are already passed
# as CONFIGURE_OPTIONS; otherwise the correct compilers are not used
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
CONFIGURE_ENV +=	CXXFLAGS="-library=stdcxx4"
endif
CONFIGURE_ENV +=	MAKE="$(GMAKE)"

CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--datadir=/share/cmake-3.5
CONFIGURE_OPTIONS +=	--docdir=/share/doc/cmake-3.5
CONFIGURE_OPTIONS += 	--mandir=/share/man

# Use system-installed third-party libraries, rather than the private
# copies in the cmake source.  Only libarchive will come from the cmake
# source, since it is not currently part of Solaris.
CONFIGURE_OPTIONS +=	--system-curl
CONFIGURE_OPTIONS +=	--system-expat
CONFIGURE_OPTIONS +=	--system-zlib
CONFIGURE_OPTIONS +=	--system-bzip2
CONFIGURE_OPTIONS +=    --system-libarchive                                                                                          
CONFIGURE_OPTIONS +=    --system-liblzma 

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"
COMPONENT_BUILD_TARGETS =	all

ASLR_MODE = $(ASLR_ENABLE)

# Need C and C++ compiler locations for cmake tests
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CXX="$(CXX)"

COMPONENT_TEST_TARGETS =	test

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# expected failure: CTestTestUpload
test:		$(TEST_32)

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl

