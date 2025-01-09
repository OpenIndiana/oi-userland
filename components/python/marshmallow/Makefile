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
HUMAN_VERSION =			3.24.2
COMPONENT_SUMMARY =		A lightweight library for converting complex datatypes to and from native Python datatypes.
COMPONENT_ARCHIVE_HASH =	\
	sha256:0822c3701de396b51d3f8ac97319aea5493998ba4e7d0e4c05f6fce7777bf3a2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Normalize timetstamps that change with every run
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..-..-.... ..:..:..\]/[XX-XX-XXXX XX:XX:XX]/'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\[..:..:.. ....-..-..\]/[XX:XX:XX XXXX-XX-XX]/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/simplejson
