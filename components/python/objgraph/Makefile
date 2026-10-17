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
#   $WS_TOOLS/python-integrate-project objgraph
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		objgraph
HUMAN_VERSION =			3.7.0
COMPONENT_SUMMARY =		Draws Python object reference graphs with graphviz
COMPONENT_PROJECT_URL =		https://mg.pov.lt/objgraph/
COMPONENT_ARCHIVE_HASH =	\
	sha256:b6ef4b244217410509b257970413b01a979d54df48d2d4055b6941e8679ddbbb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by objgraph >= 3.7.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Testing needs HOME environment variable (the directory does not need to
# exist) because otherwise Fontconfig complains it is unable to find a writable
# cache directories and so pollutes the test results.
COMPONENT_TEST_ENV += HOME="$(@D)/.test_home"

# Testing needs to find the setup.py in the build directory
COMPONENT_TEST_ENV += PYTHONPATH=$(PROTOPYTHONVENDORDIR):$(COMPONENT_TEST_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
