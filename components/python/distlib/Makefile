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
#   $WS_TOOLS/python-integrate-project distlib
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		distlib
HUMAN_VERSION =			0.4.1
COMPONENT_SUMMARY =		Distribution utilities
COMPONENT_PROJECT_URL =		https://github.com/pypa/distlib
COMPONENT_ARCHIVE_HASH =	\
	sha256:c3804d0d2d4b5fcd44036eb860cb6660485fcdf5c2aba53dc324d805837ea65b
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find the compat module in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)/tests

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
