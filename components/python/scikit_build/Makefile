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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scikit_build
HUMAN_VERSION =			0.17.5
COMPONENT_SUMMARY =		scikit_build - Improved build system generator for Python C/C++/Fortran/Cython extensions
COMPONENT_PROJECT_URL =		https://github.com/scikit-build/scikit-build
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f8/23/a07369d9095648b61a302cd45c9661ef2d92fe546e0eb28a467c66c7c1d3/scikit_build-0.17.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:76856e7631d9e8887a7aa71913d5f184a6177246225391af96ce4801d89fa254
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

# Testing needs to compile some C++ sources
COMPONENT_TEST_ENV += CXX="$(CXX)"
# and it also needs fortran
COMPONENT_TEST_ENV += FC="$(FC.gcc.$(BITS))"

# Python 3.7 test results contains process pids
COMPONENT_TEST_TRANSFORMS += "-e 's/\(subprocess \)[0-9]\{1,\}\( is still running\)/\1\$$(PID)\2/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/distro
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
