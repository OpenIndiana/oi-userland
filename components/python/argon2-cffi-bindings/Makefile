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
#   $WS_TOOLS/python-integrate-project -d python/argon2-cffi-bindings argon2_cffi_bindings
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		argon2_cffi_bindings
HUMAN_VERSION =			26.2.0
COMPONENT_SUMMARY =		Low-level CFFI bindings for Argon2
COMPONENT_ARCHIVE_HASH =	\
	sha256:f21ab89bb9850f32b9ca038d9961424bb0d3669d579cbbbfed068cffa6fc0643
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by argon2-cffi-bindings >= 26.1.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cffi
REQUIRED_PACKAGES.python += library/python/scikit-build-core
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
