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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		argcomplete
HUMAN_VERSION =			3.1.0
COMPONENT_SUMMARY =		argcomplete - Bash tab completion for argparse
COMPONENT_PROJECT_URL =		https://github.com/kislyuk/argcomplete
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/43/30/09472981132ae3783d43367cbda65abec3e04aa233593877bc9e8982ff41/argcomplete-3.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3a81445fa51c9875c36789ae5386d5e95c5c43d503963a0029a747aea74de1e3
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.rst

# The automatically detected pytest test style does not work properly
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# Testing needs to find test_package
COMPONENT_TEST_ENV += PYTHONPATH=$(@D)/test/test_package:$(PROTO_DIR)/$(PYTHON_LIB)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
