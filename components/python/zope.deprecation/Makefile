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
#   $WS_TOOLS/python-integrate-project -d python/zope.deprecation zope_deprecation
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_deprecation
HUMAN_VERSION =			6.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Zope Deprecation Infrastructure
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.deprecation
COMPONENT_ARCHIVE_HASH =	\
	sha256:18727ebda8e63a6d4bd28a290e8b46852e9f14473debb5cc40a0a2dccfadf15f
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
