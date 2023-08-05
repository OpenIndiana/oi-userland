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
#   $WS_TOOLS/python-integrate-project virtualenv
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		virtualenv
HUMAN_VERSION =			20.24.2
COMPONENT_SUMMARY =		virtualenv - Virtual Python Environment builder
COMPONENT_PROJECT_URL =		https://github.com/pypa/virtualenv
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ea/3a/9e31ffe1d38f2ca7e249445783651548103237b29dd6389c104ff0feef93/virtualenv-20.24.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fd8a78f46f6b99a67b7ec5cf73f92357891a7b3a40fd97637c27f854aae3b9e0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:cov
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/distlib
PYTHON_REQUIRED_PACKAGES += library/python/filelock
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/coverage-enable-subprocess
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-env
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/time-machine
