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
#   $WS_TOOLS/python-integrate-project pbr
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pbr
HUMAN_VERSION =			7.0.3
COMPONENT_SUMMARY =		Python Build Reasonableness
COMPONENT_PROJECT_URL =		https://docs.openstack.org/pbr/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:b46004ec30a5324672683ec848aed9e8fc500b0d261d40a3229c2d2bbfcedc29
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# pbr --> testresources ==> pbr
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# Random temporary directory
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\).\{8\}/tmp.\{8\}|\1XXXXXXXX/tmpXXXXXXXX|'"

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/stestr
TEST_REQUIRED_PACKAGES.python += library/python/testresources
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/testtools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
