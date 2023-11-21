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
HUMAN_VERSION =			69.0.1
COMPONENT_SUMMARY =		setuptools - Easily download, build, install, upgrade, and uninstall Python packages
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/fb/d0/d5744a7190a984ab728c7d2bd7e39bae2ff523538b233246fd34e2148566/setuptools-69.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f25195d54deb649832182d6455bffba7ac3d8fe71d35185e738d2198a4310044
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - cachetools (test bootstrap)
# - calver (test bootstrap)
# - chardet (test bootstrap)
# - distlib (test bootstrap)
# - importlib_metadata
# - pluggy (test bootstrap)
# - pytest (test bootstrap)
# - setuptools-scm
# - tox-current-env (test bootstrap)
# - trove-classifiers (test bootstrap)
# - zipp
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pypa/setuptools/issues/4050
PYTEST_ADDOPTS += '-p no:perf'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/flake8-2020
TEST_REQUIRED_PACKAGES.python += library/python/ini2toml
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-develop
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-envs
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-path
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-perf
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
