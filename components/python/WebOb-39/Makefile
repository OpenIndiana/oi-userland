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
#   $WS_TOOLS/python-integrate-project -d python/WebOb-39 webob
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		webob
HUMAN_VERSION =			1.8.9
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		WSGI request and response object
COMPONENT_PROJECT_URL =		http://webob.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:ad6078e2edb6766d1334ec3dee072ac6a7f95b1e32ce10def8ff7f0f02d56589
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	docs/license.txt

# runtime dependencies differs for Python >= 3.13
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
