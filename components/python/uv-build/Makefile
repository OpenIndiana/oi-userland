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
#   $WS_TOOLS/python-integrate-project -d python/uv-build uv_build
#

BUILD_STYLE = pyproject
CARGO_VENDOR = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		uv_build
HUMAN_VERSION =			0.9.12
COMPONENT_SUMMARY =		The uv build backend
COMPONENT_PROJECT_URL =		https://pypi.org/project/uv/
COMPONENT_ARCHIVE_HASH =	\
	sha256:d11ef6c659e4bc1b89b3a556edac71c431521efbc574a6fd4e6588236137d0c5
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = none

# https://github.com/astral-sh/uv/issues/16849

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += runtime/python
