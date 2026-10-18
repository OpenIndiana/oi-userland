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
#   $WS_TOOLS/python-integrate-project soupsieve
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		soupsieve
HUMAN_VERSION =			3.0.3
COMPONENT_SUMMARY =		A modern CSS selector implementation for Beautiful Soup.
COMPONENT_PROJECT_URL =		https://github.com/facelessuser/soupsieve
COMPONENT_ARCHIVE_HASH =	\
	sha256:7dcf6022eed0399eb9934a75e020148f7a2024c37b7dfcd3cf2c5505d69c364e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# soupsieve --> beautifulsoup4 ==> soupsieve
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by soupsieve >= 2.9
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_HATCH += dev

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/beautifulsoup4
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/pytest
