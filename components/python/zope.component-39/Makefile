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
#   $WS_TOOLS/python-integrate-project -d python/zope.component-39 zope_component
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_component
HUMAN_VERSION =			7.0
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		Zope Component Architecture
COMPONENT_ARCHIVE_HASH =	\
	sha256:1256ca091ccd7e368ec4faaede45211c824038546d6961776223d99db79896a9
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

# zope.component >= 7.1 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += library/python/zope-event
REQUIRED_PACKAGES.python += library/python/zope-hookable
REQUIRED_PACKAGES.python += library/python/zope-interface
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/persistent
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-configuration
TEST_REQUIRED_PACKAGES.python += library/python/zope-i18nmessageid
TEST_REQUIRED_PACKAGES.python += library/python/zope-location
TEST_REQUIRED_PACKAGES.python += library/python/zope-proxy
TEST_REQUIRED_PACKAGES.python += library/python/zope-security
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
