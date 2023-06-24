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
#   $WS_TOOLS/python-integrate-project zope.event
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.event
HUMAN_VERSION =			5.0
COMPONENT_SUMMARY =		zope.event - Very basic event publishing system
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.event
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/46/c2/427f1867bb96555d1d34342f1dd97f8c420966ab564d58d18469a1db8736/zope.event-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bac440d8d9891b4068e2b5a2c5e2c9765a9df762944bda6955f96bb9b91e67cd
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
