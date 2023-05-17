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
#   $WS_TOOLS/python-integrate-project docutils
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		docutils
HUMAN_VERSION =			0.20.1
COMPONENT_SUMMARY =		docutils - Docutils -- Python Documentation Utilities
COMPONENT_PROJECT_URL =		https://docutils.sourceforge.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1f/53/a5da4f2c5739cf66290fac1431ee52aff6851c7c8ffd8264f13affd7bcdd/docutils-0.20.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f08a4e276c3a1583a86dce3e34aba3fe04d02bba2dd51ed16106244e8a923e3b
COMPONENT_LICENSE =		CC-PDDC AND BSD-3-Clause AND BSD-2-Clause
COMPONENT_LICENSE_FILE =	COPYING.txt

include $(WS_MAKE_RULES)/common.mk

# Filter out lines with timestamps
COMPONENT_TEST_TRANSFORMS += "-e '/^Testing Docutils/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^OS:/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^Elapsed time:/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
