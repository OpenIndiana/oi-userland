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
#   $WS_TOOLS/python-integrate-project filelock
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		filelock
HUMAN_VERSION =			3.29.3
COMPONENT_SUMMARY =		A platform independent file lock.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/py-filelock
COMPONENT_ARCHIVE_HASH =	\
	sha256:7fc1b3f39cf172fd8203812043c57b8a65aef9969f38b6704f628b881f761a84
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - python-discovery (test bootstrap)
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by filelock >= 3.20.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
