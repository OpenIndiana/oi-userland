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
#   $WS_TOOLS/python-integrate-project incremental
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		incremental
HUMAN_VERSION =			24.11.0
COMPONENT_SUMMARY =		A CalVer version manager that supports the future.
COMPONENT_PROJECT_URL =		https://github.com/twisted/incremental
COMPONENT_ARCHIVE_HASH =	\
	sha256:87d3480dbb083c1d736222511a8cf380012a8176c2456d01ef483242abbbcf8c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# incremental --> twisted ==> incremental
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Remove directories created by previous test run to make test results reproducible
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_noop/build ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_noop/example_noop.egg-info ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_setuppy/build ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_setuppy/src/example_setuppy.egg-info ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_setuptools/build ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/tests/example_setuptools/src/example_setuptools.egg-info ;

# Random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/\.tmp-\).\{8\}/|\1XXXXXXXX/|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/twisted
