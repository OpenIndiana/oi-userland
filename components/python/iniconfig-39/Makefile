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
#   $WS_TOOLS/python-integrate-project -d python/iniconfig-39 iniconfig
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		iniconfig
HUMAN_VERSION =			2.1.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		brain-dead simple config-ini parsing
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/iniconfig
COMPONENT_ARCHIVE_HASH =	\
	sha256:3abbd2e30b36733fee78f9c7f7308f2d0050e88f0087fd25c2645f63c773e1c7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# The sdist is missing tests:
# https://github.com/pytest-dev/iniconfig/issues/67
# ... and building from github tarball fails

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - pytest (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

# iniconfig >= 2.2.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
