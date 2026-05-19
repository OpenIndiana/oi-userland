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
#   $WS_TOOLS/python-integrate-project -d python/zipp-39 zipp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zipp
HUMAN_VERSION =			3.23.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Backport of pathlib-compatible object wrapper for zip files
COMPONENT_ARCHIVE_HASH =	\
	sha256:32120e378d32cd9714ad503c1d024619063ec28aad2248dc6672ad13edfa5110
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# zipp >= 4.1.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/coherent-licensed
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-functools
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-itertools
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-test
TEST_REQUIRED_PACKAGES.python += library/python/more-itertools
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-ignore-flaky
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
