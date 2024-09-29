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
#   $WS_TOOLS/python-integrate-project bracex
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		bracex
HUMAN_VERSION =			2.5.post1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Bash style brace expander.
COMPONENT_PROJECT_URL =		https://github.com/facelessuser/bracex
COMPONENT_ARCHIVE_HASH =	\
	sha256:12c50952415bfa773d2d9ccb8e79651b8cdb1f31a42f6091b804f6ba2b4a66b6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
