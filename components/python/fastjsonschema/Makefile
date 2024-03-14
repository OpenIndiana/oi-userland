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
HUMAN_VERSION =			2.19.1
COMPONENT_SUMMARY =		fastjsonschema - Fastest Python implementation of JSON schema
COMPONENT_PROJECT_URL =		https://github.com/horejsek/python-fastjsonschema
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ba/7f/cedf77ace50aa60c566deaca9066750f06e1fcf6ad24f254d255bb976dd6/fastjsonschema-2.19.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e3126a94bdc4623d3de4485f8d468a12f02a67921315ddc87836d6e456dc789d
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in benchmarks
PYTEST_ADDOPTS += -m 'not benchmark'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
