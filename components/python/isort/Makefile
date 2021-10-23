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
# Copyright 2021 Gary Mills
#

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		isort
COMPONENT_VERSION=	5.9.3
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://github.com/PyCQA/isort
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:0ad5e0ec066302c7aece422b2675b81abe7e417dbf64b18438ca8b79219540dd
COMPONENT_ARCHIVE_URL=	https://github.com/PyCQA/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	python-mod/isort

# Set python version used by this product
PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

# Copy in a minimal setup.py
COMPONENT_PRE_BUILD_ACTION = $(CP) OI/setup.py $(COMPONENT_SRC)

# The tests are run using python 3.9 only and require that the
# python-39 package is installed (does not have to be the default python).
# The pytest-39, hypothesis-39, and sortedcontainers-39 packages must
# also be installed

# Use the python 3.9 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=3.9

COMPONENT_TEST_DIR = $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD = $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Disable test files that have import failures because these python
# modules are not available in OI: libcst colorama pylama black
COMPONENT_PRE_TEST_ACTION = \
( cd $(COMPONENT_TEST_DIR); \
  for F in integration/test_hypothesmith.py unit/test_format.py unit/test_pylama_isort.py unit/profiles/test_black.py; \
  do \
    test -f $$F && $(MV) $$F $$F-not; \
  done )

# Typical failures for test target:
#============================ short test summary info ============================
#FAILED integration/test_setting_combinations.py::test_isort_is_idempotent - is...
#FAILED integration/test_setting_combinations.py::test_isort_doesnt_lose_imports_or_comments
#...
#FAILED unit/test_ticketed_features.py::test_isort_literals_issue_1358 - isort....
#FAILED unit/test_ticketed_features.py::test_sort_configurable_sort_issue_1732
#ERROR benchmark/test_api.py::test_sort_file
#ERROR benchmark/test_api.py::test_sort_file_in_place
#ERROR unit/test_main.py::test_sort_imports_error_handling
#= 13 failed, 502 passed, 1 skipped, 76 warnings, 3 errors in 329.14s (0:05:29) ==

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-39
