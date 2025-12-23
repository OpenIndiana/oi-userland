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
#   $WS_TOOLS/python-integrate-project graphviz
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		graphviz
HUMAN_VERSION =			0.21
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Simple Python interface for Graphviz
COMPONENT_PROJECT_URL =		https://github.com/xflr6/graphviz
COMPONENT_ARCHIVE_HASH =	\
	sha256:20743e7183be82aaaa8ad6c93f8893c923bd6658a04c32ee115edb3c8a835f78
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest/issues/12123
PYTEST_ADDOPTS += --ignore tests/backend/conftest.py
PYTEST_ADDOPTS += --ignore tests/conftest.py

# Testing needs HOME environment variable (the directory does not need to
# exist) because otherwise Fontconfig complains it is unable to find a writable
# cache directories and so testing fails.
COMPONENT_TEST_ENV += HOME="$(@D)/.test_home"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
