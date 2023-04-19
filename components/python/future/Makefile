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
#   $WS_TOOLS/python-integrate-project future
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		future
HUMAN_VERSION =			0.18.3
COMPONENT_SUMMARY =		future - Clean single-source support for Python 3 and 2
COMPONENT_PROJECT_URL =		https://python-future.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8f/2e/cf6accf7415237d6faeeebdc7832023c90e0282aa16fd3263db0eb4715ec/future-0.18.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:34a17436ed1e96697a86f9de3d15a3b0be01d8bc8de9c1dffd59fb8234ed5307
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/PythonCharmers/python-future/issues/593
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
