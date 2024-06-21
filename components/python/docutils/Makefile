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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		docutils
HUMAN_VERSION =			0.21.2
COMPONENT_SUMMARY =		docutils - Docutils -- Python Documentation Utilities
COMPONENT_PROJECT_URL =		https://docutils.sourceforge.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:3a6b18732edf182daa3cd12775bbb338cf5691468f91eeeb109deff6ebfa986f
COMPONENT_LICENSE =		CC-PDDC AND BSD-3-Clause AND BSD-2-Clause AND ZPL-2.1
COMPONENT_LICENSE_FILE =	COPYING.txt

include $(WS_MAKE_RULES)/common.mk

# Filter out lines with timestamps
COMPONENT_TEST_TRANSFORMS += "-e '/^Testing Docutils/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^OS:/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^Elapsed time:/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
