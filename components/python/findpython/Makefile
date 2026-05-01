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
#   $WS_TOOLS/python-integrate-project findpython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		findpython
HUMAN_VERSION =			0.8.0
COMPONENT_SUMMARY =		A utility to find python versions on your system
COMPONENT_PROJECT_URL =		https://github.com/frostming/findpython
COMPONENT_ARCHIVE_HASH =	\
	sha256:53b32264874dfa5990bd09d717819386d8db3149d89fe20f88fe1078de286bae
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pdm-backend
REQUIRED_PACKAGES.python += library/python/platformdirs
REQUIRED_PACKAGES.python += runtime/python
