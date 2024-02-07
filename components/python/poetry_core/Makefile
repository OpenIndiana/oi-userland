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
HUMAN_VERSION =			1.9.0
COMPONENT_SUMMARY =		poetry_core - Poetry PEP 517 Build Backend
COMPONENT_PROJECT_URL =		https://github.com/python-poetry/poetry-core
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f2/db/20a9f9cae3f3c213a8c406deb4395698459fd96962cea8f2ccb230b1943c/poetry_core-1.9.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fa7a4001eae8aa572ee84f35feb510b321bd652e5cf9293249d62853e1f935a2
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

TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
