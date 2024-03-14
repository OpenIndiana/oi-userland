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
#   $WS_TOOLS/python-integrate-project smartypants
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		smartypants
HUMAN_VERSION =			2.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		smartypants - Python with the SmartyPants
COMPONENT_PROJECT_URL =		https://github.com/leohemsted/smartypants.py
COMPONENT_ARCHIVE_URL =		\
	https://github.com/leohemsted/smartypants.py/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b98191911ff3b4144ef8ad53e776a2d0ad24bd508a905c6ce523597c40022773
COMPONENT_LICENSE =		BSD-2-Clause AND BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

COMPONENT_SRC =			smartypants.py-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
