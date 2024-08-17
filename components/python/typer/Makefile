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
#   $WS_TOOLS/python-integrate-project typer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		typer
HUMAN_VERSION =			0.12.4
COMPONENT_SUMMARY =		Typer, build great CLIs. Easy to code. Based on Python type hints.
COMPONENT_PROJECT_URL =		https://github.com/fastapi/typer
COMPONENT_ARCHIVE_HASH =	\
	sha256:c9c1613ed6a166162705b3347b8d10b661ccc5d95692654d0fb628118f2c34e6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements-tests.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/click
PYTHON_REQUIRED_PACKAGES += library/python/pdm-backend
PYTHON_REQUIRED_PACKAGES += library/python/rich
PYTHON_REQUIRED_PACKAGES += library/python/shellingham
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/rich
TEST_REQUIRED_PACKAGES.python += library/python/shellingham
TEST_REQUIRED_PACKAGES.python += library/python/tomli
