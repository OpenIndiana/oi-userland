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
#   $WS_TOOLS/python-integrate-project certifi
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		certifi
HUMAN_VERSION =			2023.5.7
COMPONENT_SUMMARY =		certifi - Python package for providing Mozilla's CA Bundle.
COMPONENT_PROJECT_URL =		https://github.com/certifi/python-certifi
COMPONENT_ARCHIVE_URL =		\
	https://github.com/certifi/python-certifi/archive/refs/tags/$(GITHUB_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3ee59191c133d4c3c921c075fe4e8bec7c25a16d02143f0ee7de47f7f22cfd0f
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Versions at github are with leading zeros
GITHUB_VERSION = $(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.\(.\.\)/.0\1/' -e 's/\.\(.\)$$/.0\1/')
# Sources are located in non-default directory
COMPONENT_SRC = python-certifi-$(GITHUB_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
