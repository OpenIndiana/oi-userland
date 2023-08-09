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
#   $WS_TOOLS/python-integrate-project zope.hookable
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.hookable
HUMAN_VERSION =			5.4
COMPONENT_SUMMARY =		zope.hookable - Zope hookable
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.hookable
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/26/ce/ba1346f4c078321683c0118fc7706287493294d1cb637bf356be94de8c40/zope.hookable-5.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fb601f00ac87e5aa582a81315ed96768ce3513280729d3f51f79312e2b8b94ac
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
