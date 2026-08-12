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
#   $WS_TOOLS/python-integrate-project -d developer/scons scons
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		scons
HUMAN_VERSION =			4.11.0
COMPONENT_SUMMARY =		Open Source next-generation build tool.
COMPONENT_PROJECT_URL =		https://www.scons.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ba48f9e2eb6b9178cabdc9893792418e6970c84f43f4b027e4468e20616a89c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

COMPONENT_FMRI =		developer/build/scons
COMPONENT_CLASSIFICATION =	Development/Distribution Tools

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
