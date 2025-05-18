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
HUMAN_VERSION =			6.5
COMPONENT_SUMMARY =		Tornado is a Python web framework and asynchronous networking library, originally developed at FriendFeed.
COMPONENT_PROJECT_URL =		http://www.tornadoweb.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:c70c0a26d5b2d85440e4debd14a8d0b463a0cf35d92d3af05f5f1ffa8675c826
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
