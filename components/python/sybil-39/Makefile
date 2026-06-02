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
#   $WS_TOOLS/python-integrate-project -d python/sybil-39 sybil
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sybil
HUMAN_VERSION =			9.3.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Automated testing for the examples in your code and documentation.
COMPONENT_PROJECT_URL =		https://github.com/simplistix/sybil
COMPONENT_ARCHIVE_URL =		\
	https://github.com/simplistix/sybil/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:000bb402d06894f03ac7102d3952f3550b6b7adedb06ee79338c4c7fd1becc25
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# sybil >= 10.0.0 requires Python >= 3.11
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Test results order varies between runs
PYTEST_SORT_TESTS = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/seedir
TEST_REQUIRED_PACKAGES.python += library/python/testfixtures
TEST_REQUIRED_PACKAGES.python += library/python/types-pyyaml
