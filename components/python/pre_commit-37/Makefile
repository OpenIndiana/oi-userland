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
#   $WS_TOOLS/python-integrate-project pre_commit
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pre_commit
HUMAN_VERSION =			2.21.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pre_commit - A framework for managing and maintaining multi-language pre-commit hooks.
COMPONENT_PROJECT_URL =		https://github.com/pre-commit/pre-commit
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6b/00/1637ae945c6e10838ef5c41965f1c864e59301811bb203e979f335608e7c/pre_commit-2.21.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:31ef31af7e474a8d8995027fefdfcf509b5c913ff31f2015b4ec4beb26a6f658
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# pre_commit-3.3.0 was mistakenly packaged for Python 3.7
COMPONENT_VERSION =		3.3.0

# pre_commit >= 3.0.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

# https://github.com/pre-commit/pre-commit/issues/2609
# https://github.com/pre-commit/pre-commit/issues/2872
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cfgv
PYTHON_REQUIRED_PACKAGES += library/python/identify
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/nodeenv
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += runtime/python
