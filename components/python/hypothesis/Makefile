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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hypothesis
HUMAN_VERSION =			6.151.11
COMPONENT_SUMMARY =		The property-based testing library for Python
COMPONENT_PROJECT_URL =		https://hypothesis.works
COMPONENT_ARCHIVE_URL =		\
	https://github.com/HypothesisWorks/hypothesis/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:844da94423395d6abfc0eceb99f4db4dc79876068b044a0f6279cfca2390f1a9
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		hypothesis-python-$(HUMAN_VERSION).tar.gz
COMPONENT_SRC =			hypothesis-hypothesis-python-$(HUMAN_VERSION)
# https://github.com/HypothesisWorks/hypothesis/issues/3637
COMPONENT_SUBDIR =		hypothesis-python

# Python 3.9 is not supported by hypothesis >= 6.142.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Fails with tox-current-env
PYTEST_ADDOPTS += --deselect $(COMPONENT_SUBDIR)/tests/nocover/test_scrutineer.py::test_report_sort

# Contains the date of the test run
COMPONENT_TEST_TRANSFORMS += "-e '/to add failing examples to your code/d'"

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/sortedcontainers
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pexpect
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
