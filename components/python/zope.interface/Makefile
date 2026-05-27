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
#   $WS_TOOLS/python-integrate-project -d python/zope.interface zope_interface
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zope_interface
HUMAN_VERSION =			8.5
COMPONENT_SUMMARY =		Interfaces for Python
COMPONENT_ARCHIVE_HASH =	\
	sha256:7a3ba1c5877f0f3e3906b02ddf793abed2becc2948116414ce0e1dd820b68d6d
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# zope.interface --> zope.testing --> zope.interface
# zope.interface --> zope.event --> zope.testrunner ==> zope.interface
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by zope.interface >= 8.1
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# force verbose test output via tox posargs
TOX_POSARGS += --verbose
# https://github.com/zopefoundation/zope.interface/issues/196
TOX_POSARGS += -s $(PROTO_DIR)/$(PYTHON_LIB)/zope/interface -t $(PROTO_DIR)/$(PYTHON_LIB)/zope

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/zope-event
TEST_REQUIRED_PACKAGES.python += library/python/zope-testing
