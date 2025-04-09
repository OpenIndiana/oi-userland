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
#   $WS_TOOLS/python-integrate-project scripttest
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scripttest
HUMAN_VERSION =			2.0
COMPONENT_SUMMARY =		Helper to test command-line scripts
COMPONENT_PROJECT_URL =		https://scripttest.readthedocs.io/en/stable/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pypa/scripttest/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:21483f4f07db1ba3f127b67e2b7c5b19bea1d2a4d6069006f124a3a3086a9697
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	docs/license.rst

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
