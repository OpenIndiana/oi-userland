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
#   $WS_TOOLS/python-integrate-project manuel
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		manuel
HUMAN_VERSION =			1.13.0
COMPONENT_SUMMARY =		Manuel lets you build tested documentation.
COMPONENT_PROJECT_URL =		http://pypi.python.org/pypi/manuel
COMPONENT_ARCHIVE_HASH =	\
	sha256:5d63120de8fa6d927780b69ae28aa3e9d1669b10af3d32785f3fba11a5be885a
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.rst

# https://github.com/benji-york/manuel/issues/34#issuecomment-2016443027
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/benji-york/manuel/issues/34#issuecomment-2016443027
COMPONENT_TEST_TARGETS += manuel.tests.test_suite

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
