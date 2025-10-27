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
#   $WS_TOOLS/python-integrate-project smartypants
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		smartypants
HUMAN_VERSION =			2.0.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Python with the SmartyPants
COMPONENT_PROJECT_URL =		https://github.com/justinmayer/smartypants.py
COMPONENT_ARCHIVE_HASH =	\
	sha256:39d64ce1d7cc6964b698297bdf391bc12c3251b7f608e6e55d857cd7c5f800c6
COMPONENT_LICENSE =		BSD-2-Clause AND BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
# See https://github.com/justinmayer/smartypants.py/blob/main/.github/workflows/ci.yml
TEST_REQUIRED_PACKAGES.python += library/python/docutils
TEST_REQUIRED_PACKAGES.python += library/python/pygments

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
