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
HUMAN_VERSION =			0.7.7
COMPONENT_SUMMARY =		Simple data validation library
COMPONENT_PROJECT_URL =		https://github.com/keleshev/schema
COMPONENT_ARCHIVE_URL =		\
	https://github.com/keleshev/schema/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5c2fbedb393646aaaaee5dd3098810418a2ed0d7a70294102196a4f6b8e07801
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE-MIT

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
