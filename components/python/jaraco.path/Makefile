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
#   $WS_TOOLS/python-integrate-project jaraco.path
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco.path
HUMAN_VERSION =			3.5.0
COMPONENT_SUMMARY =		jaraco.path - miscellaneous path functions
COMPONENT_PROJECT_URL =		https://github.com/jaraco/jaraco.path
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b8/22/9b39c369d05886372a98c7d25868e4a47312f729db525a0d79a33d113bfd/jaraco.path-3.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:eb87aa212f6777b4efc230a6ff3cc071e148c4b9b390dd44c5041310aad39c14
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tholo/pytest-flake8/issues/92
PYTEST_ADDOPTS += -p no:flake8

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
