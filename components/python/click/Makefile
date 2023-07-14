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
#   $WS_TOOLS/python-integrate-project click
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		click
HUMAN_VERSION =			8.1.5
COMPONENT_SUMMARY =		click - Composable command line interface toolkit
COMPONENT_PROJECT_URL =		https://palletsprojects.com/p/click/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7e/ad/7a6a96fab480fb2fbf52f782b2deb3abe1d2c81eca3ef68a575b5a6a4f2e/click-8.1.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4be4b1af8d665c6d942909916d31a213a106800c47d0eeba73d34da3cbc11367
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.rst

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/iniconfig
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pluggy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
