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
#   $WS_TOOLS/python-integrate-project websockets
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		websockets
HUMAN_VERSION =			13.1
COMPONENT_SUMMARY =		An implementation of the WebSocket Protocol (RFC 6455 & 7692)
COMPONENT_PROJECT_URL =		https://github.com/python-websockets/websockets
COMPONENT_ARCHIVE_URL =		\
	https://github.com/python-websockets/websockets/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:39345b087381694ca06c5b2b922aa8c2a54dc8f08fcaee358eafaa2222c4dd22
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/python-websockets/websockets/issues/1026
COMPONENT_TEST_ENV += WEBSOCKETS_TESTS_TIMEOUT_FACTOR=10

# Force verbose test output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
