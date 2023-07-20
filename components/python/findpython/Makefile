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
#   $WS_TOOLS/python-integrate-project findpython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		findpython
HUMAN_VERSION =			0.3.1
COMPONENT_SUMMARY =		findpython - A utility to find python versions on your system
COMPONENT_PROJECT_URL =		https://github.com/frostming/findpython
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/5f/f1/e41623e7952500b0b0a259dcc3c3383800eb97da74772fb8b023464855ca/findpython-0.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7621f8a9c199a70d219831cddaeb84ca7e83e20b8358172bff47871a18a5eda4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pdm-backend
PYTHON_REQUIRED_PACKAGES += runtime/python
