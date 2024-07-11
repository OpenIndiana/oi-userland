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
#   $WS_TOOLS/python-integrate-project importcheck
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		importcheck
HUMAN_VERSION =			0.5.0
COMPONENT_SUMMARY =		A tool to check all modules can be correctly imported.
COMPONENT_PROJECT_URL =		https://github.com/python-coincidence/importcheck
COMPONENT_ARCHIVE_URL =		\
	https://github.com/python-coincidence/importcheck/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:848de325ef4bba87c36bd3af81151c0f376ca54bc73c43d2d1858aa44e87da13
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Remove line with timestamp
COMPONENT_TEST_TRANSFORMS += "-e '/^Test session started at/d'"

# https://github.com/python-coincidence/importcheck/issues/59
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir

# pytest-regressions is needed by coincidence so it will be always installed,
# but we need to list it explicitly here to make sure it is enabled
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/click
PYTHON_REQUIRED_PACKAGES += library/python/consolekit
PYTHON_REQUIRED_PACKAGES += library/python/dom-toml
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/whey
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
