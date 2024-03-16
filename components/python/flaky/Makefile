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
#   $WS_TOOLS/python-integrate-project flaky
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flaky
HUMAN_VERSION =			3.8.1
COMPONENT_SUMMARY =		flaky - Plugin for pytest that automatically reruns flaky tests.
COMPONENT_PROJECT_URL =		https://github.com/box/flaky
COMPONENT_ARCHIVE_URL =		\
	https://github.com/box/flaky/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e12f33292d2a84390691dd56dadc44876f123c2959d719b87623457a0983ffb1
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coveralls
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/pylint
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
