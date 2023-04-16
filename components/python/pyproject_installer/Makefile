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
#   $WS_TOOLS/python-integrate-project pyproject_installer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_installer
HUMAN_VERSION =			0.5.0
COMPONENT_SUMMARY =		pyproject_installer - Pyproject installer
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/79/ae/8bc349979ef640e3a9e4ab570d055ffbf8e22d1f92de4f6e06c3f58e154a/pyproject_installer-0.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:979f6db0dfe4db468fe297ffabde8fa4af03054ce681482370faff5313cdd5f3
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# The pyproject_installer is the bootstrapper so it cannot use any non-core
# Python modules and it needs to be bootstrapped.
PYTHON_BOOTSTRAP = yes

# This project requires Python >= 3.8.  Once we add support for new Python
# version (>= 3.8), such version needs to be added to PYTHON_VERSIONS below.
# Once we obsolete Python 3.7 the PYTHON_VERSIONS line should be removed.
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
