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
HUMAN_VERSION =			3.1.2
COMPONENT_SUMMARY =		argcomplete - Bash tab completion for argparse
COMPONENT_PROJECT_URL =		https://github.com/kislyuk/argcomplete
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1b/c5/fb934dda06057e182f8247b2b13a281552cf55ba2b8b4450f6e003d0469f/argcomplete-3.1.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d5d1e5efd41435260b8f85673b74ea2e883affcbec9f4230c582689e8e78251b
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
