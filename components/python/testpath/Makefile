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
#   $WS_TOOLS/python-integrate-project testpath
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testpath
COMPONENT_VERSION =		0.5.0
COMPONENT_SUMMARY =		testpath - Test utilities for code working with files and commands
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dd/bf/245f32010f761aaeff132278e91e0d0ae1c360d6f3708a11790fdc1410d2/testpath-0.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1acf7a0bcd3004ae8357409fc33751e16d37ccc650921da1094a86581ad1e417
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# setup.py does not support test command for this project
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# cli-32.exe and cli-64.exe are needed for Windows only, so drop them
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v -E '/cli-(32|64)\.exe$$'

# Auto-generated dependencies
