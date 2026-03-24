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
#   $WS_TOOLS/python-integrate-project pyasyncore
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyasyncore
HUMAN_VERSION =			1.0.5
COMPONENT_SUMMARY =		Make asyncore available for Python 3.12 onwards
COMPONENT_PROJECT_URL =		https://github.com/simonrob/pyasyncore
COMPONENT_ARCHIVE_HASH =	\
	sha256:dd483d5103a6d59b66b86e0ca2334ad43dca732ff23a0ac5d63c88c52510542e
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This is not needed for Python < 3.12
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
