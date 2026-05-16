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
#   $WS_TOOLS/python-integrate-project -d python/jsonpointer-39 jsonpointer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonpointer
HUMAN_VERSION =			3.0.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Identify specific nodes in a JSON document (RFC 6901) 
COMPONENT_PROJECT_URL =		https://github.com/stefankoegl/python-json-pointer
COMPONENT_ARCHIVE_HASH =	\
	sha256:2b2d729f2091522d61c3b31f82e11870f60b68f43fbc705cb76bf4b832af59ef
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = unittest

# jsonpointer >= 3.1.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
