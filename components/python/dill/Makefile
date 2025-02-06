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
#   $WS_TOOLS/python-integrate-project dill
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dill
HUMAN_VERSION =			0.3.9
COMPONENT_SUMMARY =		serialize all of Python
COMPONENT_PROJECT_URL =		https://github.com/uqfoundation/dill
COMPONENT_ARCHIVE_HASH =	\
	sha256:81aa267dddf68cbfe8029c42ca9ec6a4ab3b22371d1c450abc54422577b4512c
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/\(lambda> at \)0x[0-9a-f]\{1,\}/\1\$$(POINTER)/g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/objgraph
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
