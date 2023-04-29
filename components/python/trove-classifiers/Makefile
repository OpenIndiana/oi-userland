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
#   $WS_TOOLS/python-integrate-project trove-classifiers
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		trove-classifiers
HUMAN_VERSION =			2023.4.29
COMPONENT_SUMMARY =		trove-classifiers - Canonical source for classifiers on PyPI (pypi.org).
COMPONENT_PROJECT_URL =		https://github.com/pypa/trove-classifiers
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c8/9b/8e1a88794d21abb90349c7d0decbee3efe31b4b74987c51d815fc5784c81/trove-classifiers-2023.4.29.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8adcc06f1eb7c495f0bdceb698bd9c044b3e57b0d5767d99ec4b6b17c9bbe957
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
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
