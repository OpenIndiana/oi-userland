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
HUMAN_VERSION =			2.18.1
COMPONENT_SUMMARY =		fastjsonschema - Fastest Python implementation of JSON schema
COMPONENT_PROJECT_URL =		https://github.com/horejsek/python-fastjsonschema
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/82/d1/0e54b17b6ebae7a347602bb07bb2f5c4cff9bdbbd354f202b3af48f22f75/fastjsonschema-2.18.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:06dc8680d937628e993fa0cd278f196d20449a1adc087640710846b324d422ea
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# We are not interested in benchmarks
PYTEST_ADDOPTS += -m 'not benchmark'
# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
