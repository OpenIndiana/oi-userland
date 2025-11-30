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
#   $WS_TOOLS/python-integrate-project cffi
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cffi
HUMAN_VERSION =			2.0.0
COMPONENT_SUMMARY =		Foreign Function Interface for Python calling C code.
COMPONENT_ARCHIVE_HASH =	\
	sha256:44d1b5909021139fe36001ae048dbdde8214afa20200eda0f64c068cac5d5529
COMPONENT_LICENSE =		MIT-0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This is needed for the test_errno_working_even_with_pypys_jit test.  Please
# see note in the test (file testing/cffi0/test_verify.py) for details.
CFLAGS += -pthread

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/pycparser
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
