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
#   $WS_TOOLS/python-integrate-project hypothesis
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hypothesis
HUMAN_VERSION =			6.141.1
COMPONENT_SUMMARY =		The property-based testing library for Python
COMPONENT_PROJECT_URL =		https://hypothesis.works
COMPONENT_ARCHIVE_URL =		\
	https://github.com/HypothesisWorks/hypothesis/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:d28ebaa73b6d3897693ace2f27d63753eac589ef6673ddf3e5f87a37e8a2b4bd
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		hypothesis-python-$(HUMAN_VERSION).tar.gz
COMPONENT_SRC =			hypothesis-hypothesis-python-$(HUMAN_VERSION)
# https://github.com/HypothesisWorks/hypothesis/issues/3637
COMPONENT_SUBDIR =		hypothesis-python

include $(WS_MAKE_RULES)/common.mk

# Fails with tox-current-env
PYTEST_ADDOPTS += --deselect $(COMPONENT_SUBDIR)/tests/nocover/test_scrutineer.py::test_report_sort

# Contains the date of the test run
COMPONENT_TEST_TRANSFORMS += "-e '/to add failing examples to your code/d'"

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/attrs
REQUIRED_PACKAGES.python += library/python/exceptiongroup
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/sortedcontainers
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pexpect
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
