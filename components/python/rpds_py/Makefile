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
#   $WS_TOOLS/python-integrate-project rpds_py
#

BUILD_STYLE = pyproject
CARGO_VENDOR = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		rpds_py
HUMAN_VERSION =			2026.6.3
COMPONENT_SUMMARY =		Python bindings to Rust's persistent data structures (rpds)
COMPONENT_PROJECT_URL =		https://github.com/crate-py/rpds
COMPONENT_ARCHIVE_HASH =	\
	sha256:1cebd1337c242e4ec2293e541f712b2da849b29f48f0c293684b71c0632625d4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# Python 3.9 is not supported by rpds-py >= 0.28.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += runtime/python
