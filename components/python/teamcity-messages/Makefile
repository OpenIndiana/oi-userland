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
#   $WS_TOOLS/python-integrate-project teamcity-messages
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		teamcity-messages
COMPONENT_VERSION =		1.32
COMPONENT_SUMMARY =		teamcity-messages - Send test results to TeamCity continuous integration server from unittest, nose, py.test, twisted trial, behave (Python 2.6+)
COMPONENT_PROJECT_URL =		https://github.com/JetBrains/teamcity-messages
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/10/f3/6d8eac4e4ed39855a902672cac33a2441f2c3942a9730f93b3c1025d4e21/teamcity-messages-1.32.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6991d95642c8d067524c90985b650d89caab6ac0bf47b721b931b04951abbfc1
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.md

# Force none because otherwise setup.py style is detected. but it fails because
# testing support is missing:
# https://github.com/JetBrains/teamcity-messages/issues/271
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
