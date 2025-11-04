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
#   $WS_TOOLS/python-integrate-project schema
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		schema
HUMAN_VERSION =			0.7.8
COMPONENT_SUMMARY =		Simple data validation library
COMPONENT_PROJECT_URL =		https://github.com/keleshev/schema
COMPONENT_ARCHIVE_URL =		\
	https://github.com/keleshev/schema/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fa2286808bbc9c7015ad0e0253822a3a2e77792f868ab8aefc4afbbc07bc2732
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE-MIT

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
