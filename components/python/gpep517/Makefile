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
#   $WS_TOOLS/python-integrate-project gpep517
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gpep517
HUMAN_VERSION =			20
COMPONENT_SUMMARY =		Python package builder and installer for non-pip-centric world
COMPONENT_ARCHIVE_HASH =	\
	sha256:0bbedae28b26482b2e5e186cdb3c5657ded7b76558ae297c57a93724dcb8f359
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# https://github.com/gentoo/gpep517/issues/17
PYTEST_ADDOPTS += --ignore test/test_integration.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/installer
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
