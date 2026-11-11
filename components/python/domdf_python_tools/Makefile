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
#   $WS_TOOLS/python-integrate-project domdf_python_tools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		domdf_python_tools
HUMAN_VERSION =			3.11.0
COMPONENT_SUMMARY =		Helpful functions for Python
COMPONENT_PROJECT_URL =		https://github.com/domdfcoding/domdf_python_tools
COMPONENT_ARCHIVE_URL =		\
	https://github.com/domdfcoding/domdf_python_tools/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:80e813cc2eba3424da17e544c1cc560aa878c95ce657ec6d4967b24341920c47
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# domdf_python_tools --> coincidence ==> whey ==> domdf_python_tools
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/domdfcoding/domdf_python_tools/issues/82
PYTEST_ADDOPTS += --deselect tests/test_import_tools.py::test_discover_entry_points_by_name_object_match_func
PYTEST_ADDOPTS += --deselect tests/test_import_tools.py::test_discover_entry_points_by_name_name_match_func
PYTEST_ADDOPTS += --deselect tests/test_import_tools.py::test_discover_entry_points

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x0\*[0-9a-f]\{12\}/\$$(POINTER)/g'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-requirements-txt
REQUIRED_PACKAGES.python += library/python/natsort
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/click
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/consolekit
TEST_REQUIRED_PACKAGES.python += library/python/faker
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/funcy
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytz
