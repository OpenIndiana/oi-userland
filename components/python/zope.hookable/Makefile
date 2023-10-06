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
HUMAN_VERSION =			6.0
COMPONENT_SUMMARY =		zope.hookable - Zope hookable
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.hookable
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/78/ce/4eeb5f4d12bfb6ba46584c3e7cd0b8f29264b10a9159eaf06d90f71a22a9/zope.hookable-6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1668993d40a7cfdc867843dd5725929e7f83a5b0c195c709af1daef8274f43cb
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
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
