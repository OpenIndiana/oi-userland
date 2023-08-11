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
HUMAN_VERSION =			6.0.1
COMPONENT_SUMMARY =		zope.i18nmessageid - Message Identifiers for internationalization
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.i18nmessageid
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/67/0a/2f7ef863b4a19b01c87558edea49d155908f3588d02e3269bbf3b42164b1/zope.i18nmessageid-6.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2d5bce6fb31f1cea0efa2644649bc867d2972303f1dbbd9ffefce5b2eb9e0176
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
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
