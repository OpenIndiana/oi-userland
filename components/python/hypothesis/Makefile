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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hypothesis
HUMAN_VERSION =			6.83.1
COMPONENT_SUMMARY =		hypothesis - A library for property-based testing
COMPONENT_PROJECT_URL =		https://hypothesis.works
COMPONENT_ARCHIVE_URL =		\
	https://github.com/HypothesisWorks/hypothesis/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:c78abdde0eaad3ae1ccb716e74ea63a45c44793998083441dac2615363d2a5af
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		hypothesis-python-$(HUMAN_VERSION).tar.gz
COMPONENT_SRC =			hypothesis-hypothesis-python-$(HUMAN_VERSION)
# https://github.com/HypothesisWorks/hypothesis/issues/3637
COMPONENT_SUBDIR =		hypothesis-python

include $(WS_MAKE_RULES)/common.mk

# Random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp\).\{8\}/|\1XXXXXXXX/|g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/sortedcontainers
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pexpect
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
