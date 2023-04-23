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
HUMAN_VERSION =			6.3.1
COMPONENT_SUMMARY =		tornado - Tornado is a Python web framework and asynchronous networking library, originally developed at FriendFeed.
COMPONENT_PROJECT_URL =		http://www.tornadoweb.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1c/1d/89cb7050dbd009db3cb69ca74c1f0a3f5c36405f887c2d2371d9ebfe0cd5/tornado-6.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5e2f49ad371595957c50e42dd7e5c14d64a6843a3cf27352b69c706d1b5918af
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
