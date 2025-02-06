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
HUMAN_VERSION =			1.2.2.post1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A simple, correct Python build frontend
COMPONENT_ARCHIVE_HASH =	\
	sha256:b36993e92ca9375a219c99e606a122ff365a760a2d4bba0caa09bd5278b608b7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Since we cannot use the 'build' package to build itself we need to bootstrap.
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Avoid rewrite failure with xdist
PYTEST_ADDOPTS += --assert=plain

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

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
