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
#   $WS_TOOLS/python-integrate-project hatchling
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hatchling
HUMAN_VERSION =			1.31.0
COMPONENT_SUMMARY =		Modern, extensible Python build backend
COMPONENT_PROJECT_URL =		https://hatch.pypa.io/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:6b48ad4068a482ed7239b3a8215bc55b47aad3345d58dfc94e553c5d2d46211b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = none

# This project is missing tests
# See https://github.com/pypa/hatch/issues/329

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - colorama (test bootstrap)
# - filelock (test bootstrap)
# - hatch_vcs (test bootstrap)
# - platformdirs (test bootstrap)
# - pygments (test bootstrap)
# - pyproject_api (test bootstrap)
# - python-discovery (test bootstrap)
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by hatchling >= 1.28.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pathspec
REQUIRED_PACKAGES.python += library/python/pluggy
REQUIRED_PACKAGES.python += library/python/trove-classifiers
REQUIRED_PACKAGES.python += runtime/python
