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
#   $WS_TOOLS/python-integrate-project greenlet
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		greenlet
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		Lightweight in-process concurrent programming
COMPONENT_PROJECT_URL =		https://greenlet.readthedocs.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:b395121e9bbe8d02a750886f108d540abe66075e61e22f7353d9acb0b81be0f0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
