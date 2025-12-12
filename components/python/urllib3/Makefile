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
#   $WS_TOOLS/python-integrate-project urllib3
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		urllib3
HUMAN_VERSION =			2.6.2
COMPONENT_SUMMARY =		HTTP library with thread-safe connection pooling, file post, and more.
COMPONENT_ARCHIVE_HASH =	\
	sha256:016f9c98bb7e98085cb2b4b17b87d2c702975664e4f060c6532e64d1c1a5e797
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# Testing needs modified version of hypercorn.  We do not have that packaged.
# https://github.com/urllib3/urllib3/issues/3334
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
