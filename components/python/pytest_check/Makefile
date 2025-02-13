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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_check
HUMAN_VERSION =			2.5.0
COMPONENT_SUMMARY =		A pytest plugin that allows multiple failures per test.
COMPONENT_ARCHIVE_HASH =	\
	sha256:3a6be8431c7720287958436d97a6b823eed5ae5ceb7da5572a0e4a9462feaf88
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
