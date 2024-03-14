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
#   $WS_TOOLS/python-integrate-project PyQt5_sip
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PyQt5_sip
HUMAN_VERSION =			12.13.0
COMPONENT_SUMMARY =		PyQt5_sip - The sip module support for PyQt5
COMPONENT_PROJECT_URL =		https://www.riverbankcomputing.com/software/sip/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ee/81/fce2a475aa56c1f49707d9306b930695b6ff078c2242c9f2fd72a3214e1f/PyQt5_sip-12.13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7f321daf84b9c9dbca61b80e1ef37bdaffc0e93312edae2cd7da25b953971d91
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE-GPL3

TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# Testing fails without this, although there are no tests to run.
COMPONENT_PRE_TEST_ACTION += $(MKDIR) $(@D)/PyQt5 ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
