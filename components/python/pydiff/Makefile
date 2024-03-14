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
#   $WS_TOOLS/python-integrate-project pydiff
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydiff
HUMAN_VERSION =			0.2
COMPONENT_SUMMARY =		pydiff - Diffs two Python files at the bytecode level.
COMPONENT_PROJECT_URL =		https://github.com/myint/pydiff
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e4/fd/7d0c657a640e7329a4112deb437f43a84e07f1b935efe4c1e34bc356194f/pydiff-0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:847c7121625de8d5aa9eb2b079edad18a451e134cafa1b8958ea019ee0409aaa
COMPONENT_LICENSE =		MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
