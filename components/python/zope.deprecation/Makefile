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
#   $WS_TOOLS/python-integrate-project zope.deprecation
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.deprecation
HUMAN_VERSION =			5.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		zope.deprecation - Zope Deprecation Infrastructure
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.deprecation
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ba/de/a47e434ed1804d82f3fd7561aee5c55914c72d87f54cac6b99c15cbe7f89/zope.deprecation-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b7c32d3392036b2145c40b3103e7322db68662ab09b7267afe1532a9d93f640f
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
