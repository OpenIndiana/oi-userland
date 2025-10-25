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
#   $WS_TOOLS/python-integrate-project -d python/check-manifest check_manifest
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		check_manifest
HUMAN_VERSION =			0.51
COMPONENT_SUMMARY =		Check MANIFEST.in in a Python source package for completeness
COMPONENT_PROJECT_URL =		https://github.com/mgedmin/check-manifest
COMPONENT_ARCHIVE_HASH =	\
	sha256:9801c7637675755a563f33e3c48ee59a59b37a7677297c05c910c16c5b9b6d67
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.rst

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/build
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/wheel
