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
#   $WS_TOOLS/python-integrate-project lingua
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lingua
HUMAN_VERSION =			4.16.1
COMPONENT_SUMMARY =		Translation toolset
COMPONENT_PROJECT_URL =		https://github.com/wichert/lingua
COMPONENT_ARCHIVE_URL =		\
	https://github.com/wichert/lingua/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:332401650fe7d9a90d496d41755a78de1a48340f3198887fa211905ce3406def
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/click
REQUIRED_PACKAGES.python += library/python/polib
REQUIRED_PACKAGES.python += library/python/uv-build
REQUIRED_PACKAGES.python += runtime/python
