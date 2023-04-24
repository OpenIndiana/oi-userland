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
#   $WS_TOOLS/python-integrate-project zope.testrunner
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.testrunner
HUMAN_VERSION =			6.0
COMPONENT_SUMMARY =		zope.testrunner - Zope testrunner script.
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.testrunner
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b3/2b/3f6879377744e7f790cac882f72dc74781ebc35fce9de5d76004cd0457d9/zope.testrunner-6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8cb6fba3af95edb0c9f2aed039de855e333824e8ccb4ef94d36929577b3351b5
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.md

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# zope.testrunner --> zope.testing --> zope.testrunner
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-exceptions
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
