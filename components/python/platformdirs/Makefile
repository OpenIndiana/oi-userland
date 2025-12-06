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
#   $WS_TOOLS/python-integrate-project platformdirs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		platformdirs
HUMAN_VERSION =			4.5.1
COMPONENT_SUMMARY =		A small Python package for determining appropriate platform-specific dirs, e.g. a \`user data dir\`.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/platformdirs
COMPONENT_ARCHIVE_HASH =	\
	sha256:61d5cdcc6065745cdd94f0f878977f8de9437be93de97c1c12f853c9c0cdcbda
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/appdirs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
