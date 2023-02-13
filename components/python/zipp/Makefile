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
#   $WS_TOOLS/python-integrate-project zipp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zipp
HUMAN_VERSION =			3.13.0
COMPONENT_SUMMARY =		zipp - Backport of pathlib-compatible object wrapper for zip files
COMPONENT_PROJECT_URL =		https://github.com/jaraco/zipp
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d1/2f/ba544a8a6ad5ad9dcec1b00f536bb9fb078f5f50d1a1408876de18a9151b/zipp-3.13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:23f70e964bc11a34cef175bc90ba2914e1e4545ea1e3e2f67c079671883f9cb6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib-metadata
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/func-timeout
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-functools
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-itertools
TEST_REQUIRED_PACKAGES.python += library/python/more-itertools
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
