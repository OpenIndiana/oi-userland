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
#   $WS_TOOLS/python-integrate-project markdown-it-py
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		markdown-it-py
HUMAN_VERSION =			2.2.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		markdown-it-py - Python port of markdown-it. Markdown parsing, done right!
COMPONENT_PROJECT_URL =		https://github.com/executablebooks/markdown-it-py
COMPONENT_ARCHIVE_URL =		\
	https://github.com/executablebooks/markdown-it-py/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a201c93c023d0c810023b38f3e9ad48be433095c5437d5410af04a73665c8ff1
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# markdown-it-py >= 3.0.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

include $(WS_MAKE_RULES)/common.mk

# https://github.com/executablebooks/markdown-it-py/issues/288
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-mypy-plugins

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/mdurl
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/linkify-it-py
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
