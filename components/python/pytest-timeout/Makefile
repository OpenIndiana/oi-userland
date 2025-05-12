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
#   $WS_TOOLS/python-integrate-project -d python/pytest-timeout pytest_timeout
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_timeout
HUMAN_VERSION =			2.4.0
COMPONENT_SUMMARY =		pytest plugin to abort hanging tests
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-timeout
COMPONENT_ARCHIVE_HASH =	\
	sha256:7e68e90b01f9eff71332b25001f85c75495fc4e3a836701876183c4bcfd0540a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The xfailures traceback contains random data
PYTEST_TRACEBACK = --tb=no

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/ipdb
TEST_REQUIRED_PACKAGES.python += library/python/pexpect
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
