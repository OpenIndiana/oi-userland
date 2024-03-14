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
HUMAN_VERSION =			0.17.6
COMPONENT_SUMMARY =		scikit_build - Improved build system generator for Python C/C++/Fortran/Cython extensions
COMPONENT_PROJECT_URL =		https://github.com/scikit-build/scikit-build
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/85/05/dc8f28b19f3f06b8a157a47f01f395444f0bae234c4d44674453fa7eeae3/scikit_build-0.17.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b51a51a36b37c42650994b5047912f59b22e3210b23e321f287611f9ef6e5c9d
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
# Testing fails to start with black plugin
PYTEST_ADDOPTS += -p no:black
# Testing fails with cov plugin
PYTEST_ADDOPTS += -p no:cov
# https://github.com/scikit-build/scikit-build/issues/1006
PYTEST_ADDOPTS += -p no:mypy

# Testing needs to compile some C++ sources
COMPONENT_TEST_ENV += CXX="$(CXX)"
# and it also needs fortran
COMPONENT_TEST_ENV += FC="$(FC)"

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
