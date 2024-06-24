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
#   $WS_TOOLS/python-integrate-project flake8
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flake8
HUMAN_VERSION =			7.1.0
COMPONENT_SUMMARY =		the modular source code checker: pep8 pyflakes and co
COMPONENT_PROJECT_URL =		https://github.com/pycqa/flake8
COMPONENT_ARCHIVE_URL =		\
	https://github.com/PyCQA/flake8/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:af2223f8d6476097ac0bf58a08910fa19b4c045d37f6c8e26532d3f4076b78ba
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing expects there are no additional flake8 plugins installed otherwise
# some tests will fail.
TEST_CONFLICTING_PACKAGES.python += library/python/flake8-2020
TEST_CONFLICTING_PACKAGES.python += library/python/flake8-bugbear
TEST_CONFLICTING_PACKAGES.python += library/python/flake8-docstrings
TEST_CONFLICTING_PACKAGES.python += library/python/flake8-noqa
TEST_CONFLICTING_PACKAGES.python += library/python/flake8-typing-imports
TEST_CONFLICTING_PACKAGES.python += library/python/teamcity-messages

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/mccabe
PYTHON_REQUIRED_PACKAGES += library/python/pycodestyle
PYTHON_REQUIRED_PACKAGES += library/python/pyflakes
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/pytest
