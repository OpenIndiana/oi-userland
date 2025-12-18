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
#   $WS_TOOLS/python-integrate-project -d python/roman-numerals roman_numerals
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		roman_numerals
HUMAN_VERSION =			4.1.0
COMPONENT_SUMMARY =		Manipulate well-formed Roman numerals
COMPONENT_ARCHIVE_HASH =	\
	sha256:1af8b147eb1405d5839e78aeb93131690495fe9da5c91856cb33ad55a7f1e5b2
COMPONENT_LICENSE =		0BSD
COMPONENT_LICENSE_FILE =	LICENCE.rst

TEST_STYLE = pytest

# Python 3.9 is not supported by roman-numerals >= 4.0.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
