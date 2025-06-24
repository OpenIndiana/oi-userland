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
HUMAN_VERSION =			25.1.1
COMPONENT_SUMMARY =		Composable complex class support for attrs and dataclasses.
COMPONENT_PROJECT_URL =		https://catt.rs
COMPONENT_ARCHIVE_HASH =	\
	sha256:c914b734e0f2d59e5b720d145ee010f1fd9a13ee93900922a2f3f9d593b8382c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# We have no msgspec packaged yet
PYTEST_ADDOPTS += --ignore tests/preconf/test_msgspec_cpython.py
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_literal_dicts_msgspec
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_efficient_enum
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_converter
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_unstruct_collection_overrides
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_json_unions
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_msgspec_native_enums

# We have no cbor2 packaged yet
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_cbor2_efficient_enum
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_cbor2_native_enums

# We have no orjson packaged yet
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_literal_dicts_orjson
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_orjson_efficient_enum
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_orjson_native_enums

# We have no ujson packaged yet
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_ujson_native_enums
PYTEST_ADDOPTS += --deselect tests/test_preconf.py::test_ujson_efficient_enum

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

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
