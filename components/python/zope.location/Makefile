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
#   $WS_TOOLS/python-integrate-project zope.location
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.location
HUMAN_VERSION =			5.1
COMPONENT_SUMMARY =		Zope Location
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.location/
COMPONENT_ARCHIVE_HASH =	\
	sha256:e4e01d4ef46253a8e07fd59dcbd7bb0b81819bffe5d0dc2d5843bc201afa4ad9
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_SRC =			zope_location-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += library/python/zope-proxy
PYTHON_REQUIRED_PACKAGES += library/python/zope-schema
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-component
TEST_REQUIRED_PACKAGES.python += library/python/zope-configuration
TEST_REQUIRED_PACKAGES.python += library/python/zope-copy
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
