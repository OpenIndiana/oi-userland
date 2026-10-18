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
#   $WS_TOOLS/python-integrate-project -d python/pytest-mock-39 pytest_mock
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_mock
HUMAN_VERSION =			3.15.1
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Thin-wrapper around the mock package for easier use with pytest
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-mock/
COMPONENT_ARCHIVE_HASH =	\
	sha256:1849a238f6f396da19762269de72cb1814ab44416fa73a8686deac10b0d87a0f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# pytest-mock >= 3.16.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest-mock/issues/240
PYTEST_ADDOPTS += --assert=plain

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
