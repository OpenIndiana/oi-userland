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
#   $WS_TOOLS/python-integrate-project markdown2
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		markdown2
HUMAN_VERSION =			2.5.4
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A fast and complete Python implementation of Markdown
COMPONENT_PROJECT_URL =		https://github.com/trentm/python-markdown2
COMPONENT_ARCHIVE_URL =		\
	https://github.com/trentm/python-markdown2/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:304526a6cc7377ab13b566eb70c5b6929604256603ff5e398694f82057da57e6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_SRC =			python-markdown2-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# these lines could appear anywhere in the test output
COMPONENT_TEST_TRANSFORMS += "-e '/^WARNING:test:skipping/d'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
