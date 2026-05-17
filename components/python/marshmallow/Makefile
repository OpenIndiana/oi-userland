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
HUMAN_VERSION =			4.3.0
COMPONENT_SUMMARY =		A lightweight library for converting complex datatypes to and from native Python datatypes.
COMPONENT_ARCHIVE_HASH =	\
	sha256:fb43c53b3fe240b8f6af37223d6ef1636f927ad9bea8ab323afad95dff090880
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by marshmallow >= 4.1.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Normalize timetstamps that change with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..-..-.... ..:..:..\]/[XX-XX-XXXX XX:XX:XX]/'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..:..:.. ....-..-..\]/[XX:XX:XX XXXX-XX-XX]/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/simplejson
