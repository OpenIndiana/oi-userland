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
#   $WS_TOOLS/python-integrate-project zope.security
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.security
HUMAN_VERSION =			6.1
COMPONENT_SUMMARY =		zope.security - Zope Security Framework
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.security
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b5/c9/8f4d997d11047d10709f6352d48b7dfc82d4f39352523d9e80fd13a77981/zope.security-6.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4646a764152866d0fb624e63b7ed68a71ab9a21dd41e8c0ae0591234364d68c5
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-component
PYTHON_REQUIRED_PACKAGES += library/python/zope-i18nmessageid
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += library/python/zope-location
PYTHON_REQUIRED_PACKAGES += library/python/zope-proxy
PYTHON_REQUIRED_PACKAGES += library/python/zope-schema
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/btrees
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-component
TEST_REQUIRED_PACKAGES.python += library/python/zope-configuration
TEST_REQUIRED_PACKAGES.python += library/python/zope-location
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
