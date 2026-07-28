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
#   $WS_TOOLS/python-integrate-project -d python/fastjsonschema-39 fastjsonschema
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fastjsonschema
HUMAN_VERSION =			2.21.2
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Fastest Python implementation of JSON schema
COMPONENT_PROJECT_URL =		https://github.com/horejsek/python-fastjsonschema
COMPONENT_ARCHIVE_HASH =	\
	sha256:b1eb43748041c880796cd077f1a07c3d94e93ae84bba5ed36800a33554ae05de
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# fastjsonschema >= 2.22.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# We are not interested in benchmarks
PYTEST_ADDOPTS += -m 'not benchmark'

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
