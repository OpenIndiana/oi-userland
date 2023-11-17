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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		rpds_py
HUMAN_VERSION =			0.13.0
COMPONENT_SUMMARY =		rpds_py - Python bindings to Rust's persistent data structures (rpds)
COMPONENT_PROJECT_URL =		https://github.com/crate-py/rpds
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/81/b8/c18e4fa683dd67fd2f1b9239648ba8c29fed467b4aa80387b14116e3a06b/rpds_py-0.13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:35cc91cbb0b775705e0feb3362490b8418c408e9e3c3b9cb3b02f6e495f03ee7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/maturin
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-10-runtime
