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
#   $WS_TOOLS/python-integrate-project -d python/WebOb webob
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		webob
HUMAN_VERSION =			1.8.11
COMPONENT_SUMMARY =		WSGI request and response object
COMPONENT_PROJECT_URL =		http://webob.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:aa8c27231070b135c025e567a9cd7eda03f4df71352ffaac740cb6a75f0f81a5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	docs/license.txt

# runtime dependencies differs for Python < 3.13
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/Pylons/webob/issues/479
PYTEST_ADDOPTS += --deselect tests/test_in_wsgiref.py::test_interrupted_request

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/legacy-cgi
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
