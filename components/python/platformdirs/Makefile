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
#   $WS_TOOLS/python-integrate-project platformdirs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		platformdirs
HUMAN_VERSION =			3.8.0
COMPONENT_SUMMARY =		platformdirs - A small Python package for determining appropriate platform-specific dirs, e.g. a \\\\\\\"user data dir\\\\\\\".
COMPONENT_PROJECT_URL =		https://github.com/platformdirs/platformdirs
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/cb/10/e5478cc0c3ee5563f91ab7b9da15d16e21f3737b6286ed3fd9a8fb1a99dd/platformdirs-3.8.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b0cabcb11063d21a0b261d557acb0a9d2126350e63b70cdf7db6347baea456dc
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This is to make sure we do not get coverage report because it could differ
# with every test run
COMPONENT_TEST_TARGETS += -- tests

# https://github.com/platformdirs/platformdirs/issues/184
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/appdirs
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
