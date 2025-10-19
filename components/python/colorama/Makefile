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
#   $WS_TOOLS/python-integrate-project colorama
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		colorama
HUMAN_VERSION =			0.4.6
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Cross-platform colored terminal text.
COMPONENT_PROJECT_URL =		https://github.com/tartley/colorama
COMPONENT_ARCHIVE_HASH =	\
	sha256:08695f5cb7ed6e0531a20572697297273c47b8cae5a63ffc6d6ed5c201be6e44
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
