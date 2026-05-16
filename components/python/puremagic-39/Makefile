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
#   $WS_TOOLS/python-integrate-project -d python/puremagic-39 puremagic
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		puremagic
HUMAN_VERSION =			1.30
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Pure python implementation of magic file detection
COMPONENT_PROJECT_URL =		https://github.com/cdgriffith/puremagic
COMPONENT_ARCHIVE_HASH =	\
	sha256:f9ff7ac157d54e9cf3bff1addfd97233548e75e685282d84ae11e7ffee1614c9
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# puremagic >= 2.0.0 requires Python >= 3.12
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
