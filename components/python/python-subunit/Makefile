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
#   $WS_TOOLS/python-integrate-project python-subunit
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python-subunit
HUMAN_VERSION =			1.4.4
COMPONENT_SUMMARY =		python-subunit - Python implementation of subunit test streaming protocol
COMPONENT_PROJECT_URL =		http://launchpad.net/subunit
COMPONENT_ARCHIVE_HASH =	\
	sha256:1079363131aa1d3f45259237265bc2e61a77e35f20edfb6e3d1d2558a2cdea34
COMPONENT_LICENSE =		(Apache-2.0 OR BSD-3-Clause) AND MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://bugs.launchpad.net/subunit/+bug/2046453
PYTEST_ADDOPTS += -k 'not TestStatusArgParserTests and not StatusStreamResultTests and not TestStreamResultContract'

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/iso8601
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/testtools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
