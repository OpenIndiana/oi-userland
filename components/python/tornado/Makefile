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
#   $WS_TOOLS/python-integrate-project tornado
#

BUILD_STYLE = pyproject
PYTHON3_SOABI = abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tornado
HUMAN_VERSION =			6.3
COMPONENT_SUMMARY =		tornado - Tornado is a Python web framework and asynchronous networking library, originally developed at FriendFeed.
COMPONENT_PROJECT_URL =		http://www.tornadoweb.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/15/e6/88afe8318b6aaff1e6c60b3d4b94c9b68708cc0a5ba2f6dae5cbc288ce69/tornado-6.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d68f3192936ff2c4add04dc21a436a43b4408d466746b78bb2b9d0a53a18683f
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/tornadoweb/tornado/issues/3095
# https://github.com/tornadoweb/tornado/issues/3253
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# Remove timing from test results
COMPONENT_TEST_TRANSFORMS += "-e 's/[^ ]*ms$$//'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
