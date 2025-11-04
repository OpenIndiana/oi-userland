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
#   $WS_TOOLS/python-integrate-project marshmallow
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		marshmallow
HUMAN_VERSION =			4.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A lightweight library for converting complex datatypes to and from native Python datatypes.
COMPONENT_ARCHIVE_HASH =	\
	sha256:e1d860bd262737cb2d34e1541b84cb52c32c72c9474e3fe6f30f137ef8b0d97f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# runtime dependencies differs for Python < 3.11
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/marshmallow-code/marshmallow/issues/2862
PYTEST_ADDOPTS += --deselect tests/test_utils.py::test_from_timestamp_with_overflow_value

# Normalize timetstamps that change with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..-..-.... ..:..:..\]/[XX-XX-XXXX XX:XX:XX]/'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..:..:.. ....-..-..\]/[XX:XX:XX XXXX-XX-XX]/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/simplejson
