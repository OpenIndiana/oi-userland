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
#   $WS_TOOLS/python-integrate-project maturin
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		maturin
HUMAN_VERSION =			1.1.0
COMPONENT_SUMMARY =		maturin - Build and publish crates with pyo3, rust-cpython and cffi bindings as well as rust binaries as python packages
COMPONENT_PROJECT_URL =		https://github.com/pyo3/maturin
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7b/78/2814bc0e46a96861aab337fd0404e7937acdb4ce187da239224ab4560d35/maturin-1.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4650aeaa8debd004b55aae7afb75248cbd4d61cd7da2dcf4ead8b22b58cecae0
COMPONENT_LICENSE =		Apache-2.0 OR MIT

# https://github.com/PyO3/maturin/issues/1674
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-rust
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
