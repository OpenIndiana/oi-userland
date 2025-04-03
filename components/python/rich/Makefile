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
#   $WS_TOOLS/python-integrate-project rich
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		rich
HUMAN_VERSION =			14.0.0
COMPONENT_SUMMARY =		Render rich text, tables, progress bars, syntax highlighting, markdown and more to the terminal
COMPONENT_PROJECT_URL =		https://github.com/Textualize/rich
COMPONENT_ARCHIVE_URL =		\
	https://github.com/Textualize/rich/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0a1a45eb997b6fd1b133192b9590c9de9bd7fe7e2948540b4433d4ba413f331c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# This project uses poetry to manage test dependencies.
TEST_REQUIREMENTS_POETRY += dev

# https://github.com/Textualize/rich/issues/3612
PYTEST_ADDOPTS += --deselect test_markdown.py::test_inline_code
PYTEST_ADDOPTS += --deselect test_syntax.py::test_blank_lines
PYTEST_ADDOPTS += --deselect test_syntax.py::test_python_render_simple_indent_guides

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/markdown-it-py
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
