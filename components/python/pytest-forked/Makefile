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
#   $WS_TOOLS/python-integrate-project pytest-forked
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-forked
HUMAN_VERSION =			1.6.0
COMPONENT_SUMMARY =		pytest-forked - run tests in isolated forked subprocesses
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-forked
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8c/c9/93ad2ba2413057ee694884b88cf7467a46c50c438977720aeac26e73fdb7/pytest-forked-1.6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4dafd46a9a600f65d822b8f605133ecf5b3e1941ebb3588e943b4e3eb71a5a3f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest-forked/issues/52
PYTEST_ADDOPTS += -p no:flaky

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/py
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pycmd
TEST_REQUIRED_PACKAGES.python += library/python/setuptools-scm
