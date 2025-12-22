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
#   $WS_TOOLS/python-integrate-project plaster_pastedeploy
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		plaster_pastedeploy
HUMAN_VERSION =			1.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A loader implementing the PasteDeploy syntax to be used by plaster.
COMPONENT_PROJECT_URL =		https://github.com/Pylons/plaster_pastedeploy
COMPONENT_ARCHIVE_HASH =	\
	sha256:be262e6d2e41a7264875daa2fe2850cbb0615728bcdc92828fdc72736e381412
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# With plaster-pastedeploy installed the testing finds both the installed and
# the currently built plaster-pastedeploy which is unexpected and so some tests
# fails.
TEST_CONFLICTING_PACKAGES.python += library/python/plaster-pastedeploy

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/pastedeploy
REQUIRED_PACKAGES.python += library/python/plaster
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
