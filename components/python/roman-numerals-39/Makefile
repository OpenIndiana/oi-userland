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
#   $WS_TOOLS/python-integrate-project -d python/roman-numerals-39 roman_numerals
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		roman_numerals
HUMAN_VERSION =			3.1.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Manipulate well-formed Roman numerals
COMPONENT_ARCHIVE_HASH =	\
	sha256:384e36fc1e8d4bd361bdb3672841faae7a345b3f708aae9895d074c878332551
COMPONENT_LICENSE =		0BSD
COMPONENT_LICENSE_FILE =	LICENCE.rst

TEST_STYLE = pytest

# roman-numerals >= 4.0.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
