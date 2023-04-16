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
#   $WS_TOOLS/python-integrate-project pip-run
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pip-run
HUMAN_VERSION =			10.0.7
COMPONENT_SUMMARY =		pip-run - install packages and run Python with them
COMPONENT_PROJECT_URL =		https://github.com/jaraco/pip-run
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b0/30/52302b9f7e1c3f35900db765c8b45d5d911a6dfa2b8b5dcbe8751abe4e2b/pip-run-10.0.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:73273a6d267580449fc426f79beef1573ea97b51d44c9a05b74f635103243b1a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tholo/pytest-flake8/issues/92
PYTEST_ADDOPTS += -p no:flake8

# Revert back unneeded PYV normalizations
COMPONENT_TEST_TRANSFORMS += "-e 's/py\$$(PYV)compat/py$(shell echo $(PYTHON_VERSION) | tr -d .)compat/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/autocommand
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/importlib-resources
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-text
PYTHON_REQUIRED_PACKAGES += library/python/more-itertools
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/path
PYTHON_REQUIRED_PACKAGES += library/python/pip
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-path
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-test
TEST_REQUIRED_PACKAGES.python += library/python/nbformat
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
