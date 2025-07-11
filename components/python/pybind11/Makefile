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
HUMAN_VERSION =			3.0.0
COMPONENT_SUMMARY =		Seamless operability between C++11 and Python
COMPONENT_PROJECT_URL =		https://github.com/pybind/pybind11
COMPONENT_ARCHIVE_HASH =	\
	sha256:c3f07bce3ada51c3e4b76badfa85df11688d12c46111f9d242bc5c9415af7862
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/pybind/pybind11/issues/4935
# Building from github tarball fails
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/scikit-build-core
PYTHON_REQUIRED_PACKAGES += runtime/python
