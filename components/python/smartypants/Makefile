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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		smartypants
HUMAN_VERSION =			2.0.1
COMPONENT_SUMMARY =		smartypants is a Python fork of SmartyPants
COMPONENT_PROJECT_URL =		https://github.com/leohemsted/smartypants.py
COMPONENT_SRC =			smartypants.py-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL =		https://github.com/leohemsted/smartypants.py/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	sha256:b98191911ff3b4144ef8ad53e776a2d0ad24bd508a905c6ce523597c40022773
COMPONENT_LICENSE =		Custom
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# Manually added dependencies
TEST_REQUIRED_PACKAGES.python += library/python/docutils

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
