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
#   $WS_TOOLS/python-integrate-project dnspython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dnspython
HUMAN_VERSION =			2.9.2
COMPONENT_SUMMARY =		DNS toolkit
COMPONENT_PROJECT_URL =		https://www.dnspython.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:8d4d39a513e649d634004ce4d39ade2352efcea472a0247535a5c2d18a9d7ba9
COMPONENT_LICENSE =		ISC
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported by dnspython >= 2.8.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/uv-build
REQUIRED_PACKAGES.python += runtime/python
