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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project packaging
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		packaging
HUMAN_VERSION =			26.3
COMPONENT_SUMMARY =		Core utilities for Python packages
COMPONENT_ARCHIVE_HASH =	\
	sha256:94edc256424af38762eb31306eed28beb9f0efc50a8837492c9d6fd6004aed79
COMPONENT_LICENSE =		Apache-2.0 OR BSD-2-Clause

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - hatchling (test bootstrap)
# - pyproject_api (test bootstrap)
# - pytest (test bootstrap)
# - setuptools-scm
# - tox (test bootstrap)
# - wheel (test bootstrap)
# - Userland build framework (see setup.py.mk)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pretend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
