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
HUMAN_VERSION =			0.9.9
COMPONENT_SUMMARY =		Build backend for CMake based projects
COMPONENT_PROJECT_URL =		https://github.com/scikit-build/scikit-build-core
COMPONENT_ARCHIVE_HASH =	\
	sha256:64880e00c03e196ed2feb66676175dbbafe5fad1081edd9583c30bf6170d2fc9
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find pybind11
COMPONENT_TEST_ENV += CMAKE_PREFIX_PATH=$(shell /usr/bin/pybind11-config-$(PYTHON_VERSION) --cmakedir)

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# When testing finds numpy already pre-installed it tries to install own copy
# of numpy using pip.  This fails because of
# https://github.com/numpy/numpy/issues/25366
TEST_CONFLICTING_PACKAGES.python += library/python/numpy
# When pbr is installed the testing is failing because of the pkg_resources
# DeprecationWarning.
# See also https://bugs.launchpad.net/pbr/+bug/1822332
TEST_CONFLICTING_PACKAGES.python += library/python/pbr

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pathspec
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/cattrs
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pybind11
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subprocess
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
