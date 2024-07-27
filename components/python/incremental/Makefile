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
HUMAN_VERSION =			24.7.1
COMPONENT_SUMMARY =		A small library that versions your Python projects.
COMPONENT_PROJECT_URL =		https://github.com/twisted/incremental
COMPONENT_ARCHIVE_HASH =	\
	sha256:a3717c20534499835555ba727b32ee087945ba9daaf23851471dfe3d1e3d1698
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

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
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/click
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/twisted
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
