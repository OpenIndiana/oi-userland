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
#   $WS_TOOLS/python-integrate-project packaging
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		packaging
COMPONENT_VERSION =		21.3
COMPONENT_SUMMARY =		packaging - Core utilities for Python packages
COMPONENT_PROJECT_URL =		https://github.com/pypa/packaging
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/df/9e/d1a7217f69310c1db8fdf8ab396229f55a699ce34a203691794c5d1cad0c/packaging-21.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:dd47c42927d89ab911e606518907cc2d3a1f38bbd026385970643f9c5b8ecfeb
COMPONENT_LICENSE =		Apache-2.0 OR BSD-2-Clause

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - setuptools_scm
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
