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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		webtest
HUMAN_VERSION =			3.0.7
COMPONENT_SUMMARY =		Helper to test WSGI applications
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/webtest/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:7aeab50f970d46c068e7a36dd162cb242591edf72a1d04efd21374772b931741
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	license.rst

include $(WS_MAKE_RULES)/common.mk

# We do not have pyquery packaged yet
PYTEST_ADDOPTS += --deselect tests/test_response.py::TestResponse::test_pyquery

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/beautifulsoup4
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/waitress
REQUIRED_PACKAGES.python += library/python/webob
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pastedeploy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/wsgiproxy2
