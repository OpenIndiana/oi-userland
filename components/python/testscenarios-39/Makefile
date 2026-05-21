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
#   $WS_TOOLS/python-integrate-project -d python/testscenarios-39 testscenarios
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testscenarios
HUMAN_VERSION =			0.5.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Testscenarios, a unittest extension for dependency injection
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/testscenarios
COMPONENT_ARCHIVE_HASH =	\
	sha256:c257cb6b90ea7e6f8fef3158121d430543412c9a87df30b5dde6ec8b9b57a2b6
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

# Force unittest test style because the automatically detected pytest does not
# work properly.
# See https://bugs.launchpad.net/testscenarios/+bug/1930149
# and https://github.com/testing-cabal/testscenarios/issues/5
TEST_STYLE = unittest

# testscenarios >= 0.6 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# https://bugs.launchpad.net/testscenarios/+bug/1930149/comments/3
COMPONENT_TEST_ARGS += testscenarios.tests.test_suite

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pbr
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/testtools
REQUIRED_PACKAGES.python += runtime/python
