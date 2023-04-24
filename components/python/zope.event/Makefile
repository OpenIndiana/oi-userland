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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.event
HUMAN_VERSION =			4.6
COMPONENT_SUMMARY =		zope.event - Very basic event publishing system
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.event
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/42/49/ba8610674cad200da2f9c87b5f52fdcf18b02dd743a8a1e90726803cc42f/zope.event-4.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:81d98813046fc86cc4136e3698fee628a3282f9c320db18658c21749235fce80
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
