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
#   $WS_TOOLS/python-integrate-project poetry_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		poetry_core
HUMAN_VERSION =			1.7.0
COMPONENT_SUMMARY =		poetry_core - Poetry PEP 517 Build Backend
COMPONENT_PROJECT_URL =		https://github.com/python-poetry/poetry-core
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/cb/1c/af7f886e723b2dfbaea9b8a739153f227b386dd856cf956f9fd0ed0a502b/poetry_core-1.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8f679b83bd9c820082637beca1204124d5d2a786e4818da47ec8acefd0353b74
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing dependencies for this project are maintained using poetry.  We
# neither do have poetry packaged yet, nor support listing poetry dependencies
# without poetry.  For now we just hope all required testing dependencies are
# installed.

# https://github.com/python-poetry/poetry/issues/7824
# https://github.com/python-poetry/poetry/issues/7826

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
