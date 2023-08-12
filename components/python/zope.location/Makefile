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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.location
HUMAN_VERSION =			5.0
COMPONENT_SUMMARY =		zope.location - Zope Location
COMPONENT_PROJECT_URL =		http://github.com/zopefoundation/zope.location/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/eb/f9/1fb7a001feb5fec6f180ef3610169f1cbef76e8c015c52409c2d18b7fac4/zope.location-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:016fea934b97dad2b08a64ea7f2fbc3de55dbb074c461f66d871c70bf3aaaea5
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += library/python/zope-proxy
PYTHON_REQUIRED_PACKAGES += library/python/zope-schema
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-component
TEST_REQUIRED_PACKAGES.python += library/python/zope-configuration
TEST_REQUIRED_PACKAGES.python += library/python/zope-copy
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
