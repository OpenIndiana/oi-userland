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
#   $WS_TOOLS/python-integrate-project argcomplete
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		argcomplete
HUMAN_VERSION =			3.5.1
COMPONENT_SUMMARY =		Bash tab completion for argparse
COMPONENT_PROJECT_URL =		https://github.com/kislyuk/argcomplete
COMPONENT_ARCHIVE_HASH =	\
	sha256:eb1ee355aa2557bd3d0145de7b06b2a45b0ce461e1e7813f5d066039ab4177b4
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.rst

# The automatically detected pytest test style does not work properly
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find test_package
COMPONENT_TEST_ENV += PYTHONPATH=$(@D)/test/test_package:$(PROTO_DIR)/$(PYTHON_LIB)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
