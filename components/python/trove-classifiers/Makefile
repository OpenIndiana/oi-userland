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
HUMAN_VERSION =			2023.11.7
COMPONENT_SUMMARY =		trove-classifiers - Canonical source for classifiers on PyPI (pypi.org).
COMPONENT_PROJECT_URL =		https://github.com/pypa/trove-classifiers
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/90/58/e1bb61d071e889320698017415621373b95bb86c8c491c62df845f3de08f/trove-classifiers-2023.11.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ef85282f6ec9c028b5349ae9bab4f384f770bb4883a15694318e1b1a5cedf5fe
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
