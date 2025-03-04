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
#   $WS_TOOLS/python-integrate-project -d python/inline-snapshot inline_snapshot
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		inline_snapshot
HUMAN_VERSION =			0.20.4
COMPONENT_SUMMARY =		golden master/snapshot/approval testing library which puts the values right into your source code
COMPONENT_PROJECT_URL =		https://15r10nk.github.io/inline-snapshot/latest
COMPONENT_ARCHIVE_HASH =	\
	sha256:6f353b1893b60ad6d3134f215d527fe507df01e5e1155cd3c2d7242bde451e4d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses hatch to manage test dependencies.
TEST_REQUIREMENTS_HATCH += hatch-test

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Normalize the order of elements in the list
COMPONENT_TEST_TRANSFORMS += "-e 's/<update, fix>/<fix, update>/'"

# https://github.com/15r10nk/inline-snapshot/issues/126
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist

# https://github.com/15r10nk/inline-snapshot/issues/206
PYTEST_ADDOPTS += --deselect tests/test_formating.py::test_format_command_fail

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/asttokens
PYTHON_REQUIRED_PACKAGES += library/python/executing
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/rich
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/dirty-equals
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-freezer
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
