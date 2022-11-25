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
#   $WS_TOOLS/python-integrate-project zope.interface
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.interface
COMPONENT_VERSION =		5.5.2
COMPONENT_SUMMARY =		zope.interface - Interfaces for Python
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.interface
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/38/6f/fbfb7dde38be7e5644bb342c4c7cdc444cd5e2ffbd70d091263b3858a8cb/zope.interface-5.5.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bfee1f3ff62143819499e348f5b8a7f3aa0259f9aca5e0ddae7391d059dce671
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

# zope.interface needs repoze.sphinx.autointerface to run tests, but
# repoze.sphinx.autointerface needs zope.interface to build itself.  This is
# special case when we need to set PYTHON_TEST_BOOTSTRAP to make sure the
# zope.interface tests are not run when there is no repoze.sphinx.autointerface
# available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-event
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
