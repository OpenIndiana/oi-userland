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
#   $WS_TOOLS/python-integrate-project pytest_metadata
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_metadata
HUMAN_VERSION =			3.1.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pytest plugin for test session metadata
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-metadata
COMPONENT_ARCHIVE_HASH =	\
	sha256:d2a29b0355fbc03f168aa96d41ff88b1a3b44a3b02acbe491801c98a048017c8
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Force no colors via tox posargs to override defaults in tox.ini
TOX_POSARGS += --color=no
# override -s in tox.ini to suppress annoying test output
TOX_POSARGS += --capture=fd

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/pytest
REQUIRED_PACKAGES.python += runtime/python
