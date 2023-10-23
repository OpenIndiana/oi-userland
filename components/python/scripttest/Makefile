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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scripttest
HUMAN_VERSION =			1.3
COMPONENT_SUMMARY =		scripttest - Helper to test command-line scripts
COMPONENT_PROJECT_URL =		http://pythonpaste.org/scripttest/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pypa/scripttest/archive/refs/tags/$(HUMAN_VERSION).0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:33c2c5315538598652cecc28984557d55dbe75ff814e50e4307dc8fbfac51cd5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	docs/license.rst

# The git tag contains extra '.0'.
COMPONENT_SRC = $(COMPONENT_NAME)-$(HUMAN_VERSION).0

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
