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
#   $WS_TOOLS/python-integrate-project immutables
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		immutables
HUMAN_VERSION =			0.21
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Immutable Collections
COMPONENT_ARCHIVE_HASH =	\
	sha256:b55ffaf0449790242feb4c56ab799ea7af92801a0a43f9e2f4f8af2ab24dfc4a
COMPONENT_LICENSE =		Apache-2.0 AND 0BSD

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# We do not need to check typing for this project.
PYTEST_ADDOPTS += --ignore tests/test_mypy.py

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
