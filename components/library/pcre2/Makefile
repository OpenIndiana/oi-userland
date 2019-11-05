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
# Copyright (c) 2017, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pcre2
COMPONENT_VERSION=	10.33
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:35514dff0ccdf02b55bd2e9fa586a1b9d01f62332c3356e379eabb75f789d8aa
COMPONENT_ARCHIVE_URL=	https://ftp.pcre.org/pub/pcre/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	Version 2 of Perl-Compatible Regular Expressions
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_PROJECT_URL=  http://pcre.org/
COMPONENT_FMRI=		library/pcre2
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENCE

include $(WS_MAKE_RULES)/common.mk

TEST_TARGET= install $(TEST_32_and_64)

# pick up -std=c99 in CFLAGS
CFLAGS +=	-std=c99

# turn on largefile support
CFLAGS +=	$(CPP_LARGEFILES)

# Although -norunpath is set for CXXFLAGS, we need to put -norunpath
# here, otherwise -norunpath doesn't get set when creating the shared
# libraries (CC -G).
CXX +=	$(studio_NORUNPATH)

CXXFLAGS+=	$(CC_PIC)

# turn on support for large files
CXXFLAGS +=	$(CPP_LARGEFILES)

CONFIGURE_ENV +=	"CPP=$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV +=	"CXXCPP=$(CXX) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV +=	"CXXLDFLAGS=$(LDFLAGS)"
CONFIGURE_ENV +=	"CXXLD=$(CXX) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV +=	"INSTALL=$(INSTALL)"
CONFIGURE_ENV +=	"MAKE=$(GMAKE)"

CONFIGURE_ENV.64 +=	"CXXLINKLIB=$(CXX) $(CCFLAGS) $(LDFLAGS)"
CONFIGURE_ENV.64 +=	"MACH64=$(MACH64)"

CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)/pcre
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-rebuild-chartables
CONFIGURE_OPTIONS +=	--enable-newline-is-any
CONFIGURE_OPTIONS +=	--enable-pcre2grep-libz
CONFIGURE_OPTIONS +=	--enable-pcre2grep-libbz2
CONFIGURE_OPTIONS +=	--enable-pcre2-32
CONFIGURE_OPTIONS +=	--with-link-size=4
CONFIGURE_OPTIONS +=	--with-match-limit=10000000
CONFIGURE_OPTIONS +=	--with-pic
# Enable UTF8 support    (was --enable-utf8 in pcre(1) configure).
CONFIGURE_OPTIONS +=	--enable-pcre2-8
# Enable Unicode support (was --enable-unicode-properties in pcre(1) configure).
CONFIGURE_OPTIONS +=	--enable-unicode

COMPONENT_BUILD_ENV +=	"LDFLAGS=$(LDFLAGS)"
COMPONENT_BUILD_ENV +=	"INSTALL=$(INSTALL)"
COMPONENT_BUILD_ENV +=	"MAKE=$(GMAKE)"

COMPONENT_BUILD_ARGS +=	-e

COMPONENT_INSTALL_ARGS +=	"INSTALL=$(INSTALL)"

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Get correct libpcre2-8.so.0 from the build area.
TEST_LIBPATH.32 =	$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =	$(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
	'-e "/Nothing to be done/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/Entering directory/d"' \
	'-e "s|Testsuite summary for PCRE .*|Testsuite summary for PCRE|" '

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
