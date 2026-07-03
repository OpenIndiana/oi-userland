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
#   $WS_TOOLS/python-integrate-project stevedore
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		stevedore
HUMAN_VERSION =			5.9.0
COMPONENT_SUMMARY =		Manage dynamic plugins for Python applications
COMPONENT_PROJECT_URL =		https://docs.openstack.org/stevedore
COMPONENT_ARCHIVE_HASH =	\
	sha256:abbd0af7a38a8bbb1d6adea2e35b17609cf004eaac323e88a8d8963640dd2b3c
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# stevedore --> stestr ==> cliff ==> stevedore
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by stevedore >= 5.6.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pbr
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
