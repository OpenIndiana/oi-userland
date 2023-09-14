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
HUMAN_VERSION =			0.10.3
COMPONENT_SUMMARY =		rpds_py - Python bindings to Rust's persistent data structures (rpds)
COMPONENT_PROJECT_URL =		https://github.com/crate-py/rpds
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/52/fa/31c7210f4430317c890ed0c8713093843442a98d8a9cafd0333c0040dda4/rpds_py-0.10.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fcc1ebb7561a3e24a6588f7c6ded15d80aec22c66a070c757559b57b17ffd1cb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/maturin
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
