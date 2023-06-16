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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-mock
HUMAN_VERSION =			3.11.1
COMPONENT_SUMMARY =		pytest-mock - Thin-wrapper around the mock package for easier use with pytest
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-mock/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d8/2d/b3a811ec4fa24190a9ec5013e23c89421a7916167c6240c31fdc445f850c/pytest-mock-3.11.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7f6b125602ac6d743e523ae0bfa71e1a697a2f5534064528c6ff84c2f7c2fc7f
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
