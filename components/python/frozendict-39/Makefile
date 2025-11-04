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
#   $WS_TOOLS/python-integrate-project -d python/frozendict-39 frozendict
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		frozendict
HUMAN_VERSION =			2.4.6
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A simple immutable dictionary
COMPONENT_PROJECT_URL =		https://github.com/Marco-Sulla/python-frozendict
COMPONENT_ARCHIVE_HASH =	\
	sha256:df7cd16470fbd26fc4969a208efadc46319334eb97def1ddf48919b351192b8e
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# deliverables differs for Python >= 3.11
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
