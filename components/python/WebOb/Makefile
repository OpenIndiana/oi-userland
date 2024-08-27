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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		webob
HUMAN_VERSION =			1.8.8
COMPONENT_SUMMARY =		WSGI request and response object
COMPONENT_PROJECT_URL =		http://webob.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:2abc1555e118fc251e705fc6dc66c7f5353bb9fbfab6d20e22f1c02b4b71bcee
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	docs/license.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
