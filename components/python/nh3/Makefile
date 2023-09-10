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
HUMAN_VERSION =			0.2.14
COMPONENT_SUMMARY =		nh3 - Ammonia HTML sanitizer Python binding
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b0/bb/e967b7bc659cd1fd87f845d02194a08ea8da88d7d9dcc28164ee513f76f3/nh3-0.2.14.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a0c509894fd4dccdff557068e5074999ae3b75f4c5a2d6fb5415e782e25679c4
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
