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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Python
COMPONENT_VERSION=	3.5.2
COMPONENT_PROJECT_URL=	http://python.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0010f56100b9b74259ebcd5d4b295a32324b58b517403a10d1a2aa7cb22bca40
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	utility/python

TPNO=			29999

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

# Need to preserve timestamp for Grammar files.  If the pickle files are older,
# Python will try to rebuild them.
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.txt
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.pickle

# We patch auto* files, so regenerate headers and configure
COMPONENT_PREP_ACTION = (cd $(@D) ; autoheader ; autoconf -f)

# The DTrace patch needs this file to be mode 0755.
COMPONENT_PRE_BUILD_ACTION=($(CHMOD) +x \
    $(SOURCE_DIR)/Include/pydtrace_offsets.sh)

# we don't want to leak $(CC_BITS) into BASECFLAGS as it causes problems with
# python-config
CC +=	$(CFLAGS)

C99MODE=
CPPFLAGS +=	-IPython

# to find the ncurses headers
CPPFLAGS +=	-I/usr/include/ncurses
# enable large files how they did in JDS
CPPFLAGS +=	-D_LARGEFILE64_SOURCE

# libffi for _ctypes
CPPFLAGS +=	$(shell pkg-config --cflags-only-I libffi)

# because python links with $(CC) ... $(LDFLAGS) ...
LDFLAGS =	$(CC_BITS) $(CC_PIC)

# build pic
CFLAGS +=	$(CC_PIC)

# for DWARF
CFLAGS.i386 =	-preserve_argvalues=complete
# Use the Studio VIS SDK in order to explicitly generate nonfaulting loads
# that allow Python to work with ADI-aware memory allocators.
CFLAGS.studio.sparc.64 =	-xvis

CFLAGS +=	$(CFLAGS.$(MACH))

# 16-byte memory alignment + interpretation of non-alignment prevents SIGBUS.
studio_ALIGN.sparc.64 = -xmemalign=16i

# The python build is profile-guided for studio; to see the benefits of that,
# Python must be compiled with -xO5 and a different build target must be used.
# Use of xprofile requires that the same options be used during compilation and
# linking.  The targets chosen are based on Solaris 11 minimum supported system
# requirements.
COMPONENT_BUILD_TARGETS = profile-opt
XPROFILE_DIR = $(BUILD_DIR_$(BITS))/.profile
PYFLAGS.i386 = -xtarget=opteron -xarch=sse2 -xcache=generic
PYFLAGS.sparc =
CFLAGS += -xO5 $(PYFLAGS.$(MACH))
LDFLAGS += -xO5 $(PYFLAGS.$(MACH))

# Python puts its header files in a special place.
LINT_FLAGS +=	-I$(SOURCE_DIR)/Include

# PYTHONPATH in the environment can be harmful, but setting it to empty via
# _INSTALL_ENV causes problems too, so just ignore the entire environment.
# Because of this, we need to specify PATH in multiple places below.
ENV +=				-i

CONFIGURE_ENV +=		PATH="$(PATH)"

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--with-dtrace
CONFIGURE_OPTIONS  +=		--with-system-expat
CONFIGURE_OPTIONS  +=		--with-system-ffi
CONFIGURE_OPTIONS  +=		--without-gcc
CONFIGURE_OPTIONS  +=		--without-ensurepip
CONFIGURE_OPTIONS  +=		--enable-ipv6
CONFIGURE_OPTIONS  +=		--bindir=/usr/bin
CONFIGURE_OPTIONS  +=		"ac_cv_func_getentropy=no"
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		DFLAGS="-$(BITS)"
CONFIGURE_OPTIONS  +=		XPROFILE_DIR="$(XPROFILE_DIR)"

COMPONENT_BUILD_ENV  +=		DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV  +=		XPROFILE_DIR="$(XPROFILE_DIR)"
COMPONENT_BUILD_ENV  +=		PATH="$(PATH)"

# Some tests have non-ASCII characters encoded for international domain names;
# the publish step will fail in 'pkgdepend generate' without this:
COMPONENT_PUBLISH_ENV  +=	LC_ALL=en_US.UTF-8

# 64 bit shared objects need to go in a 64-bit directory
COMPONENT_INSTALL_ARGS.64 += DESTSHARED=$(CONFIGURE_PREFIX)/lib/python3.5/lib-dynload

ASLR_MODE = $(ASLR_ENABLE)

# Simplify the definitions of CC, CXX, CFLAGS and LDFLAGS so they hard-code
# neither paths from our build systems nor Studio-specific options.
COMPONENT_PRE_INSTALL_ACTION= \
    (cd $(@D) ; \
     $(GSED) -i -e 's/^CC=.*/CC=\t\tcc/' -e 's/^CXX=.*/CXX=\t\tCC/' \
	-e 's/^CFLAGS=.*/CFLAGS=\t\t\$$\(BASECFLAGS) \$$\(OPT) \$$\(EXTRA_CFLAGS)/' \
	-e 's|^LDFLAGS=.*|LDFLAGS=|' Makefile)

# Because we stripped the Makefile above, we need to pass several things in the
# environment, and use -e to tell gmake to pay attention to the environment.
COMPONENT_INSTALL_ENV +=	CC="$(CC)"
COMPONENT_INSTALL_ENV +=	CXX="$(CXX)"
COMPONENT_INSTALL_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ENV +=	PATH="$(PATH)"
COMPONENT_INSTALL_ARGS +=	-e

# Strip build machine paths from _sysconfigdata.py & config/Makefile,
# then (re)compile _sysconfigdata.py since we just updated it.
# Note that once Python 3.5 has been integrated and propagated to build
# machines, then the LD_LIBRARY_PATH setting and PROTO_DIR prefix below
# can both be removed.
COMPONENT_POST_INSTALL_ACTION= \
    (cd $(PROTOUSRLIBDIR)/python3.5 ; \
     $(GSED) -i -e 's|$(SOURCE_DIR)|.|g' -e 's|$(COMPONENT_DIR)|..|g' \
	-e 's|$(SPRO_VROOT)/bin/||g' _sysconfigdata.py config-3.5m/Makefile; \
	LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64) $(PROTO_DIR)$(PYTHON.3.5) -m py_compile _sysconfigdata.py)

# common targets
configure:	$(CONFIGURE_64)
build:		$(BUILD_64)
install:	$(INSTALL_64)

# Using "-uall,-network" ensures all tests are run except the network tests.
# The network tests contain many expected failures when run behind a firewall.
# The "-v" ensures verbose mode.  You can set TESTOPTS_PYTHON_TEST to a
# particular test if you want to run just one test.  For example,
# $ TESTOPTS_PYTHON_TEST=test_sys gmake -k test
# Note that when a test succeeds, the builds/*/.tested file gets created.  You
# may need to remove these files, or run "gmake clobber" or "gmake clean"
# between tests.
#
COMPONENT_TEST_ENV = EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"
# The distutils tests need $CC in $PATH.
COMPONENT_TEST_ENV += PATH="$(SPRO_VROOT)/bin:$(PATH)"
# Prevent the tests from getting stuck waiting for input.
COMPONENT_TEST_TARGETS = test < /dev/null
# Some different values for system testing.
COMPONENT_SYSTEM_TEST_ENV = EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"
COMPONENT_SYSTEM_TEST_TARGETS = 
COMPONENT_SYSTEM_TEST_CMD=    $(PYTHON.3.5)
COMPONENT_SYSTEM_TEST_ARGS=   /usr/lib/python3.5/test/regrtest.py -v -uall,-network

# The test output contains details from each test, in whatever order they
# complete.  The default _TRANSFORMER is not powerful enough to deal with
# this; we need heavier artillery.  Extract just the sections that start
# with "tests OK." and end with "Re-running failed tests..." for comparison.
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS =	"'/tests OK./ {results = 1}; /Re-running failed tests in verbose mode/ {results = 0} {if (results) print $0 } '"

test:				$(TEST_64)
system-test:			$(SYSTEM_TEST_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
