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
#   $WS_TOOLS/python-integrate-project pyproject_installer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_installer
HUMAN_VERSION =			0.5.6
COMPONENT_SUMMARY =		Pyproject installer
COMPONENT_ARCHIVE_HASH =	\
	sha256:4e97bf3de9bdb915aa4dd4156ab6e626ec16982dc91ec7873afd5d0ecb180670
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# The pyproject_installer is the bootstrapper so it cannot use any non-core
# Python modules and it needs to be bootstrapped.
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_PEP735 += test

# Auto-generated dependencies
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
