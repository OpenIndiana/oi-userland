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
#   $WS_TOOLS/python-integrate-project cleo
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cleo
HUMAN_VERSION =			2.1.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Cleo allows you to create beautiful and testable command-line interfaces.
COMPONENT_PROJECT_URL =		https://github.com/python-poetry/cleo
COMPONENT_ARCHIVE_HASH =	\
	sha256:0b2c880b5d13660a7ea651001fb4acb527696c01f15c9ee650f377aa543fd523
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses poetry to manage test dependencies.
TEST_REQUIREMENTS_POETRY += dev

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/crashtest
REQUIRED_PACKAGES.python += library/python/poetry-core
REQUIRED_PACKAGES.python += library/python/rapidfuzz
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
