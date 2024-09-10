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
#   $WS_TOOLS/python-integrate-project cattrs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cattrs
HUMAN_VERSION =			24.1.0
COMPONENT_SUMMARY =		Composable complex class support for attrs and dataclasses.
COMPONENT_PROJECT_URL =		https://catt.rs
COMPONENT_ARCHIVE_HASH =	\
	sha256:8274f18b253bf7674a43da851e3096370d67088165d23138b04a1c04c8eaf48e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This project uses pdm to manage test dependencies.
TEST_REQUIREMENTS_PDM += test

# We have no msgspec packaged yet
PYTEST_ADDOPTS += --ignore tests/preconf/test_msgspec_cpython.py
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_converter
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_unstruct_collection_overrides
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_unions

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/immutables
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
