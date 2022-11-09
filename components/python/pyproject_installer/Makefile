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
COMPONENT_VERSION =		0.3.1
COMPONENT_SUMMARY =		pyproject_installer - Pyproject installer
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7f/4f/e8eef34fcbe43f06309e52a0ca499fadb62213665d9be3e22969fba9a07c/pyproject_installer-0.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8cbfd68f7f3020a886d94eb4af8fc98eae3b91b53f656817a3fb1b01c93f2747
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# The pyproject_installer is the bootstrapper so it cannot use any non-core
# Python modules and it needs to be bootstrapped.
PYTHON_BOOTSTRAP = yes

# This project requires Python >= 3.8.  Once we add support for new Python
# version (>= 3.8), such version needs to be added to PYTHON_VERSIONS below.
# Once we obsolete Python 3.7 the PYTHON_VERSIONS line should be removed.
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
