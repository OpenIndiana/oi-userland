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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=64
# Currently only builds with gcc
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cmake
COMPONENT_VERSION=	3.5.2
COMPONENT_ARCHIVE_HASH=	\
    sha256:92d8410d3d981bb881dfff2aed466da55a58d34c7390d50449aa59b32bb5e62a
COMPONENT_ARCHIVE_URL=	http://www.cmake.org/files/v3.5/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.cmake.org/

TPNO=			29071

# configure in cmake does not accept many of the options set in
# configure.mk (CC=, CXX=, --bindir, --libdir, --sbindir).
CONFIGURE_DEFAULT_DIRS= no

# expected failure for test: CTestTestUpload
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)

include $(WS_MAKE_RULES)/common.mk

# Remove undesriable /opt/csw lines from the Modules/*.cmake files.
COMPONENT_PREP_ACTION += \
	cd $(COMPONENT_SRC)/Modules; $(GNU_GREP) -l '/opt/csw' *.cmake | /usr/bin/xargs -I \{\} $(GSED) -i -e '/^[ ]*\/opt\/csw/d' \{\}

# The default -O3 is *MUCH* too aggressive and will break things,
# not just in CMake but everywhere.
# CMake sets its own Language Standard flags in the Makefile it
# generates for itself. The Userland default Language Standard flags
# contradict cmake.
gcc_OPT = -O2

HTTP_PROXY = http://www-proxy.us.oracle.com:80/
HTTPS_PROXY = https://www-proxy.us.oracle.com:80/

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS.sparc=

# We need these in the environment, although they are already passed
# as CONFIGURE_OPTIONS; otherwise the correct compilers are not used
CONFIGURE_ENV +=	MAKE="$(GMAKE)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS)"

# Use system-installed third-party libraries, rather than the private
# copies in the cmake source.
CONFIGURE_OPTIONS =
CONFIGURE_OPTIONS +=	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	--system-curl
CONFIGURE_OPTIONS +=	--system-expat
CONFIGURE_OPTIONS +=	--system-zlib
CONFIGURE_OPTIONS +=	--system-bzip2
CONFIGURE_OPTIONS +=	--system-libarchive
CONFIGURE_OPTIONS +=	--system-liblzma

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV +=	CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_TARGETS =	all

# Need C and C++ compiler locations for cmake tests
COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CXX="$(CXX)"
COMPONENT_TEST_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_TEST_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_TEST_ENV += http_proxy="$(HTTP_PROXY)"
COMPONENT_TEST_ENV += https_proxy="$(HTTPS_PROXY)"
COMPONENT_TEST_ENV += HTTP_PROXY="$(HTTP_PROXY)"
COMPONENT_TEST_ENV += HTTPS_PROXY="$(HTTPS_PROXY)"

# Results output is different on Intel vs. SPARC.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

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

COMPONENT_SYSTEM_TEST_ENV += CC="$(CC)"
COMPONENT_SYSTEM_TEST_ENV += CXX="$(CXX)"
COMPONENT_SYSTEM_TEST_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_SYSTEM_TEST_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_SYSTEM_TEST_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_SYSTEM_TEST_ENV += http_proxy="$(HTTP_PROXY)"
COMPONENT_SYSTEM_TEST_ENV += https_proxy="$(HTTPS_PROXY)"
COMPONENT_SYSTEM_TEST_ENV += HTTP_PROXY="$(HTTP_PROXY)"
COMPONENT_SYSTEM_TEST_ENV += HTTPS_PROXY="$(HTTPS_PROXY)"

COMPONENT_SYSTEM_TEST_TARGETS =	test

# Install the man pages this way because we do not have Sphinx.
COMPONENT_POST_INSTALL_ACTION += \
	( $(MKDIR) -p $(PROTO_DIR)/usr/share ; \
	  $(CP) -r $(COMPONENT_DIR)/files/man1 $(PROTO_DIR)/usr/share/ ; \
	  $(CP) -r $(COMPONENT_DIR)/files/man7 $(PROTO_DIR)/usr/share/ )

# Built binaries are moved aside and replaced with
# symlinks to the system-installed binaries in /usr/bin,
# which will be executed for the system-test target
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	$(MV) $(BUILD_DIR_64)/bin $(BUILD_DIR_64)/bin-save; \
	$(MKDIR) $(BUILD_DIR_64)/bin; cd $(BUILD_DIR_64)/bin; \
	$(LN) -s $(USRBINDIR)/cmake; $(LN) -s /usr/bin/ctest; \
	$(LN) -s $(USRBINDIR)/ccmake; $(LN) -s /usr/bin/cpack

# Restore the built binaries after system-test is done
COMPONENT_POST_SYSTEM_TEST_ACTION += \
	$(RM) -r $(BUILD_DIR_64)/bin; \
	$(MV) $(BUILD_DIR_64)/bin-save $(BUILD_DIR_64)/bin

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
