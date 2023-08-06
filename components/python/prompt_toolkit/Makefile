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
#   $WS_TOOLS/python-integrate-project prompt_toolkit
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		prompt_toolkit
HUMAN_VERSION =			3.0.39
COMPONENT_SUMMARY =		prompt_toolkit - Library for building powerful interactive command lines in Python
COMPONENT_PROJECT_URL =		https://github.com/prompt-toolkit/python-prompt-toolkit
COMPONENT_ARCHIVE_URL =		\
	https://github.com/prompt-toolkit/python-prompt-toolkit/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f723e610262ccc4e356490a31f6a0530c02ad40bbc96d49c6b2edb79c68cac30
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			python-prompt-toolkit-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wcwidth
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
