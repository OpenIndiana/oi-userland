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
#   $WS_TOOLS/python-integrate-project pydantic
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic
HUMAN_VERSION =			2.9.2
COMPONENT_SUMMARY =		Data validation using Python type hints
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic
COMPONENT_ARCHIVE_HASH =	\
	sha256:d155cef71265d1e9807ed1c32b4c8deec042a44a50a4188b25ac67ecd81a9c0f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses pdm to manage test dependencies.
TEST_REQUIREMENTS_PDM += testing
# Additional extras are needed for tests too
TEST_REQUIREMENTS_EXTRAS += email

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# We do not have pytest-examples packaged yet
PYTEST_ADDOPTS += --ignore tests/test_docs.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/annotated-types
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/pydantic-core
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cloudpickle
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/dirty-equals
TEST_REQUIRED_PACKAGES.python += library/python/email-validator
TEST_REQUIRED_PACKAGES.python += library/python/eval-type-backport
TEST_REQUIRED_PACKAGES.python += library/python/faker
TEST_REQUIRED_PACKAGES.python += library/python/jsonschema
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytz
