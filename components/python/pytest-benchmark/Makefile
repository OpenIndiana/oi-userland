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
#   $WS_TOOLS/python-integrate-project pytest-benchmark
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-benchmark
HUMAN_VERSION =			5.1.0
COMPONENT_SUMMARY =		A \`\`pytest\`\` fixture for benchmarking code. It will group the tests into rounds that are calibrated to the chosen timer.
COMPONENT_PROJECT_URL =		https://github.com/ionelmc/pytest-benchmark
COMPONENT_ARCHIVE_HASH =	\
	sha256:9ea661cdc292e8231f7cd4c10b0319e56a2118e2c09d9f50e1b3d150d2aca105
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We have no pygal packaged yet
PYTEST_ADDOPTS += --deselect tests/test_benchmark.py::test_histogram
PYTEST_ADDOPTS += --deselect tests/test_cli.py::test_compare
PYTEST_ADDOPTS += --deselect tests/test_storage.py::test_rendering
PYTEST_ADDOPTS += --deselect tests/test_storage.py::test_regression_checks
PYTEST_ADDOPTS += --deselect tests/test_storage.py::test_regression_checks_inf
PYTEST_ADDOPTS += --deselect tests/test_storage.py::test_compare_1
PYTEST_ADDOPTS += --deselect tests/test_storage.py::test_compare_2

# We have no aspectlib packaged yet
PYTEST_ADDOPTS += --deselect tests/test_with_testcase.py::TerribleTerribleWayToWritePatchTests::test_foo2
PYTEST_ADDOPTS += --deselect tests/test_with_weaver.py::test_weave_fixture
PYTEST_ADDOPTS += --deselect tests/test_with_weaver.py::test_weave_method

# https://github.com/ionelmc/pytest-benchmark/issues/163
PYTEST_ADDOPTS += --deselect tests/test_utils.py::test_parse_elasticsearch_storage

# https://github.com/fedora-python/tox-current-env/issues/68
PYTEST_ADDOPTS += --deselect tests/test_cli.py::test_hooks

# Drop benchmark reports
COMPONENT_TEST_TRANSFORMS += "-e '/^-\{1,\} benchmark:/,/^$$/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^-\{1,\} cProfile/,/^$$/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/py-cpuinfo
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/elasticsearch
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
