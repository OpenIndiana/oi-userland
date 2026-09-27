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
#   $WS_TOOLS/python-integrate-project -d python/sqlparse-39 sqlparse
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sqlparse
HUMAN_VERSION =			0.5.5
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A non-validating SQL parser.
COMPONENT_ARCHIVE_HASH =	\
	sha256:e20d4a9b0b8585fdf63b10d30066c7c94c5d7a7ec47c889a2d83a3caa93ff28e
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# sqlparse >= 0.6.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
