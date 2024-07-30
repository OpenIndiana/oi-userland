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
#   $WS_TOOLS/python-integrate-project -d developer/scons SCons
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		SCons
HUMAN_VERSION =			4.8.0
COMPONENT_SUMMARY =		Open Source next-generation build tool.
COMPONENT_PROJECT_URL =		https://www.scons.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ec/5c/cc835a17633de8b260ec1a6e527b5c57f4975cee5949f49e57ad4d5fab4b/scons-4.8.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2c7377ff6a22ca136c795ae3dc3d0824696e5478d1e4940f2af75659b0d45454
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = setup.py

COMPONENT_FMRI =		developer/build/scons
COMPONENT_CLASSIFICATION =	Development/Distribution Tools

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
