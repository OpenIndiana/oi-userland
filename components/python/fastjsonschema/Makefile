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
HUMAN_VERSION =			2.21.1
COMPONENT_SUMMARY =		Fastest Python implementation of JSON schema
COMPONENT_PROJECT_URL =		https://github.com/horejsek/python-fastjsonschema
COMPONENT_ARCHIVE_HASH =	\
	sha256:794d4f0a58f848961ba16af7b9c85a3e88cd360df008c59aac6fc5ae9323b5d4
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in benchmarks
PYTEST_ADDOPTS += -m 'not benchmark'

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
