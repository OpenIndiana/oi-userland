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
#   $WS_TOOLS/python-integrate-project nh3
#

BUILD_STYLE = pyproject
PYTHON3_SOABI = abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nh3
HUMAN_VERSION =			0.2.15
COMPONENT_SUMMARY =		nh3 - Python bindings to the ammonia HTML sanitization library.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/08/03/506eb477d723da0db7c46d6259ee06bc68243ef40f5626eb66ab72ae4d69/nh3-0.2.15.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d1e30ff2d8d58fb2a14961f7aac1bbb1c51f9bdd7da727be35c63826060b0bf3
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/maturin
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
