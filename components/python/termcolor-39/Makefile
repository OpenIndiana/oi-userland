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
#   $WS_TOOLS/python-integrate-project -d python/termcolor-39 termcolor
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		termcolor
HUMAN_VERSION =			3.1.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		ANSI color formatting for output in terminal
COMPONENT_PROJECT_URL =		https://github.com/termcolor/termcolor
COMPONENT_ARCHIVE_HASH =	\
	sha256:6a6dd7fbee581909eeec6a756cff1d7f7c376063b14e4a298dc4980309e55970
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING.txt

# termcolor >= 3.2.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
