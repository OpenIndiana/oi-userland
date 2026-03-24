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
#   $WS_TOOLS/python-integrate-project -d python/identify-39 identify
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		identify
HUMAN_VERSION =			2.6.15
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		File identification library for Python
COMPONENT_PROJECT_URL =		https://github.com/pre-commit/identify
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pre-commit/identify/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bcdb19f63ead0dc06c0bc603e21bb00c24da550ac40f16b7461bc405a05f2155
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# identify >= 2.6.16 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/ukkonen
