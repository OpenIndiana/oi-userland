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
HUMAN_VERSION =			67.7.0
COMPONENT_SUMMARY =		setuptools - Easily download, build, install, upgrade, and uninstall Python packages
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/68/86/d82a2a8f3f63f0dad4cb287dbae0cac178efb6267b07e0aef8b072866032/setuptools-67.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b7e53a01c6c654d26d2999ee033d8c6125e5fa55f03b7b193f937ae7ac999f22
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
TEST_REQUIRED_PACKAGES.python += library/python/flake8
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
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-perf
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/tomli-w
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
