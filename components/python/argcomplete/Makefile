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
HUMAN_VERSION =			3.1.6
COMPONENT_SUMMARY =		argcomplete - Bash tab completion for argparse
COMPONENT_PROJECT_URL =		https://github.com/kislyuk/argcomplete
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c0/da/2565ca2ea7609388b49697653ef60c8588a61fa59346c56151c16e6ea0c6/argcomplete-3.1.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3b1f07d133332547a53c79437527c00be48cca3807b1d4ca5cab1b26313386a6
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
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
