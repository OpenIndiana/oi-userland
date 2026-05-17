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
#   $WS_TOOLS/python-integrate-project -d python/testresources-39 testresources
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testresources
HUMAN_VERSION =			2.0.2
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Testresources, a pyunit extension for managing expensive test resources
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/testresources
COMPONENT_ARCHIVE_HASH =	\
	sha256:2cbf3d7e00ab2e9fe24b754a102644f6f334244980464c38233b18127f1deaec
COMPONENT_LICENSE =		Apache-2.0 OR BSD-3-Clause

# testresources >= 2.1.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pbr
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/testtools
