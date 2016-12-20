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

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		Python
COMPONENT_VERSION=	2.7.13
COMPONENT_PROJECT_URL=	https://python.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:35d543986882f78261f97787fd3e06274bfa6df29fac9b4a94f73930ff98f731
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	utility/python

TPNO=			33100

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

studio_C99MODE= $(studio_C99_ENABLE)
CFLAGS += $(XPG6MODE)

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
CFLAGS +=	$(CFLAGS.$(MACH))

# The python build is profile-guided for studio; to see the benefits of that,
# Python must be compiled with -xO5 and a different build target must be used.
# Use of xprofile requires that the same options be used during compilation and
# linking.  The targets chosen are based on Solaris 11 minimum supported system
# requirements.
#
# We bypass the profile build for one file (ceval.c; see the DTrace patch)
# and reduce the optimization level for that same file to work around a
# problem (see bug 23467236) where Python would core dump on sparc when
# run under DTrace.
COMPONENT_BUILD_TARGETS = profile-opt
XPROFILE_DIR = $(BUILD_DIR_$(BITS))/.profile
PYFLAGS.i386 = -xtarget=opteron -xarch=sse2 -xcache=generic
PYFLAGS.sparc =
CEVAL_PATSUBST.i386 =	
CEVAL_PATSUBST.sparc =	"-xprofile=\%"
CEVAL_PATSUBST =	$(CEVAL_PATSUBST.$(MACH))
CEVAL_CFLAGS.i386 =	$(CFLAGS)
CEVAL_CFLAGS.sparc =	$(subst -xO5,-xO4,$(CFLAGS))
CEVAL_CFLAGS =		$(CEVAL_CFLAGS.$(MACH))

CFLAGS += -xO5 $(PYFLAGS.$(MACH))
LDFLAGS += -xO5 $(PYFLAGS.$(MACH))

# Use the Studio VIS SDK in order to explicitly generate nonfaulting loads
# that allow Python to work with ADI-aware memory allocators.
CFLAGS.studio.sparc.64 +=  -xvis

# Python puts its header files in a special place.
LINT_FLAGS +=	-I$(SOURCE_DIR)/Include

# PYTHONPATH in the environment can be harmful, but setting it to empty via
# _INSTALL_ENV causes problems too, so just ignore the entire environment.
# Because of this, we need to specify PATH in multiple places below.
ENV +=				-i

CONFIGURE_ENV +=		PATH="$(PATH)"

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--with-system-expat
CONFIGURE_OPTIONS  +=		--with-system-ffi
CONFIGURE_OPTIONS  +=		--without-gcc
CONFIGURE_OPTIONS  +=		--enable-ipv6
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		DFLAGS="-$(BITS)"
CONFIGURE_OPTIONS  +=		XPROFILE_DIR="$(XPROFILE_DIR)"

COMPONENT_BUILD_ENV  +=		PATH="$(PATH)"
COMPONENT_BUILD_ENV  +=		DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV  +=		XPROFILE_DIR="$(XPROFILE_DIR)"
COMPONENT_BUILD_ENV  +=		CEVAL_CFLAGS="$(CEVAL_CFLAGS)"
COMPONENT_BUILD_ENV  +=		CEVAL_PATSUBST="$(CEVAL_PATSUBST)"

# 64 bit shared objects need to go in a 64-bit directory
COMPONENT_INSTALL_ARGS.64 += DESTSHARED=$(CONFIGURE_PREFIX)/lib/python2.7/lib-dynload

# Simplify the definitions of CC, CXX, CFLAGS and LDFLAGS so they hard-code
# neither paths from our build systems nor Studio-specific options.
COMPONENT_PRE_INSTALL_ACTION= \
            (cd $(@D) ; $(GSED) -i -e 's/^CC=.*/CC=\t\tcc/' \
		-e 's/^CXX=.*/CXX=\t\tCC/' \
		-e 's/^CFLAGS=.*/CFLAGS=\t\t\$$\(BASECFLAGS) \$$\(OPT) \$$\(EXTRA_CFLAGS)/' \
		-e 's|^LDFLAGS=.*|LDFLAGS=|' \
		Makefile)

# Because we stripped the Makefile above, we need to pass several things in the
# environment, and use -e to tell gmake to pay attention to the environment.
COMPONENT_INSTALL_ENV +=	CC="$(CC)"
COMPONENT_INSTALL_ENV +=	CXX="$(CXX)"
COMPONENT_INSTALL_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV +=	LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ENV +=	PATH="$(PATH)"
COMPONENT_INSTALL_ARGS +=	-e

# 1. Setup pyconfig.h file to support 32 & 64 bit.
# 2. If the /usr/lib/python2.7/lib2to3/*.pickle files are older than the
#    related *.txt files in the same directory, it will rebuild them any time
#    you try to build a Python module.  So here we also touch the pickle files
#    to avoid this.
# 3. Strip build machine paths from _sysconfigdata.py & config/Makefile.
#    Note that although the 64-bit version is not used (and thus commented
#    out in the manifest), we still need to specify the 32-/64-bit paths,
#    otherwise the 64-bit build will fail to find the 32-bit path.
# 4. (Re)compile _sysconfigdata.py since we just updated it.
CONFIG_MAKEFILE.32=	lib/python2.7/config/Makefile
CONFIG_MAKEFILE.64=	lib/$(MACH64)/python2.7/config/Makefile
CONFIG_MAKEFILE=	$(CONFIG_MAKEFILE.$(BITS))
COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/python2.7/pyconfig.h include/python2.7/pyconfig-$(BITS).h ; \
             $(TOUCH) lib/python2.7/lib2to3/*.pickle ; \
	     $(GSED) -i -e 's|$(SOURCE_DIR)|.|g' -e 's|$(COMPONENT_DIR)|..|g' \
		-e 's|$(SPRO_VROOT)/bin/||g' lib/python2.7/_sysconfigdata.py \
		$(CONFIG_MAKEFILE); \
	     $(PYTHON.2.7) -m py_compile lib/python2.7/_sysconfigdata.py)

# common targets
$(INSTALL_32):  $(INSTALL_64)
configure:	$(CONFIGURE_32_and_64)
build:		$(BUILD_32_and_64)
install:	$(INSTALL_32_and_64)

# Using "-uall,-network" ensures all tests are run except the network tests.
# The network tests contain many expected failures when run behind a firewall.
# The "-v" ensures verbose mode.  You can set TESTOPTS_PYTHON_TEST to a
# particular test if you want to run just one test.  For example, run gmake with
# "-k" so it continues and does both 32-bit and 64-bit tests, even if there is a
# failure, like this:
# $ TESTOPTS_PYTHON_TEST=test_sys gmake -k test
# Note that when a test succeeds, the builds/*/.tested file gets created.  You
# may need to remove these files, or run "gmake clobber" or "gmake clean"
# between tests.
#
COMPONENT_TEST_ENV = EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"
# The distutils tests need $CC in $PATH.
COMPONENT_TEST_ENV += PATH="$(SPRO_VROOT)/bin:$(PATH)"
COMPONENT_TEST_TARGETS = test

# The test output contains details from each test, in whatever order they
# complete.  The default _TRANSFORMER is not powerful enough to deal with
# this; we need heavier artillery.  Extract just the sections that start
# with "tests OK." and end with "Makefile: " for comparison.
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS =	"'/tests OK./ {results = 1}; /Makefile:/ {results = 0} {if (results) print $0 } '"

test:				$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/library/xprofile
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/python/pip-27
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
