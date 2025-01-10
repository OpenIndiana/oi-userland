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
#   $WS_TOOLS/python-integrate-project poetry_dynamic_versioning
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		poetry_dynamic_versioning
HUMAN_VERSION =			1.5.2
COMPONENT_SUMMARY =		Plugin for Poetry to enable dynamic versioning based on VCS tags
COMPONENT_PROJECT_URL =		https://github.com/mtkennerly/poetry-dynamic-versioning
COMPONENT_ARCHIVE_HASH =	\
	sha256:7e7b1e54623e56e86ba454016a0b5c1e60e2bd26e4f6f006b8b53f4ae1b555f4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# All tests either require poetry or should be run from project git repo.
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/dunamai
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/tomlkit
PYTHON_REQUIRED_PACKAGES += runtime/python
