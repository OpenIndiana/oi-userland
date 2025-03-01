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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.testing
HUMAN_VERSION =			5.1
COMPONENT_SUMMARY =		Zope testing helpers
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.testing
COMPONENT_ARCHIVE_HASH =	\
	sha256:7135ebaaec3d38796e491a9adb127a3651aa0e3b20128de6c778451fa11acc47
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_SRC =			zope_testing-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# sphinx-build is unable to find zope.testing modules in proto area during testing.
# The root cause is unknown (yet), but it looks like a bug.
COMPONENT_TEST_ENV +=	PYTHONPATH=$(@D)/src

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-exceptions
TEST_REQUIRED_PACKAGES.python += library/python/zope-interface
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
