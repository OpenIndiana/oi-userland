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
# Copyright (c) 2011, 2020, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Aurelien Larcher
#

# hold at openssl 1.1 until test failures with 3.1 are root-caused.
USE_OPENSSL11= yes
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        Python
COMPONENT_VERSION=      3.12.2
PYTHON_VERSION =	$(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(COMPONENT_VERSION))))
COMPONENT_SUMMARY=      The Python interpreter, libraries and utilities
COMPONENT_PROJECT_URL=  https://python.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:be28112dac813d2053545c14bf13a16401a21877f1a69eb6ea5d84c4a0f3d870
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		runtime/python-$(subst .,,$(PYTHON_VERSION))
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_LICENSE=      PSF-2.0
COMPONENT_LICENSE_FILE=	LICENSE

COMPONENT_FMRI.idle =		library/python/idle-$(subst .,,$(PYTHON_VERSION))
COMPONENT_SUMMARY.idle =	Python $(PYTHON_VERSION) IDLE (Integrated Development and Learning Environment)

COMPONENT_FMRI.tkinter =	library/python/tkinter-$(subst .,,$(PYTHON_VERSION))
COMPONENT_SUMMARY.tkinter =	Python $(PYTHON_VERSION) bindings to tcl/tk

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Need to preserve timestamp for Grammar files.  If the pickle files are older,
# Python will try to rebuild them.
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.txt
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.pickle

# We patch auto* files, so regenerate headers and configure
COMPONENT_PREP_ACTION = (cd $(@D) ; autoheader ; autoconf -f)

# we don't want to leak $(CC_BITS) into BASECFLAGS as it causes problems with
# python-config
CC += $(CFLAGS)

gcc_OPT = -O2

CPPFLAGS += -IPython

# to find the ncurses headers
CPPFLAGS += -I/usr/include/ncurses

# libffi for _ctypes
CPPFLAGS += $(shell pkg-config --cflags-only-I libffi)

# because python links with $(CC) ... $(LDFLAGS) ...
LDFLAGS = $(CC_BITS) $(CC_PIC)

# build pic
CFLAGS += $(CC_PIC)
CFLAGS += $(CFLAGS.$(MACH))

# XPG6
CFLAGS += $(CPP_XPG6MODE)

# The python build is profile-guided for gcc.  Use of xprofile requires that
# the same options be used during compilation and linking.  The targets chosen
# are based on Solaris 11 minimum supported system requirements.
XPROFILE_DIR= $(BUILD_DIR_$(BITS))/.profile

# Configure script should look into sbin folder when looking for dtrace
CONFIGURE_ENV += PATH="$(PATH):/usr/sbin"

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-optimizations
CONFIGURE_OPTIONS += --enable-loadable-sqlite-extensions
CONFIGURE_OPTIONS += --with-dtrace
CONFIGURE_OPTIONS += --with-system-expat
CONFIGURE_OPTIONS += --without-ensurepip
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --with-c-locale-coercion
CONFIGURE_OPTIONS += --bindir=$(USRBINDIR)
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS) -DSKIP_ZIP_PATH "
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += DFLAGS="-$(BITS)"
CONFIGURE_OPTIONS += XPROFILE_DIR="$(XPROFILE_DIR)"

COMPONENT_BUILD_ENV += DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV += XPROFILE_DIR="$(XPROFILE_DIR)"

# 64 bit shared objects need to go in a 64-bit directory
COMPONENT_INSTALL_ARGS += DESTSHARED=$(CONFIGURE_PREFIX)/lib/python$(PYTHON_VERSION)/lib-dynload

# Simplify the definitions of CC, CXX, CFLAGS and LDFLAGS so they hard-code
# neither paths from our build systems nor Studio-specific options.
COMPONENT_PRE_INSTALL_ACTION= \
    (cd $(@D) ; \
    $(GSED) -i -e 's/^CC=.*/CC=\t\tgcc/' -e 's/^CXX=.*/CXX=\t\tg++/' \
    -e 's/^CFLAGS=.*/CFLAGS=\t\t\$$\(BASECFLAGS) \$$\(OPT) \$$\(EXTRA_CFLAGS)/' \
    -e 's|^LDFLAGS=.*|LDFLAGS=|' Makefile)

# Because we stripped the Makefile above, we need to pass several things in the
# environment, and use -e to tell gmake to pay attention to the environment.
COMPONENT_INSTALL_ENV  += CC="$(CC)"
COMPONENT_INSTALL_ENV  += CXX="$(CXX)"
COMPONENT_INSTALL_ENV  += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV  += LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ARGS += -e

# Strip build machine paths from _sysconfigdata.py & config/Makefile,
# then (re)compile _sysconfigdata.py since we just updated it.
# Note that once Python 3.9 has been integrated and propagated to build
# machines, then the LD_LIBRARY_PATH setting and PROTO_DIR prefix below
# can both be removed.
COMPONENT_POST_INSTALL_ACTION= \
    (cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
     $(GSED) -i -e 's|$(SOURCE_DIR)|.|g' -e 's|$(COMPONENT_DIR)|..|g' \
    -e 's|$(SPRO_VROOT)/bin/||g' _sysconfigdata__sunos5_.py config-$(PYTHON_VERSION)/Makefile; \
    LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64) $(PROTO_DIR)$(PYTHON.$(PYTHON_VERSION).$(BITS)) -m py_compile _sysconfigdata__sunos5_.py) ;

# Create symlinks without ending '3' for binaries
COMPONENT_POST_INSTALL_ACTION += \
	for f in idle pydoc python python-config ; do \
		$(SYMLINK) $${f}$(PYTHON_VERSION) $(PROTOUSRBINDIR)/$$f ; \
	done ;

# Allow mediated libpython3.so stable ABI
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR.$(BITS))/libpython3.so $(PROTOUSRLIBDIR.$(BITS))/libpython$(subst .,,$(PYTHON_VERSION)).so ; \
	$(SYMLINK) libpython$(subst .,,$(PYTHON_VERSION)).so $(PROTOUSRLIBDIR.$(BITS))/libpython3.so ;

# You can set TESTOPTS_PYTHON_TEST to a particular test if you want to run just
# one test.  For example:
# $ TESTOPTS_PYTHON_TEST=test_sys
TESTOPTS_PYTHON_TEST=

# Using "-uall,-network" ensures all tests are run except the network tests.
# The network tests contain many expected failures when run behind a firewall.
# The "-v" ensures verbose mode.
COMPONENT_TEST_ENV += EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"

# Override default test target.  See README.rst.
COMPONENT_TEST_TARGETS = test

# The test output contains details from each test, in whatever order they
# complete.  The default _TRANSFORMER is not powerful enough to deal with
# this; we need heavier artillery.  Extract just the sections that start
# with "tests OK." and end with "Re-running failed tests..." for comparison.
COMPONENT_TEST_TRANSFORMER= $(NAWK)
COMPONENT_TEST_TRANSFORMS= "'/tests OK./ {results = 1}; /Total duration/ {results = 0}; /Re-running failed tests in verbose mode/ {results = 0} {if (results) print $0 }'"

# Required for dump(1)
REQUIRED_PACKAGES += developer/object-file
# Required to build ossaudiodev module
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
