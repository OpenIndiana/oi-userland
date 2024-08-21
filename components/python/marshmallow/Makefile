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
HUMAN_VERSION =			3.22.0
COMPONENT_SUMMARY =		A lightweight library for converting complex datatypes to and from native Python datatypes.
COMPONENT_ARCHIVE_HASH =	\
	sha256:4972f529104a220bb8637d595aa4c9762afbe7f7a77d82dc58c1615d70c5823e
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
TEST_REQUIRED_PACKAGES.python += library/python/pytz
TEST_REQUIRED_PACKAGES.python += library/python/simplejson
