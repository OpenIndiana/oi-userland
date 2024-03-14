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
#   $WS_TOOLS/python-integrate-project zope.testing
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.testing
HUMAN_VERSION =			5.0.1
COMPONENT_SUMMARY =		zope.testing - Zope testing helpers
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.testing
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1c/45/a22985a9a5bb886ae0665f04c1ffe985d9558c3e9881fde808fc9dc0a6f9/zope.testing-5.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e87cd0d8d666573cdaf133816ab7b9beec801a64a86595c19cb5fe992ef3d649
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# sphinx-build is unable to find zope.testing modules in proto area during testing.
# The root cause is unknown (yet), but it looks like a bug.
COMPONENT_TEST_ENV +=	PYTHONPATH=$(@D)/src

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-exceptions
TEST_REQUIRED_PACKAGES.python += library/python/zope-interface
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
