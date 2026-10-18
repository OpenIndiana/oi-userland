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
#   $WS_TOOLS/python-integrate-project pytimeparse
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytimeparse
HUMAN_VERSION =			1.1.10
COMPONENT_SUMMARY =		Time expression parser
COMPONENT_PROJECT_URL =		https://github.com/wroberts/pytimeparse
COMPONENT_ARCHIVE_HASH =	\
	sha256:ecf0ee613a72cb0b1d3d5404bd398a64266576fc36ccf3149178af6f2ec6f736
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.rst

TEST_STYLE = unittest

# Python 3.9 is not supported by pytimeparse >= 1.1.9
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
