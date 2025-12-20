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
#   $WS_TOOLS/python-integrate-project -d python/prettytable-39 prettytable
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		prettytable
HUMAN_VERSION =			3.16.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A simple Python library for easily displaying tabular data in a visually appealing ASCII table format
COMPONENT_PROJECT_URL =		https://github.com/prettytable/prettytable
COMPONENT_ARCHIVE_HASH =	\
	sha256:3c64b31719d961bf69c9a7e03d0c1e477320906a98da63952bc6698d6164ff57
COMPONENT_LICENSE =		BSD-3-Clause

# prettytable >= 3.17.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/wcwidth
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-lazy-fixtures
