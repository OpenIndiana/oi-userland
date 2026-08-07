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

# fewer tests fail
ENV = /usr/bin/env

# OPENSSL_VERSION= 3.1
USE_PARALLEL_BUILD = yes
USE_CTF=yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        Python
COMPONENT_VERSION=      3.13.15
PYTHON_VERSION =	$(subst $(space),.,$(wordlist 1,2,$(subst ., ,$(COMPONENT_VERSION))))
COMPONENT_SUMMARY=      The Python interpreter, libraries and utilities
COMPONENT_PROJECT_URL=  https://python.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:1e66a7945a48390ee4c2a4268a0e4185884059a13c4aab6d148aa208deea4a76
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

# fewer tests fail
PKG_CONFIG_PATHS += /usr/openssl/3.1/lib/amd64/pkgconfig

# We patch auto* files, so regenerate headers and configure
COMPONENT_PREP_ACTION = (cd $(@D) ; autoheader ; autoconf -f)

# we don't want to leak $(CC_BITS) into BASECFLAGS as it causes problems with
# python-config
CC += $(CFLAGS)

gcc_OPT = -O2

CPPFLAGS += -IPython

# Needed to find right openssl
CPPFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

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

# Save arguments to the stack so that the mdb/pstack plugin can find them.
CFLAGS += -msave-args

# The python build is profile-guided for gcc.  Use of xprofile requires that
# the same options be used during compilation and linking.  The targets chosen
# are based on Solaris 11 minimum supported system requirements.
XPROFILE_DIR= $(BUILD_DIR_$(BITS))/.profile
PYFLAGS = -march=opteron -fno-semantic-interposition
CFLAGS += $(PYFLAGS.$(MACH))
LDFLAGS += $(PYFLAGS.$(MACH))

# Python puts its header files in a special place.
LINT_FLAGS += -I$(SOURCE_DIR)/Include
# C11 atomic intrinsics cause our linter to fail (see 37651387). Forcing
# Py_LIMITED_API works around that issue and provides at least limited coverage.
LINT_FLAGS += -DPy_LIMITED_API

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
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += DFLAGS="-$(BITS)"
CONFIGURE_OPTIONS += XPROFILE_DIR="$(XPROFILE_DIR)"

COMPONENT_BUILD_ENV += DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV += XPROFILE_DIR="$(XPROFILE_DIR)"

CONFIGURE_OPTIONS += "ac_cv_func_getentropy=no"
CONFIGURE_OPTIONS += "ac_cv_file__dev_ptmx=yes"
CONFIGURE_OPTIONS += "ac_cv_file__dev_ptc=no"

# hstrerror() is present in -lresolv, but if configure decides it's available
# then it uses it in a number of modules, which then don't link.
# Versions of Python < 3.11 did not detect this function but the new checks
# in 3.11 are less robust and think it's there even when it isn't.
# https://github.com/python/cpython/issues/89886#issuecomment-1106100113
CONFIGURE_OPTS+=" ac_cv_func_hstrerror=no"

# Our newly introduced implementation of pthread_getcpuclockid and other
# related functions is problematic because when called on the current thread,
# it returns reserved value 'CURRENT_THREAD' and thus cannot be passed to
# other threads. While not necessarily against the standard, it is different
# from Linux Kernel and might cause problems.
CONFIGURE_OPTIONS += "ac_cv_func_pthread_getcpuclockid=no"

# On Solaris, we need -lncurses to link with readline.
# Also insert '-zrecord' before the readline libraries that we
# want to link with to avoid rl_insert() elimination
CONFIGURE_OPTIONS += LIBREADLINE_LIBS="-Wl,-zrecord -lreadline -lncurses"

COMPONENT_BUILD_ENV += DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV += XPROFILE_DIR="$(XPROFILE_DIR)"
COMPONENT_BUILD_ENV += PATH="$(PATH)"

# Some tests have non-ASCII characters encoded for international domain names;
# the publish step will fail in 'pkgdepend generate' without this:
COMPONENT_PUBLISH_ENV += LC_ALL=en_US.UTF-8

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

GCC_GNU_SHORT_TRIPLET = $(shell $(GCC_ROOT)/bin/gcc -dumpmachine | /usr/bin/sed -E 's/\.[0-9]+$$//')

# Strip build machine paths from _sysconfigdata.py & config/Makefile,
# then (re)compile _sysconfigdata.py since we just updated it.
# Note that once Python 3.9 has been integrated and propagated to build
# machines, then the LD_LIBRARY_PATH setting and PROTO_DIR prefix below
# can both be removed.
COMPONENT_POST_INSTALL_ACTION= \
    (cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
     $(GSED) -i -e 's|$(SOURCE_DIR)|.|g' -e 's|$(COMPONENT_DIR)|..|g' \
    -e 's|$(SPRO_VROOT)/bin/||g' _sysconfigdata__sunos5_$(GCC_GNU_SHORT_TRIPLET).py config-$(PYTHON_VERSION)-$(GCC_GNU_SHORT_TRIPLET)/Makefile; \
    LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64) $(PROTO_DIR)$(PYTHON) -m py_compile _sysconfigdata__sunos5_$(GCC_GNU_SHORT_TRIPLET).py) ;

# Create symlinks without ending '3' for binaries
COMPONENT_POST_INSTALL_ACTION += \
	for f in idle pydoc python ; do \
		$(SYMLINK) $${f}$(PYTHON_VERSION) $(PROTOUSRBINDIR)/$$f ; \
	done ; \
	$(SYMLINK) python$(PYTHON_VERSION)-config $(PROTOUSRBINDIR)/python-config ;

# Allow mediated libpython3.so stable ABI
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR.$(BITS))/libpython3.so $(PROTOUSRLIBDIR.$(BITS))/libpython$(subst .,,$(PYTHON_VERSION)).so ; \
	$(SYMLINK) libpython$(subst .,,$(PYTHON_VERSION)).so $(PROTOUSRLIBDIR.$(BITS))/libpython3.so ;

# Add missing files/folders that break processing of gmake REQUIRED_PACKAGES
COMPONENT_POST_INSTALL_ACTION += \
	touch $(PROTO_DIR)/usr/lib/python3.13/test/tokenizedata/__pycache__/bad_coding.cpython-313.pyc ; \
	touch $(PROTO_DIR)/usr/lib/python3.13/test/tokenizedata/__pycache__/bad_coding2.cpython-313.pyc ; \
	touch $(PROTO_DIR)/usr/lib/python3.13/test/tokenizedata/__pycache__/badsyntax_3131.cpython-313.pyc ; \
	touch $(PROTO_DIR)/usr/lib/python3.13/test/tokenizedata/__pycache__/badsyntax_pep3120.cpython-313.pyc ; \
	touch $(PROTO_DIR)/usr/lib/python3.13/test/test_future_stmt/__pycache__/badsyntax_future.cpython-313.pyc ; \
	mkdir $(PROTO_DIR)/usr/lib/python3.13/config-3.13-x86_64-pc-solaris2/__pycache__ ; \
	touch $(PROTO_DIR)/usr/lib/python3.13/config-3.13-x86_64-pc-solaris2/__pycache__/python-config.cpython-313.pyc ;

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

# fewer tests fail
COMPONENT_TEST_ENV += SETUPTOOLS_USE_DISTUTILS=stdlib

# The test output contains details from each test, in whatever order they
# complete.  The default _TRANSFORMER is not powerful enough to deal with
# this. Capture minimal necessary output from both first run and re-run.
COMPONENT_TEST_TRANSFORMS +=    "-n -e '/\(tests OK.$$\|tests failed:$$\)/p'"

# Required for dump(1)
REQUIRED_PACKAGES += developer/object-file
# Required to build ossaudiodev module
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/math/libmpdec2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
