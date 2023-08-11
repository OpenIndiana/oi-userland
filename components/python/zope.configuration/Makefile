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
#   $WS_TOOLS/python-integrate-project zope.configuration
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.configuration
HUMAN_VERSION =			5.0
COMPONENT_SUMMARY =		zope.configuration - Zope Configuration Markup Language (ZCML)
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.configuration
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f7/ef/06e1600ed7102e1a8c81993c028d90d6da1e1283c25e99a618c353194244/zope.configuration-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:234b4a18c71f6b3b9bf6bcf225264bae0149ac68dea07b072f0f699a4cec26e7
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-i18nmessageid
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += library/python/zope-schema
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-schema
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
