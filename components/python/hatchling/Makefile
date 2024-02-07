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
HUMAN_VERSION =			1.21.1
COMPONENT_SUMMARY =		hatchling - Modern, extensible Python build backend
COMPONENT_PROJECT_URL =		https://hatch.pypa.io/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d8/a1/7dd1caa87c0b15c04c6291e25112e5d082cce02ee87f221a8be1d594f857/hatchling-1.21.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bba440453a224e7d4478457fa2e8d8c3633765bafa02975a6b53b9bf917980bc
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
PYTHON_REQUIRED_PACKAGES += library/python/editables
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pathspec
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/trove-classifiers
PYTHON_REQUIRED_PACKAGES += runtime/python
