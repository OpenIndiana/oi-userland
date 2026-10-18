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
#   $WS_TOOLS/python-integrate-project -d python/pytest-mock pytest_mock
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_mock
HUMAN_VERSION =			3.17.0
COMPONENT_SUMMARY =		Thin-wrapper around the mock package for easier use with pytest
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-mock/
COMPONENT_ARCHIVE_HASH =	\
	sha256:e36576e0985e01027e999891e7a966c67822d40c89ef1b4c8b6e22737e3590b4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by pytest-mock >= 3.16.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

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
