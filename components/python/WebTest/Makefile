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
#   $WS_TOOLS/python-integrate-project WebTest
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		WebTest
HUMAN_VERSION =			3.0.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Helper to test WSGI applications
COMPONENT_PROJECT_URL =		https://docs.pylonsproject.org/projects/webtest/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:54bd969725838d9861a9fa27f8d971f79d275d94ae255f5c501f53bb6d9929eb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	license.rst

include $(WS_MAKE_RULES)/common.mk

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
