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
#   $WS_TOOLS/python-integrate-project -d python/python-discovery python_discovery
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python_discovery
HUMAN_VERSION =			1.3.0
COMPONENT_SUMMARY =		Python interpreter discovery
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/python-discovery
COMPONENT_ARCHIVE_HASH =	\
	sha256:d098f1e86be5d45fe4d14bf1029294aabbd332f4321179dec85e76cddce834b0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# tox >= 4.38 is needed to run tests, but
# Python 3.9 is not supported by tox >= 4.31.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/filelock
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/platformdirs
REQUIRED_PACKAGES.python += runtime/python
