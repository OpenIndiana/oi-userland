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
HUMAN_VERSION =			12.19.0
COMPONENT_SUMMARY =		The sip module support for PyQt5
COMPONENT_PROJECT_URL =		https://github.com/Python-SIP/sip
COMPONENT_ARCHIVE_HASH =	\
	sha256:71cacf1879da2cd3e50cb239e21673cfe02d358af70ab6768817c960428868c3
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# Python 3.9 is not supported by PyQt5_sip >= 12.17.2
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
