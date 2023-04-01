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
#   $WS_TOOLS/python-integrate-project jaraco.collections
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco.collections
HUMAN_VERSION =			4.0.0
COMPONENT_SUMMARY =		jaraco.collections - Collection objects similar to those in stdlib by jaraco
COMPONENT_PROJECT_URL =		https://github.com/jaraco/jaraco.collections
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ff/d1/b06e9c9c3343c5bb056c84376e0cc19c3d94108454e495bda1f402f37ed8/jaraco.collections-4.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9bbe39e1a13c73cb471f6114a2b3cb21d704c2e3271ad5a60daf94a436dec939
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tholo/pytest-flake8/issues/92
PYTEST_ADDOPTS += -p no:flake8

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-text
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
