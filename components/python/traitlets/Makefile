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
#   $WS_TOOLS/python-integrate-project traitlets
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		traitlets
HUMAN_VERSION =			5.16.1
COMPONENT_SUMMARY =		Traitlets Python configuration system
COMPONENT_PROJECT_URL =		https://github.com/ipython/traitlets
COMPONENT_ARCHIVE_HASH =	\
	sha256:ed900c2b631aa3a112811139fa97b8d2c3bad5e989656bba4b7e52c7852c18c1
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported traitlets >= 5.16.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# https://github.com/ipython/traitlets/issues/925
PYTEST_ADDOPTS += --deselect tests/config/test_argcomplete.py::TestArgcomplete::test_complete_simple_app
PYTEST_ADDOPTS += --deselect tests/config/test_argcomplete.py::TestArgcomplete::test_complete_custom_completers
PYTEST_ADDOPTS += --deselect tests/config/test_argcomplete.py::TestArgcomplete::test_complete_subcommands_subapp1

# Testing needs to find the tests module in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/argcomplete
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
