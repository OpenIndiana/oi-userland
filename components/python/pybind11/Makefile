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
#   $WS_TOOLS/python-integrate-project pybind11
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pybind11
HUMAN_VERSION =			3.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Seamless operability between C++11 and Python
COMPONENT_PROJECT_URL =		https://github.com/pybind/pybind11
COMPONENT_ARCHIVE_HASH =	\
	sha256:9c0f40056a016da59bab516efb523089139fcc6f2ba7e4930854c61efb932051
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/pybind/pybind11/issues/4935
# Building from github tarball fails
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/scikit-build-core
REQUIRED_PACKAGES.python += runtime/python
