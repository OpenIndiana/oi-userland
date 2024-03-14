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
#   $WS_TOOLS/python-integrate-project zope.i18nmessageid
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.i18nmessageid
HUMAN_VERSION =			6.1.0
COMPONENT_SUMMARY =		zope.i18nmessageid - Message Identifiers for internationalization
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.i18nmessageid
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c0/55/73436beb7a4fdb139cf0ac259a2a67519460f91b1756bac05ba9af038568/zope.i18nmessageid-6.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:45ac26fdc86fabdf7b78f1c1bccfc1d4372d1a54838bbaedda9dba7444ad8941
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/sphinx-rtd-theme
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
