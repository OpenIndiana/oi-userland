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
#   $WS_TOOLS/python-integrate-project -d python/bracex-39 bracex
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		bracex
HUMAN_VERSION =			2.6
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Bash style brace expander.
COMPONENT_PROJECT_URL =		https://github.com/facelessuser/bracex
COMPONENT_ARCHIVE_HASH =	\
	sha256:98f1347cd77e22ee8d967a30ad4e310b233f7754dbf31ff3fceb76145ba47dc7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.md

# bracex >= 2.7 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
