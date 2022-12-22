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
HUMAN_VERSION =			20.17.1
COMPONENT_SUMMARY =		virtualenv - Virtual Python Environment builder
COMPONENT_PROJECT_URL =		https://virtualenv.pypa.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7b/19/65f13cff26c8cc11fdfcb0499cd8f13388dd7b35a79a376755f152b42d86/virtualenv-20.17.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f8b927684efc6f1cc206c9db297a570ab9ad0e51c16fa9e45487d36d1905c058
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/distlib
PYTHON_REQUIRED_PACKAGES += library/python/filelock
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/coverage-enable-subprocess
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-env
TEST_REQUIRED_PACKAGES.python += library/python/pytest-freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
