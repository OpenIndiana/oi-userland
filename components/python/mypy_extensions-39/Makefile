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
#   $WS_TOOLS/python-integrate-project -d python/mypy_extensions-39 mypy_extensions
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mypy_extensions
HUMAN_VERSION =			1.1.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Type system extensions for programs checked with the mypy type checker.
COMPONENT_PROJECT_URL =		https://github.com/python/mypy_extensions
COMPONENT_ARCHIVE_HASH =	\
	sha256:52e68efc3284861e772bbcd66823fde5ae21fd2fdb51c62a211403730b916558
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# mypy-extensions >= 1.2.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
