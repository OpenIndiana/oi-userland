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
#   $WS_TOOLS/python-integrate-project pytest-mock
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-mock
HUMAN_VERSION =			3.12.0
COMPONENT_SUMMARY =		pytest-mock - Thin-wrapper around the mock package for easier use with pytest
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-mock/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b3/96/25588c55fbe330b751bd7c7d723c3544957566bc090f6d506551b514f488/pytest-mock-3.12.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:31a40f038c22cad32287bb43932054451ff5583ff094bca6f675df2f8bc1a6e9
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pytest-mock/issues/240
PYTEST_ADDOPTS += --assert=plain

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
