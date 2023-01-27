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
HUMAN_VERSION =			6.0.0
COMPONENT_SUMMARY =		importlib_metadata - Read metadata from Python packages
COMPONENT_PROJECT_URL =		https://github.com/python/importlib_metadata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/90/07/6397ad02d31bddf1841c9ad3ec30a693a3ff208e09c2ef45c9a8a5f85156/importlib_metadata-6.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e354bedeb60efa6affdcc8ae121b73544a7aa74156d047311948f6d711cd378d
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - chardet (test bootstrap)
# - hatchling (test bootstrap)
# - pluggy (test bootstrap)
# - pytest (test bootstrap)
# - tox (test bootstrap)
# - tox-current-env (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/zipp
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/flufl-flake8
TEST_REQUIRED_PACKAGES.python += library/python/importlib-resources
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pyfakefs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-perf
