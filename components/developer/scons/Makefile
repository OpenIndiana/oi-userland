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
HUMAN_VERSION =			4.6.0
COMPONENT_SUMMARY =		SCons - Open Source next-generation build tool.
COMPONENT_PROJECT_URL =		https://www.scons.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a4/ce/31e6d2f5e1d1cc23d65cfe4e28b2a83cc2d49f4bb99b5eec9240fb9a9857/SCons-4.6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7db28958b188b800f803c287d0680cc3ac7c422ed0b1cf9895042c52567803ec
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = setup.py

COMPONENT_FMRI =		developer/build/scons
COMPONENT_CLASSIFICATION =	Development/Distribution Tools

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/SCons/scons/issues/2285
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRSHAREMAN1DIR) ; \
	$(MV) $(PROTOUSRDIR)/*.1 $(PROTOUSRSHAREMAN1DIR) ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/build
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
