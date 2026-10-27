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
#   $WS_TOOLS/python-integrate-project -d python/PyQt-builder pyqt_builder
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyqt_builder
HUMAN_VERSION =			1.20.3
COMPONENT_SUMMARY =		The PyQt build system
COMPONENT_PROJECT_URL =		https://github.com/Python-PyQt/PyQt-builder
COMPONENT_ARCHIVE_HASH =	\
	sha256:be65ff822a75d020fafc0edcaf9fd79b7e3f145a00995a177c98c3286a5f85d5
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# This project is missing tests
# https://github.com/Python-PyQt/PyQt-builder/issues/35

# Python 3.9 is not supported by PyQt-builder >= 1.20.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/sip
REQUIRED_PACKAGES.python += runtime/python
