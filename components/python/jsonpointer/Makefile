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
#   $WS_TOOLS/python-integrate-project jsonpointer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonpointer
HUMAN_VERSION =			3.3
COMPONENT_SUMMARY =		Identify specific nodes in a JSON document (RFC 6901) 
COMPONENT_PROJECT_URL =		https://github.com/stefankoegl/python-json-pointer
COMPONENT_ARCHIVE_HASH =	\
	sha256:2d851da328132043289a03df1dbb1577b901ad9cd22911f515d17875fbc1773a
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = unittest

# Python 3.9 is not supported by jsonpointer >= 3.1.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
