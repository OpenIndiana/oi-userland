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
#   $WS_TOOLS/python-integrate-project isort
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		isort
HUMAN_VERSION =			6.0.1
COMPONENT_SUMMARY =		A Python utility / library to sort Python imports.
COMPONENT_ARCHIVE_HASH =	\
	sha256:1cb5df28dfbc742e490c5e41bad6da41b805b0a8be7bc93cd0fb2a8a890ac450
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += dev

# We have no hypothesmith packaged yet.
PYTEST_ADDOPTS += --ignore tests/integration/test_hypothesmith.py
# We have no pylama packaged yet.
PYTEST_ADDOPTS += --ignore tests/unit/test_pylama_isort.py

# https://github.com/PyCQA/isort/issues/2129
PYTEST_ADDOPTS += --deselect tests/integration/test_setting_combinations.py::test_isort_is_idempotent
PYTEST_ADDOPTS += --deselect tests/integration/test_setting_combinations.py::test_isort_doesnt_lose_imports_or_comments
PYTEST_ADDOPTS += --deselect tests/unit/test_deprecated_finders.py::TestRequirementsFinder::test_requirements_dir
PYTEST_ADDOPTS += --deselect tests/unit/test_deprecated_finders.py::test_requirements_finder
PYTEST_ADDOPTS += --deselect tests/unit/test_ticketed_features.py::test_isort_supports_shared_profiles_issue_970
PYTEST_ADDOPTS += --deselect tests/unit/test_ticketed_features.py::test_sort_configurable_sort_issue_1732

# https://github.com/PyCQA/isort/issues/2355
PYTEST_ADDOPTS += --deselect tests/unit/test_isort.py::test_cimport_support

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/colorama
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/flake8-bugbear
TEST_REQUIRED_PACKAGES.python += library/python/httpx
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/libcst
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/mypy-extensions
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/toml
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/types-setuptools
TEST_REQUIRED_PACKAGES.python += library/python/types-toml
