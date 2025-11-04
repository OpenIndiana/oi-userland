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
HUMAN_VERSION =			0.2.0
COMPONENT_SUMMARY =		A Fast, spec compliant Python 3.13+ tokenizer that runs on older Pythons.
COMPONENT_PROJECT_URL =		https://github.com/tusharsadhwani/pytokens
COMPONENT_ARCHIVE_URL =		\
	https://github.com/tusharsadhwani/pytokens/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:74f119c46e07e1dbf6b0a09e5516d54b1773cfbbeef9bd4ceb1b83e17f794fef
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tusharsadhwani/pytokens/issues/10
TEST_REQUIREMENTS_EXTRAS += dev

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tox
TEST_REQUIRED_PACKAGES.python += library/python/wheel
