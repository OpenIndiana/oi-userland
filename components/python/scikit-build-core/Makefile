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
#   $WS_TOOLS/python-integrate-project -d python/scikit-build-core scikit_build_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scikit_build_core
HUMAN_VERSION =			1.0.3
COMPONENT_SUMMARY =		Build backend for CMake based projects
COMPONENT_PROJECT_URL =		https://github.com/scikit-build/scikit-build-core
COMPONENT_ARCHIVE_HASH =	\
	sha256:a4d7a05978ee37975c37743510c8991e2debce7ef83afb0a07c0c576fd4f16e8
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# scikit-build-core --> pybind11 ==> scikit-build-core
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find pybind11
COMPONENT_TEST_ENV += CMAKE_PREFIX_PATH=$(shell /usr/bin/pybind11-config-$(PYTHON_VERSION) --cmakedir)

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test-parallel
TEST_REQUIREMENTS_PEP735 += test-pybind11

# When testing finds numpy already pre-installed it tries to install own copy
# of numpy using pip.  This fails because of
# https://github.com/numpy/numpy/issues/25366
TEST_CONFLICTING_PACKAGES.python += library/python/numpy
# When pbr is installed the testing is failing because of the pkg_resources
# DeprecationWarning.
# See also https://bugs.launchpad.net/pbr/+bug/1822332
TEST_CONFLICTING_PACKAGES.python += library/python/pbr
# The validate-pyproject causes the
# tests/test_schema.py::test_valid_schemas_files test to fail.
TEST_CONFLICTING_PACKAGES.python += library/python/validate-pyproject

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/exceptiongroup
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pathspec
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/cattrs
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/hatch-vcs
TEST_REQUIRED_PACKAGES.python += library/python/hatchling
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pybind11
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subprocess
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
