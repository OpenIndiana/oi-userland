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
HUMAN_VERSION =			1.0.4
COMPONENT_SUMMARY =		Make asyncore available for Python 3.12 onwards
COMPONENT_PROJECT_URL =		https://github.com/simonrob/pyasyncore
COMPONENT_ARCHIVE_URL =		\
	https://github.com/simonrob/pyasyncore/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4d9d423ef3a3a601a9e6e638cb2951e1b49f7e94095818f25e439529fec34674
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This is not needed for Python < 3.12
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

# https://github.com/simonrob/pyasyncore/issues/6
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
