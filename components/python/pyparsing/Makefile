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
#   $WS_TOOLS/python-integrate-project pyparsing
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyparsing
HUMAN_VERSION =			3.1.1
COMPONENT_SUMMARY =		pyparsing - pyparsing module - Classes and methods to define and execute parsing grammars
COMPONENT_PROJECT_URL =		https://github.com/pyparsing/pyparsing/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/37/fe/65c989f70bd630b589adfbbcd6ed238af22319e90f059946c26b4835e44b/pyparsing-3.1.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ede28a1a32462f5a9705e07aea48001a08f7cf81a021585011deba701581a0db
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/jinja2
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/railroad-diagrams
