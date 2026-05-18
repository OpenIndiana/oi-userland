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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.packaging jaraco_packaging
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_packaging
HUMAN_VERSION =			10.4.0
COMPONENT_SUMMARY =		tools to supplement packaging Python releases
COMPONENT_ARCHIVE_HASH =	\
	sha256:7537e3a2be1c90f8442442cec6e31a9a2fd0a022223b0986286f08492483fc88
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# We temporarily build for Python 3.9 only because we do not have some
# dependecies built for Python 3.14 yet.
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/build
REQUIRED_PACKAGES.python += library/python/coherent-licensed
REQUIRED_PACKAGES.python += library/python/domdf-python-tools
REQUIRED_PACKAGES.python += library/python/jaraco-context
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/sphinx
REQUIRED_PACKAGES.python += library/python/virtualenv
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/types-docutils
