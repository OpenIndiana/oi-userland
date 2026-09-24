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
#   $WS_TOOLS/python-integrate-project multidict
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		multidict
HUMAN_VERSION =			6.9.1
COMPONENT_SUMMARY =		multidict implementation
COMPONENT_PROJECT_URL =		https://github.com/aio-libs/multidict
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f06e60fa190aa7abd0914c2a766736fdc8e9f34878c4346338534b73d1b20e2
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported by multidict >= 6.8.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements/pytest.txt

# We have no pytest-codspeed packaged yet
PYTEST_ADDOPTS += --ignore tests/test_multidict_benchmarks.py
PYTEST_ADDOPTS += --ignore tests/test_views_benchmarks.py

# This test needs coverage
PYTEST_ADDOPTS += --deselect tests/test_leaks.py::test_leak

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
