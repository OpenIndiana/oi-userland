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
#   $WS_TOOLS/python-integrate-project -d python/urllib3-39 urllib3
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		urllib3
HUMAN_VERSION =			2.6.3
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		HTTP library with thread-safe connection pooling, file post, and more.
COMPONENT_ARCHIVE_HASH =	\
	sha256:1b62b6884944a57dbe321509ab94fd4d3b307075e0c2eae991ac71ee15ad38ed
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# urllib3 >= 2.7.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

# Testing needs modified version of hypercorn.  We do not have that packaged.
# https://github.com/urllib3/urllib3/issues/3334
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
