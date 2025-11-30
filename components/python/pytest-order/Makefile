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
#   $WS_TOOLS/python-integrate-project -d python/pytest-order pytest_order
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_order
HUMAN_VERSION =			1.3.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pytest plugin to run your tests in a specific order
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-order
COMPONENT_ARCHIVE_HASH =	\
	sha256:51608fec3d3ee9c0adaea94daa124a5c4c1d2bb99b00269f098f414307f23dde
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This test does not work with tox-current-env
PYTEST_ADDOPTS += --deselect tests/test_xdist_handling.py::test_xdist_ordering

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-dependency
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
