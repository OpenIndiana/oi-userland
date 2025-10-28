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
#   $WS_TOOLS/python-integrate-project py
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		py
HUMAN_VERSION =			1.11.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		library with cross-python path, ini-parsing, io, code, log facilities
COMPONENT_PROJECT_URL =		https://py.readthedocs.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:51c75c4126074b472f746a24399ad32f6053d1b34b68d2fa41e558e6f4a98719
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Testing is known to fail: https://github.com/pytest-dev/py/issues/281
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
