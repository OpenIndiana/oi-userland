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
#   $WS_TOOLS/python-integrate-project importlib_metadata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		importlib_metadata
HUMAN_VERSION =			9.1.0
COMPONENT_SUMMARY =		Read metadata from Python packages
COMPONENT_ARCHIVE_HASH =	\
	sha256:9607fb24f95d4e0b1c17d57ec4604357d76d3f0d154f19fd4861f2e31c8e4065
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
PYTHON_BOOTSTRAP = yes

# Python 3.9 is not supported by importlib-metadata >= 8.8.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# We do not need to run performance tests for this project
PYTEST_ADDOPTS += --ignore exercises.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/coherent-licensed
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/zipp
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pyfakefs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
