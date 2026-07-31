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
#   $WS_TOOLS/python-integrate-project -d python/zope.testrunner zope_testrunner
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_testrunner
HUMAN_VERSION =			8.3
COMPONENT_SUMMARY =		Zope testrunner script.
COMPONENT_ARCHIVE_HASH =	\
	sha256:6fef88117314676650829140c2a9038fb7a0b46fd7c01a29dd7f2842bfc614d7
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

# Python 3.9 is not supported by zope.testrunner >= 8.2
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
TOX_POSARGS += -vv

# https://github.com/zopefoundation/zope.testrunner/issues/189
TOX_POSARGS += --test !testrunner-edge-cases
# https://github.com/zopefoundation/zope.testrunner/issues/203
TOX_POSARGS += --test !testrunner-colors

# Random pid
COMPONENT_TEST_TRANSFORMS += "-e 's/\(subprocess \)[0-9]\{1,\}\( is still running\)/\1\$$(PID)\2/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += library/python/zope-exceptions
REQUIRED_PACKAGES.python += library/python/zope-interface
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
