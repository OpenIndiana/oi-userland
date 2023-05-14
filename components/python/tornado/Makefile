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
HUMAN_VERSION =			6.3.2
COMPONENT_SUMMARY =		tornado - Tornado is a Python web framework and asynchronous networking library, originally developed at FriendFeed.
COMPONENT_PROJECT_URL =		http://www.tornadoweb.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/30/f0/6e5d85d422a26fd696a1f2613ab8119495c1ebb8f49e29f428d15daf79cc/tornado-6.3.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4b927c4f19b71e627b13f3db2324e4ae660527143f9e1f2e2fb404f3a187e2ba
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
