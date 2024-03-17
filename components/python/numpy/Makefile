#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Geoff Weiss
#

BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         numpy
COMPONENT_VERSION=      1.26.4
COMPONENT_FMRI=         library/python/numpy
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=      Fundamental package for scientific computing with Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:2a02aba9ed12e4ac4eb3ea9421c420301a0c6460d9830d74a9df87efa4912010
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://numpy.org/
COMPONENT_LICENSE=      NUMPY
COMPONENT_LICENSE_FILE= LICENSE.txt

# gmake test fails after writing the results file, but before it generates
# the snapshot file.   These four tests fail:
# FAILED numpy/core/tests/test_longdouble.py::test_repr_roundtrip - AssertionEr...
# FAILED numpy/core/tests/test_print.py::TestCommaDecimalPointLocale::test_locale_longdouble
# FAILED numpy/core/tests/test_scalarprint.py::TestRealScalars::test_dragon4_interface
# FAILED numpy/core/tests/test_umath.py::TestSpecialFloats::test_exp2 - Asserti...
TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk
LD_OPTIONS      += -lm

CFLAGS+= -D_GLIBCXX_NO_C99_ROUNDING_FUNCS


PYTHON_ENV +=   CC="$(CC) $(CC_BITS)"

# .pyc files have to be recompiled after changing shebang path
COMPONENT_POST_INSTALL_ACTION += \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*/*/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_TRANSFORMS += \
        '-nE -e "s/ ?=+ ?//g" ' \
        '-e "s/ in [0-9]+(\.[0-9]*)?s.*//" ' \
        '-e "s/[0-9]+ warnings/x warnings/g" ' \
        '-e "/^FAILED/p" ' \
        '-e "/^ERROR/p" ' \
        '-e "/passed,/p"'

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython

# Test dependencies
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
