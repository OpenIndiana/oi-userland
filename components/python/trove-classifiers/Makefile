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
HUMAN_VERSION =			2024.9.12
COMPONENT_SUMMARY =		Canonical source for classifiers on PyPI (pypi.org).
COMPONENT_PROJECT_URL =		https://github.com/pypa/trove-classifiers
COMPONENT_ARCHIVE_HASH =	\
	sha256:4b46b3e134a4d01999ac5bc6e528afcc10cc48f0f724f185f267e276005768f4
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - hatchling (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/calver
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
