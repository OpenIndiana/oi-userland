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
#   $WS_TOOLS/python-integrate-project -d python/WebTest webtest
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		webtest
HUMAN_VERSION =			3.0.1
COMPONENT_SUMMARY =		Helper to test WSGI applications
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/webtest/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:493b5c802f8948a65b5e3a1ad5b2524ee5e1ab60cd713d9a3da3b8da082c06fe
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	license.rst

include $(WS_MAKE_RULES)/common.mk

# We do not have pyquery packaged yet
PYTEST_ADDOPTS += --deselect tests/test_response.py::TestResponse::test_pyquery

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/beautifulsoup4
PYTHON_REQUIRED_PACKAGES += library/python/waitress
PYTHON_REQUIRED_PACKAGES += library/python/webob
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pastedeploy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/wsgiproxy2
