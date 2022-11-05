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
#   $WS_TOOLS/python-integrate-project setuptools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools
COMPONENT_VERSION =		65.5.1
COMPONENT_SUMMARY =		setuptools - Easily download, build, install, upgrade, and uninstall Python packages
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/26/f4/ca5cb6df512f453ad50f78900bf7ec6a5491ee44bb49d0f6f76802dbdd43/setuptools-65.5.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e197a19aa8ec9722928f2206f8de752def0e4c9fc6953527360d1c36d94ddb2f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# The bootstrapped 'build' component requires setuptools to build so setuptools
# must be bootstrapped too.
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
