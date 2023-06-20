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
#   $WS_TOOLS/python-integrate-project setuptools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools
HUMAN_VERSION =			68.0.0
COMPONENT_SUMMARY =		setuptools - Easily download, build, install, upgrade, and uninstall Python packages
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dc/98/5f896af066c128669229ff1aa81553ac14cfb3e5e74b6b44594132b8540e/setuptools-68.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:baf1fdb41c6da4cd2eae722e135500da913332ab3f2f5c7d33af9b492acb5235
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - cachetools (test bootstrap)
# - calver (test bootstrap)
# - chardet (test bootstrap)
# - distlib (test bootstrap)
# - editables (test bootstrap)
# - importlib_metadata
# - pluggy (test bootstrap)
# - pytest (test bootstrap)
# - setuptools_scm
# - tox-current-env (test bootstrap)
# - trove-classifiers (test bootstrap)
# - zipp
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/flake8-2020
TEST_REQUIRED_PACKAGES.python += library/python/ini2toml
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-envs
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-path
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pip-run
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-perf
TEST_REQUIRED_PACKAGES.python += library/python/pytest-ruff
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
