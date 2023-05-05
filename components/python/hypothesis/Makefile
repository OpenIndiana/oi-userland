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
HUMAN_VERSION =			6.75.2
COMPONENT_SUMMARY =		hypothesis - A library for property-based testing
COMPONENT_PROJECT_URL =		https://hypothesis.works
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a8/8b/e4dc05c9c6b10b02c1e7693a61886a5eb0328cd302c1025a150ced413f1a/hypothesis-6.75.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:50c270b38d724ce0fefa71b8e3511d123f7a31a9af9ea003447d4e1489292fbc
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

# https://github.com/HypothesisWorks/hypothesis/issues/3588
# https://github.com/HypothesisWorks/hypothesis/issues/3637
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/sortedcontainers
PYTHON_REQUIRED_PACKAGES += runtime/python
