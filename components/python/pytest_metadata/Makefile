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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_metadata
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		pytest_metadata - pytest plugin for test session metadata
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-metadata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/03/ba/bda83d96bed99276a0b142baeb9a4b8b3183c0d3ae2d5470a0e2b1ebfe40/pytest_metadata-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:53dcd8bbd101cf6ca97efb4a42a72fcbee5de173bddad4850f4ce9bb27e9f0f2
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TARGETS += --
# Force no colors via tox posargs to override defaults in tox.ini
COMPONENT_TEST_TARGETS += --color=no
# override -s in tox.ini to suppress annoying test output
COMPONENT_TEST_TARGETS += --capture=fd

# https://github.com/pytest-dev/pluggy/issues/457
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
