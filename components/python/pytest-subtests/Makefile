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
#   $WS_TOOLS/python-integrate-project pytest-subtests
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-subtests
HUMAN_VERSION =			0.11.0
COMPONENT_SUMMARY =		pytest-subtests - unittest subTest() support and subtests fixture
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-subtests
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f3/89/ba24ce1d1224e92901e1ceb2a3b45c2296cb71951f6fd50b7755e21a455f/pytest-subtests-0.11.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:51865c88457545f51fb72011942f0a3c6901ee9e24cbfb6d1b9dc1348bafbe37
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pluggy/issues/457
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-relaxed
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
