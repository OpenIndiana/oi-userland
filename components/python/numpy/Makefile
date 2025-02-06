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
#   $WS_TOOLS/python-integrate-project numpy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		numpy
HUMAN_VERSION =			2.0.2
COMPONENT_SUMMARY =		Fundamental package for array computing in Python
COMPONENT_PROJECT_URL =		https://numpy.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:883c987dee1880e2a864ab0dc9892292582510604156762362d9326444636e78
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# NumPy Tests must be run outside source directory so switch to the proto area
COMPONENT_TEST_DIR = $(PROTO_DIR)/$(PYTHON_LIB)

# https://github.com/numpy/numpy/issues/27670
# https://www.illumos.org/issues/5346
PYTEST_ADDOPTS += --deselect numpy/_core/tests/test_longdouble.py::test_str_roundtrip
PYTEST_ADDOPTS += --deselect numpy/_core/tests/test_print.py::TestCommaDecimalPointLocale::test_locale_longdouble
PYTEST_ADDOPTS += --deselect numpy/lib/tests/test_function_base.py::TestPercentile::test_linear_interpolation[inverted_cdf-False-20-longdouble-longdouble-quantile-0.4]
PYTEST_ADDOPTS += --deselect numpy/lib/tests/test_function_base.py::TestPercentile::test_linear_interpolation[averaged_inverted_cdf-False-27.5-longdouble-longdouble-quantile-0.4]

# https://www.illumos.org/issues/16874
PYTEST_ADDOPTS += --deselect numpy/_core/tests/test_umath.py::TestSpecialFloats::test_exp2

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += library/python/meson-python
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
