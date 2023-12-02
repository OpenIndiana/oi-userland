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
#   $WS_TOOLS/python-integrate-project importlib_metadata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		importlib_metadata
HUMAN_VERSION =			6.9.0
COMPONENT_SUMMARY =		importlib_metadata - Read metadata from Python packages
COMPONENT_PROJECT_URL =		https://github.com/python/importlib_metadata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/97/4b/54711968ae127aa7c781017c85344477ed7da8e8493a06f02cd92bdc8dae/importlib_metadata-6.9.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e8acb523c335a91822674e149b46c0399ec4d328c4d1f6e49c273da5ff0201b9
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - tox-current-env (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/jaraco/pytest-perf/issues/6
PYTEST_ADDOPTS += '-p no:perf'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += library/python/zipp
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flufl-flake8
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pyfakefs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-perf
