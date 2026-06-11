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

USE_PARALLEL_BUILD = yes
USE_CTF = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Python
COMPONENT_VERSION =		3.14.6
PYTHON_VERSION =		$(basename $(COMPONENT_VERSION))
PYV =				$(subst .,,$(PYTHON_VERSION))
COMPONENT_SUMMARY =		The Python interpreter, libraries and utilities
COMPONENT_PROJECT_URL =		https://python.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH =	sha256:143b1dddefaec3bd2e21e3b839b34a2b7fb9842272883c576420d605e9f30c63
COMPONENT_ARCHIVE_URL =		$(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		runtime/python-$(PYV)
COMPONENT_CLASSIFICATION =	Development/Python
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI.idle =		library/python/idle-$(PYV)
COMPONENT_SUMMARY.idle =	Python $(PYTHON_VERSION) IDLE (Integrated Development and Learning Environment)

COMPONENT_FMRI.tkinter =	library/python/tkinter-$(PYV)
COMPONENT_SUMMARY.tkinter =	Python $(PYTHON_VERSION) bindings to tcl/tk

include $(WS_MAKE_RULES)/common.mk

# Without this several tests fails
CFLAGS += $(XPG6MODE)

# This is needed to make sure our Setup.local is really used
CLONEY_MODE = copy

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-optimizations
CONFIGURE_OPTIONS += --enable-loadable-sqlite-extensions
CONFIGURE_OPTIONS += --without-static-libpython
CONFIGURE_OPTIONS += --with-system-expat
CONFIGURE_OPTIONS += --with-dtrace
CONFIGURE_OPTIONS += --without-ensurepip

# Make sure dynamic libraries are placed at their usual location
COMPONENT_INSTALL_ARGS += BINLIBDEST=$(PYTHON_DIR)

# Support for the vendor-packages directory.
# https://github.com/python/cpython/issues/42401
COMPONENT_POST_INSTALL_ACTION += \
	echo "import site; site.addsitedir('$(PYTHON_VENDOR_PACKAGES)')" > $(PROTOPYTHONSITEDIR)/vendor-packages.pth ;

# Strip build machine paths from _sysconfigdata.py & config/Makefile,
# then (re)compile _sysconfigdata.py since we just updated it.
COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTO_DIR)/$(PYTHON_DIR) ; \
	$(GSED) -i -e 's|$(SOURCE_DIR)|.|g' -e 's|$(COMPONENT_DIR)|..|g' \
		_sysconfigdata__sunos5_.py config-$(PYTHON_VERSION)/Makefile ; \
	LD_LIBRARY_PATH=$(PROTOUSRLIBDIR.$(BITS)) $(PROTO_DIR)$(PYTHON) -m py_compile _sysconfigdata__sunos5_.py ) ;

# Create symlinks without ending '3' for binaries
COMPONENT_POST_INSTALL_ACTION += \
	for f in idle pydoc python ; do \
		$(SYMLINK) $${f}$(PYTHON_VERSION) $(PROTOUSRBINDIR)/$$f ; \
	done ; \
	$(SYMLINK) python$(PYTHON_VERSION)-config $(PROTOUSRBINDIR)/python-config ;

# Create symlink without ending '3' for the man page
COMPONENT_POST_INSTALL_ACTION += \
	$(SYMLINK) python$(PYTHON_VERSION).1 $(PROTOUSRSHAREMAN1DIR)/python.1 ;

# Allow mediated libpython3.so stable ABI
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRLIBDIR.$(BITS))/libpython3.so $(PROTOUSRLIBDIR.$(BITS))/libpython$(PYV).so ; \
	$(SYMLINK) libpython$(PYV).so $(PROTOUSRLIBDIR.$(BITS))/libpython3.so ;

# You can set TESTOPTS_PYTHON_TEST to a particular test if you want to run just
# one test.  For example:
# $ TESTOPTS_PYTHON_TEST=test_sys
TESTOPTS_PYTHON_TEST =

# Using "-uall,-network" ensures all tests are run except the network tests.
# The network tests contain many expected failures when run behind a firewall.
# The "-v" ensures verbose mode.
COMPONENT_TEST_ENV += EXTRATESTOPTS="-v -uall,-network $(TESTOPTS_PYTHON_TEST)"

# Override default test target.  See README.rst.
COMPONENT_TEST_TARGETS = test

# Custom test transforms
COMPONENT_TEST_TRANSFORMS =
# Drop the slowest test list
COMPONENT_TEST_TRANSFORMS += "-e '/slowest/,/^\$$/d'"
# Convert test lists to contain one test per line only
COMPONENT_TEST_TRANSFORMS += "-e '/^    /s/\([^ ]\) /\\1\\\\n    /g'"
# Print the test results summary only
COMPONENT_TEST_TRANSFORMS += -n
COMPONENT_TEST_TRANSFORMS += "-e '/^== Test/,/OK/p'"

# Testing fails with tzdata installed
TEST_CONFLICTING_PACKAGES.python += library/python/tzdata

# Allow 'pkgdepend generate' to run the currently built Python
PKGDEPEND_GENERATE_ENV += PATH="$(PROTOUSRBINDIR):$(PATH)"
PKGDEPEND_GENERATE_ENV += LD_LIBRARY_PATH=$(PROTOUSRLIBDIR.64)

# Replace Python version by $(PYVER) really everywhere.  The default transforms
# misses some occurrences.  Also replace the stripped down Python version by
# $(PYV).
PYVER_RE = $(subst .,\.,$(PYTHON_VERSION))
GENERATE_EXTRA_SED += -e 's/$(PYVER_RE)/$$(PYVER)/g'
GENERATE_EXTRA_SED += -e 's/$(PYV)/$$(PYV)/g'

# PYVER_RE is needed to process manifests
PKG_VARS += PYVER_RE

# Need to preserve timestamp for Grammar files.  If the pickle files are older,
# Python will try to rebuild them.
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.txt
PKGSEND_PUBLISH_OPTIONS += -T \*Grammar\*.pickle

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/math/libmpdec2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
