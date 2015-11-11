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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cmake
COMPONENT_VERSION=	3.3.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e75a178d6ebf182b048ebfe6e0657c49f0dc109779170bad7ffcb17463f2fc22
COMPONENT_ARCHIVE_URL=	http://www.cmake.org/files/v3.3/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.cmake.org/
COMPONENT_BUGDB=	utility/cmake

TPNO=			25030

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Remove undesriable /opt/csw lines from the Modules/*.cmake files.
COMPONENT_PREP_ACTION += \
	cd $(COMPONENT_SRC)/Modules; $(GNU_GREP) -l '/opt/csw' *.cmake | /usr/bin/xargs -I \{\} $(GSED) -i -e '/^[ ]*\/opt\/csw/d' \{\}
# Currently only builds with gcc, and since it's C++, we'll just force it to
# build as C++11 for ABI compatibility.
COMPILER=gcc
CXXFLAGS += -std=c++11

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS=

LDFLAGS +=	$($(COMPILER)_NORUNPATH)

# We need these in the environment, although they are already passed
# as CONFIGURE_OPTIONS; otherwise the correct compilers are not used
CONFIGURE_ENV +=	CC="$(CC)"	
CONFIGURE_ENV +=	CXX="$(CXX)"	
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS)"	
CONFIGURE_ENV +=	MAKE="$(GMAKE)"	
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	CXXFLAGS="$(CXXFLAGS)"

# configure in cmake does not accept many of the options set in
# configure.mk (CC=, CXX=, --bindir, --libdir, --sbindir). Clear those
# out and just include the default options it does accept.
CONFIGURE_OPTIONS =
CONFIGURE_OPTIONS +=	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)

# Use system-installed third-party libraries, rather than the private
# copies in the cmake source.
CONFIGURE_OPTIONS +=	--system-curl
CONFIGURE_OPTIONS +=	--system-expat
CONFIGURE_OPTIONS +=	--system-zlib
CONFIGURE_OPTIONS +=	--system-bzip2
CONFIGURE_OPTIONS +=	--system-libarchive

COMPONENT_BUILD_ENV +=	CC="$(CC)"	
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"	
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"	
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"	
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV +=	CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_TARGETS =	all

ASLR_MODE = $(ASLR_ENABLE)

# Need C and C++ compiler locations for cmake tests
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CXX="$(CXX)"

COMPONENT_TEST_TARGETS =	test

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s\s*[0-9][0-9]*\.[0-9][0-9]* sec/ SEC sec/"' \
	'-e "s/\][0-9][0-9]*\.[0-9][0-9]* sec/\]SEC sec/"'

COMPONENT_SYSTEM_TEST_ENV +=	CC="$(CC)"
COMPONENT_SYSTEM_TEST_ENV +=	CXX="$(CXX)"

COMPONENT_SYSTEM_TEST_TARGETS =	test

# Built binaries are moved aside and replaced with
# symlinks to the system-installed binaries in /usr/bin,
# which will be executed for the system-test target
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	$(MV) $(BUILD_DIR_64)/bin $(BUILD_DIR_64)/bin-save; \
	$(MKDIR) $(BUILD_DIR_64)/bin; cd $(BUILD_DIR_64)/bin; \
	$(LN) -s /usr/bin/cmake; $(LN) -s /usr/bin/ctest; \
	$(LN) -s /usr/bin/ccmake; $(LN) -s /usr/bin/cpack

# Restore the built binaries after system-test is done
COMPONENT_POST_SYSTEM_TEST_ACTION += \
	$(RM) -r $(BUILD_DIR_64)/bin; \
	$(MV) $(BUILD_DIR_64)/bin-save $(BUILD_DIR_64)/bin


# common targets

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# expected failure: CTestTestUpload
test:		$(TEST_64)

system-test:    $(BUILD_64) $(SYSTEM_TEST_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
