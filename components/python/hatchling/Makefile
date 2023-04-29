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
HUMAN_VERSION =			1.14.1
COMPONENT_SUMMARY =		hatchling - Modern, extensible Python build backend
COMPONENT_PROJECT_URL =		https://hatch.pypa.io/latest/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/aa/d2/613087e785e4631a96d8b53688e28d5cd55a67caee9000e6408c0c58bcd2/hatchling-1.14.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:55fbc88cbd0d96c09c3e9392b51db513fd4cb4caf47615d65f935a5ef1756133
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = none

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
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pathspec
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/trove-classifiers
PYTHON_REQUIRED_PACKAGES += runtime/python
