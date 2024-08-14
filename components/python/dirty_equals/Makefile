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
#   $WS_TOOLS/python-integrate-project dirty_equals
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dirty_equals
HUMAN_VERSION =			0.8.0
COMPONENT_SUMMARY =		Doing dirty (but extremely useful) things with equals.
COMPONENT_PROJECT_URL =		https://github.com/samuelcolvin/dirty-equals
COMPONENT_ARCHIVE_HASH =	\
	sha256:798db3b9481b9a5024c0e520946507676ed2f0c65317d3e95bdce1a01657cf60
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# dirty_equals --> pydantic --> dirty_equals
# dirty_equals --> pydantic ==> pydantic_core --> dirty_equals
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements/tests.in
TEST_REQUIREMENTS_EXTRAS += pydantic

# We do not have pytest-examples packaged yet.
PYTEST_ADDOPTS += --ignore tests/test_docs.py

# This is needed for few tests to pass
# See also https://github.com/samuelcolvin/dirty-equals/issues/97
COMPONENT_TEST_ENV += TZ=UTC

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pydantic
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytz
TEST_REQUIRED_PACKAGES.python += library/python/tomli
