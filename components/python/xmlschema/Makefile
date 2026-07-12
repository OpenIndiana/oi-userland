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
#   $WS_TOOLS/python-integrate-project xmlschema
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		xmlschema
HUMAN_VERSION =			4.3.2
COMPONENT_SUMMARY =		An XML Schema validator and decoder
COMPONENT_PROJECT_URL =		https://github.com/sissaschool/xmlschema
COMPONENT_ARCHIVE_HASH =	\
	sha256:f3b33a21a2b2cdc404ddc3fb599d8bc1dee90b155d547370672e6e684746b8d6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by xmlschema >= 4.3.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/elementpath
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/elementpath
TEST_REQUIRED_PACKAGES.python += library/python/jinja2
TEST_REQUIRED_PACKAGES.python += library/python/lxml
