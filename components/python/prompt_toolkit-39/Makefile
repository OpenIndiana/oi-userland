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
#   $WS_TOOLS/python-integrate-project -d python/prompt_toolkit-39 prompt_toolkit
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		prompt_toolkit
HUMAN_VERSION =			3.0.52
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Library for building powerful interactive command lines in Python
COMPONENT_PROJECT_URL =		https://github.com/prompt-toolkit/python-prompt-toolkit
COMPONENT_ARCHIVE_URL =		\
	https://github.com/prompt-toolkit/python-prompt-toolkit/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:50f74f474df47f2f8eaa0ef7b62ef5fc6f35bdccf0c4635ec7d4c42b719bf149
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =				python-prompt-toolkit-$(HUMAN_VERSION)

# prompt_toolkit >= 3.0.53 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wcwidth
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
