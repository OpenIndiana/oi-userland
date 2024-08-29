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
#   $WS_TOOLS/python-integrate-project scikit_build
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scikit_build
HUMAN_VERSION =			0.18.1
COMPONENT_SUMMARY =		Improved build system generator for Python C/C++/Fortran/Cython extensions
COMPONENT_PROJECT_URL =		https://github.com/scikit-build/scikit-build
COMPONENT_ARCHIVE_HASH =	\
	sha256:a4152ac5a084d499c28a7797be0628d8366c336e2fb0e1a063eb32e55efcb8e7
COMPONENT_LICENSE =		BSD-2-Clause OR MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/scikit-build/scikit-build/issues/951
PYTEST_ADDOPTS += -W ignore::DeprecationWarning
# We usually do have setuptools-scm installed so we need to disable tests that
# expect setuptools-scm is not installed.
PYTEST_ADDOPTS += -m 'not nosetuptoolsscm'
# pep518 tests are trying to install numpy using pip, but that fails during
# numpy compilation.
PYTEST_ADDOPTS += -k 'not pep518'
# These tests are trying to install numpy using pip, but that fails because of
# https://github.com/numpy/numpy/issues/25366
PYTEST_ADDOPTS += --ignore tests/test_distribution.py

# Testing needs to compile some C++ sources
COMPONENT_TEST_ENV += CXX="$(CXX)"
# and it also needs fortran
COMPONENT_TEST_ENV += FC="$(FC)"

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/distro
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
