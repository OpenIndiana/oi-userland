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
#   $WS_TOOLS/python-integrate-project -d python/zope.location zope_location
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_location
HUMAN_VERSION =			6.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Zope Location
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.location/
COMPONENT_ARCHIVE_HASH =	\
	sha256:baa3e0e8eab734ff908ffd9860185c8de458025d49eae62f11ba3b16579ee6ce
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += library/python/zope-interface
REQUIRED_PACKAGES.python += library/python/zope-proxy
REQUIRED_PACKAGES.python += library/python/zope-schema
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-component
TEST_REQUIRED_PACKAGES.python += library/python/zope-configuration
TEST_REQUIRED_PACKAGES.python += library/python/zope-copy
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
