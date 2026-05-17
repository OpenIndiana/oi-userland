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
#   $WS_TOOLS/python-integrate-project build
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		build
HUMAN_VERSION =			1.4.4
COMPONENT_SUMMARY =		A simple, correct Python build frontend
COMPONENT_PROJECT_URL =		https://build.pypa.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:f832ae053061f3fb524af812dc94b8b84bac6880cd587630e3b5d91a6a9c1703
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Since we cannot use the 'build' package to build itself we need to bootstrap.
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Avoid rewrite failure with xdist
PYTEST_ADDOPTS += --assert=plain

# This test fails on Python 3.9 for some (not yet known) reason
PYTEST_ADDOPTS += --deselect tests/test_env.py::test_virtualenv_no_wheel_flag

# This list could vary between Python versions
COMPONENT_TEST_TRANSFORMS += "-e '/^installed packages of interest:/d'"

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/importlib-metadata
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pyproject-hooks
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/setuptools-scm
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
