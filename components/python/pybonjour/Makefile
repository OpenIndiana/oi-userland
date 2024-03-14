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
#   $WS_TOOLS/python-integrate-project pybonjour
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pybonjour
HUMAN_VERSION =			1.1.1
COMPONENT_REVISION =		6
COMPONENT_SUMMARY =		pybonjour - Pure-Python interface to Apple Bonjour and compatible DNS-SD libraries
COMPONENT_PROJECT_URL =		http://code.google.com/p/pybonjour/
COMPONENT_ARCHIVE_HASH =	\
	sha256:006175b0fa6ef555fe8970132db81332827662a680d5f64dcb005bfcc80299ad
COMPONENT_LICENSE =		MIT

TEST_STYLE = pytest

# This project cannot be downloaded from PyPI
COMPONENT_ARCHIVE_URL =		\
	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/pybonjour/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

# Note: Testing fails if the svc:/network/dns/multicast:default service is not
# online.

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
