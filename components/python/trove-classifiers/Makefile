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
#   $WS_TOOLS/python-integrate-project -d python/trove-classifiers trove_classifiers
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		trove_classifiers
HUMAN_VERSION =			2026.5.7.17
COMPONENT_SUMMARY =		Canonical source for classifiers on PyPI (pypi.org).
COMPONENT_PROJECT_URL =		https://github.com/pypa/trove-classifiers
COMPONENT_ARCHIVE_HASH =	\
	sha256:a04a48f8f0a787cb996514d3969ac7608aa3c60cb15d073c1e02801e60533e80
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - hatchling (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/calver
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
