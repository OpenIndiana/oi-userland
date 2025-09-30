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
#   $WS_TOOLS/python-integrate-project pytokens
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytokens
HUMAN_VERSION =			0.1.10
COMPONENT_SUMMARY =		A Fast, spec compliant Python 3.12+ tokenizer that runs on older Pythons.
COMPONENT_PROJECT_URL =		https://github.com/tusharsadhwani/pytokens
COMPONENT_ARCHIVE_HASH =	\
	sha256:c9a4bfa0be1d26aebce03e6884ba454e842f186a59ea43a6d3b25af58223c044
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# We cannot run tests because
# https://github.com/tusharsadhwani/pytokens/issues/3
# https://github.com/tusharsadhwani/pytokens/issues/4
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
