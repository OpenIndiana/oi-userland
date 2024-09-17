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
#   $WS_TOOLS/python-integrate-project -d python/zope.i18nmessageid zope_i18nmessageid
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_i18nmessageid
HUMAN_VERSION =			7.0
COMPONENT_SUMMARY =		Message Identifiers for internationalization
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.i18nmessageid
COMPONENT_ARCHIVE_HASH =	\
	sha256:bf9146078c0d7359da41043bd2b713203c4fc56ef2122b3cdbb7551c3fcd8464
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
