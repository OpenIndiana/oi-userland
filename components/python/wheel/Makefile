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
#   $WS_TOOLS/python-integrate-project wheel
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wheel
HUMAN_VERSION =			0.41.0
COMPONENT_SUMMARY =		wheel - A built-package format for Python
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ec/34/903929e15b2657335b2ce8723d92fc804d3569b7ac0f1f8877ed1a7b2024/wheel-0.41.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:55a0f0a5a84869bce5ba775abfd9c462e3a6b1b7b7ec69d72c0b83d673a5114d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - cachetools (test bootstrap)
# - chardet (test bootstrap)
# - distlib (test bootstrap)
# - importlib_metadata
# - pluggy (test bootstrap)
# - pytest (test bootstrap)
# - setuptools
# - tox-current-env (test bootstrap)
# - trove-classifiers (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
