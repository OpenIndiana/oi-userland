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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.functools-39 jaraco_functools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_functools
HUMAN_VERSION =			4.4.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Functools like those found in stdlib
COMPONENT_ARCHIVE_HASH =	\
	sha256:da21933b0417b89515562656547a77b4931f98176eb173644c0d35032a33d6bb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# jaraco.functools >= 4.5.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/coherent-licensed
REQUIRED_PACKAGES.python += library/python/more-itertools
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-classes
TEST_REQUIRED_PACKAGES.python += library/python/pytest
