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
#   $WS_TOOLS/python-integrate-project trustme
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		trustme
HUMAN_VERSION =			1.2.0
COMPONENT_SUMMARY =		\#1 quality TLS certs while you wait, for the discerning tester
COMPONENT_PROJECT_URL =		https://github.com/python-trio/trustme
COMPONENT_ARCHIVE_HASH =	\
	sha256:ed2264fb46c35459e6de9e454ed4bab73be44b6a2a26ad417f9b6854aebb644a
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/idna
PYTHON_REQUIRED_PACKAGES += runtime/python
