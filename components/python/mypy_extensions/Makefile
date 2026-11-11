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
#   $WS_TOOLS/python-integrate-project mypy_extensions
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mypy_extensions
HUMAN_VERSION =			1.2.0
COMPONENT_SUMMARY =		Type system extensions for programs checked with the mypy type checker.
COMPONENT_PROJECT_URL =		https://github.com/python/mypy_extensions
COMPONENT_ARCHIVE_HASH =	\
	sha256:c6e275a07f1c2fc096b62940452d0eaa3f3af7de45d704787866240a7c6d5a51
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by mypy-extensions >= 1.2.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
