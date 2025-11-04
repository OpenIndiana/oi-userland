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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tornado
HUMAN_VERSION =			6.5.2
COMPONENT_SUMMARY =		Tornado is a Python web framework and asynchronous networking library, originally developed at FriendFeed.
COMPONENT_PROJECT_URL =		http://www.tornadoweb.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:ab53c8f9a0fa351e2c0741284e06c7a45da86afb544133201c5cc8578eb076a0
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Force verbose output via tox posargs
TOX_POSARGS += --verbose

# Remove timing from test results
COMPONENT_TEST_TRANSFORMS += "-e 's/[^ ]*ms$$//'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
