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
#   $WS_TOOLS/python-integrate-project flit_scm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flit_scm
HUMAN_VERSION =			1.7.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		A PEP 518 build backend that uses setuptools_scm to generate a version file from your version control system, then flit to build the package.
COMPONENT_PROJECT_URL =		https://gitlab.com/WillDaSilva/flit_scm
COMPONENT_ARCHIVE_HASH =	\
	sha256:961bd6fb24f31bba75333c234145fff88e6de0a90fc0f7e5e7c79deca69f6bb2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - exceptiongroup (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += runtime/python
