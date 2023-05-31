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
HUMAN_VERSION =			1.6.1
COMPONENT_SUMMARY =		poetry_core - Poetry PEP 517 Build Backend
COMPONENT_PROJECT_URL =		https://github.com/python-poetry/poetry-core
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/20/e8/e0a80cc355bc207fb1760160344e978f39d683c35e1230f71b8916bf3a50/poetry_core-1.6.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f9b0de39665f36d6594657e7d57b6f463cc10f30c28e6d1c3b9ff54c26c9ac3
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

# We need to set GIT_DIR to workaround the nasty poetry bug:
# https://github.com/python-poetry/poetry/issues/5547.
# Without this some tests (like test_includes_with_inline_table) fails.
COMPONENT_TEST_ENV += GIT_DIR=$(BUILD_DIR)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += runtime/python
