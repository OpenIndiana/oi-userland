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
#   $WS_TOOLS/python-integrate-project pytest_check
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_check
HUMAN_VERSION =			2.3.0
COMPONENT_SUMMARY =		pytest_check - A pytest plugin that allows multiple failures per test.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/06/bb/4766884834d2e03f3b95b76e25d857ce161227f45228556d0568ae2c63d5/pytest_check-2.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6e5a2dbbcef5b8865ac3ac3339fe86fb59013630410ac844ef88c9a1a45c3266
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/pluggy/issues/457
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
