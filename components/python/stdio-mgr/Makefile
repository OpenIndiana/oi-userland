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
#   $WS_TOOLS/python-integrate-project stdio-mgr
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		stdio-mgr
HUMAN_VERSION =			1.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Context manager for mocking/wrapping stdin/stdout/stderr
COMPONENT_PROJECT_URL =		https://www.github.com/bskinn/stdio-mgr
COMPONENT_ARCHIVE_URL =		\
	https://github.com/bskinn/stdio-mgr/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b70044b1b31b9be3935d0b1e3ada3d713f7274d2124ffff42195e1fdac0a4029
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# https://github.com/bskinn/stdio-mgr/issues/99
PYTEST_ADDOPTS += --deselect README.rst::README.rst

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/attrs
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
