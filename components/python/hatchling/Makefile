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
HUMAN_VERSION =			1.27.0
COMPONENT_SUMMARY =		Modern, extensible Python build backend
COMPONENT_PROJECT_URL =		https://hatch.pypa.io/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:971c296d9819abb3811112fc52c7a9751c8d381898f36533bb16f9791e941fd6
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
# - iniconfig (test bootstrap)
# - platformdirs (test bootstrap)
# - pyproject_api (test bootstrap)
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pathspec
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/trove-classifiers
PYTHON_REQUIRED_PACKAGES += runtime/python
