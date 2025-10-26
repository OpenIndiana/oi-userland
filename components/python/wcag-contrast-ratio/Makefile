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
#   $WS_TOOLS/python-integrate-project wcag-contrast-ratio
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wcag-contrast-ratio
HUMAN_VERSION =			0.9
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A library for computing contrast ratios, as required by WCAG 2.0
COMPONENT_PROJECT_URL =		https://github.com/gsnedders/wcag-contrast-ratio
COMPONENT_ARCHIVE_URL =		\
	https://github.com/gsnedders/wcag-contrast-ratio/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5263b7b2d0f5a8de2eb409421284947df6229b67bca0055fa10da38153835815
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
