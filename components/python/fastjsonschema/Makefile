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
#   $WS_TOOLS/python-integrate-project fastjsonschema
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fastjsonschema
HUMAN_VERSION =			2.19.0
COMPONENT_SUMMARY =		fastjsonschema - Fastest Python implementation of JSON schema
COMPONENT_PROJECT_URL =		https://github.com/horejsek/python-fastjsonschema
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7a/61/5fc12c3a9b206e2d85399253ecbe602a753bfb54ae891bc74819ab594312/fastjsonschema-2.19.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e25df6647e1bc4a26070b700897b07b542ec898dd4f1f6ea013e7f6a88417225
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in benchmarks
PYTEST_ADDOPTS += -m 'not benchmark'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
