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
#   $WS_TOOLS/python-integrate-project zipp
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zipp
HUMAN_VERSION =			3.20.2
COMPONENT_SUMMARY =		Backport of pathlib-compatible object wrapper for zip files
COMPONENT_ARCHIVE_HASH =	\
	sha256:bc9eb26f4506fda01b81bcde0ca78103b6e62f991b381fec825435c836edbc29
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib-metadata
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-functools
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-itertools
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-test
TEST_REQUIRED_PACKAGES.python += library/python/more-itertools
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-ignore-flaky
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
