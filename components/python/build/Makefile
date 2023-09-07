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
#   $WS_TOOLS/python-integrate-project build
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		build
HUMAN_VERSION =			1.0.3
COMPONENT_SUMMARY =		build - A simple, correct Python build frontend
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/98/e3/83a89a9d338317f05a68c86a2bbc9af61235bc55a0c6a749d37598fb2af1/build-1.0.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:538aab1b64f9828977f84bc63ae570b060a8ed1be419e7870b8b4fc5e6ea553b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Since we cannot use the 'build' package to build itself we need to bootstrap.
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# This is to make sure we do not run pytest with "-n auto" because it is hard
# to normalize pytest-xdist test results.
COMPONENT_TEST_TARGETS += --

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pyproject-hooks
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
TEST_REQUIRED_PACKAGES.python += library/python/wheel
