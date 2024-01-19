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
HUMAN_VERSION =			2.3.1
COMPONENT_SUMMARY =		pytest_check - A pytest plugin that allows multiple failures per test.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/87/9d/77750d005fe5746c29f2ed12ec383a7cd54c99bb7a7454ca86faaa8e71a1/pytest_check-2.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:51b8f18a8ccaa426c5d913c4e0e46f014aaa7579481ea03d22d7e1f498f689b2
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
