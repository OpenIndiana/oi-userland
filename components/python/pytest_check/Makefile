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
#   $WS_TOOLS/python-integrate-project pytest_check
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_check
HUMAN_VERSION =			2.9.1
COMPONENT_SUMMARY =		A pytest plugin that allows multiple failures per test.
COMPONENT_ARCHIVE_HASH =	\
	sha256:2d8c9f1fe5cceb0b41c480e1454e95e9ed6a3a534bf2c7e3e0f39167b11cf88b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
