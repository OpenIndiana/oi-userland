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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope.testrunner
HUMAN_VERSION =			6.2
COMPONENT_SUMMARY =		zope.testrunner - Zope testrunner script.
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/zope.testrunner
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f4/8d/21b90e83d18110d8d073894f295fdaf4b94d07bf0d8d713ea6c0ae3cff60/zope.testrunner-6.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f8dc92e1363837567a02c78f252b6fd43c3b69c08ff2db748333aefd111bccd
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

# Random pid
COMPONENT_TEST_TRANSFORMS += "-e 's/\(subprocess \)[0-9]\{1,\}\( is still running\)/\1\$$(PID)\2/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/zope-exceptions
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
