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
#   $WS_TOOLS/python-integrate-project -d python/soupsieve-39 soupsieve
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		soupsieve
HUMAN_VERSION =			2.8.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A modern CSS selector implementation for Beautiful Soup.
COMPONENT_PROJECT_URL =		https://github.com/facelessuser/soupsieve
COMPONENT_ARCHIVE_HASH =	\
	sha256:e121fd02e975c695e4e9e8774a5ee35d74714b59307868dcc5319ad2d9e3328e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.md

# soupsieve >= 2.9 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/beautifulsoup4
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/pytest
