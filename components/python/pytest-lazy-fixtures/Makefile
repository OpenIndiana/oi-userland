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
#   $WS_TOOLS/python-integrate-project -d python/pytest-lazy-fixtures pytest_lazy_fixtures
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_lazy_fixtures
HUMAN_VERSION =			1.4.1
COMPONENT_SUMMARY =		Allows you to use fixtures in @pytest.mark.parametrize.
COMPONENT_PROJECT_URL =		https://github.com/dev-petrov/pytest-lazy-fixtures
COMPONENT_ARCHIVE_HASH =	\
	sha256:8684abfd4914ea01f1e2f7b24524739344421d8f3f12286fb3100fb5681e1181
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We have no pytest-deadfixtures packaged
PYTEST_ADDOPTS += --ignore tests/test_deadfixtures_support.py
# We have no pytest-fixture-classes packaged
PYTEST_ADDOPTS += --deselect tests/tests.py::test_fixture_classes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += runtime/python
