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
#   $WS_TOOLS/python-integrate-project -d python/PyQt5_sip pyqt5_sip
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyqt5_sip
HUMAN_VERSION =			12.16.1
COMPONENT_SUMMARY =		The sip module support for PyQt5
COMPONENT_PROJECT_URL =		https://github.com/Python-SIP/sip
COMPONENT_ARCHIVE_HASH =	\
	sha256:8c831f8b619811a32369d72339faa50ae53a963f5fdfa4d71f845c63e9673125
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Testing fails without this, although there are no tests to run.
COMPONENT_PRE_TEST_ACTION += $(MKDIR) $(@D)/PyQt5 ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
