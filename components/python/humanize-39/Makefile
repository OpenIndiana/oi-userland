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
#   $WS_TOOLS/python-integrate-project -d python/humanize-39 humanize
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		humanize
HUMAN_VERSION =			4.13.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Python humanize utilities
COMPONENT_PROJECT_URL =		https://github.com/python-humanize/humanize
COMPONENT_ARCHIVE_HASH =	\
	sha256:78f79e68f76f0b04d711c4e55d32bebef5be387148862cb1ef83d2b58e7935a0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENCE

# humanize >= 4.14.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest
