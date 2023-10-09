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
#   $WS_TOOLS/python-integrate-project pytest-timeout
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-timeout
HUMAN_VERSION =			2.2.0
COMPONENT_SUMMARY =		pytest-timeout - pytest plugin to abort hanging tests
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-timeout
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2a/b0/8e3182e9ed65ad5b247f9d13769f214fc52b0d3522c3e1c8dbfa2f879e5a/pytest-timeout-2.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3b0b95dabf3cb50bac9ef5ca912fa0cfc286526af17afc806824df20c2f72c90
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The test_suppresses_timeout_when_debugger_is_entered test uses spawn_pytest()
# to execute tests.  The spawn_pytest() have no support for passing additional
# pytest options (see also https://github.com/pytest-dev/pytest/pull/7207) so
# we cannot disable some toxic pytest plugins (black and mypy in this case) as
# we usually do using the "-p no:PLUGIN" option.  To have tests pass we need to
# make sure both pytest-black and pytest-mypy are not installed during testing.
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-black
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/ipdb
TEST_REQUIRED_PACKAGES.python += library/python/pexpect
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
