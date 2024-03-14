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
#   $WS_TOOLS/python-integrate-project pytest-xdist
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-xdist
HUMAN_VERSION =			3.5.0
COMPONENT_SUMMARY =		pytest-xdist - pytest xdist plugin for distributed testing, most importantly across multiple CPUs
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pytest-xdist
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b3/f4/ac9c4ccbc5984ebc3bef6dbdbcdaf553a1aae07c08e63b8b25a6239ecc45/pytest-xdist-3.5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cbb36f3d67e0c478baa57fa4edc8843887e0f6cfc42d677530a36d7472b32d8a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# There is an incompatibility between execnet and teamcity-messages causing
# some tests to fail if teamcity-messages is installed while pytest-xdist tests
# are run.  See https://github.com/pytest-dev/execnet/issues/161 for details.
TEST_CONFLICTING_PACKAGES.python += library/python/teamcity-messages

# https://github.com/okken/pytest-check/issues/146
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-check

# https://github.com/pytest-dev/pytest-xdist/issues/968
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-checkdocs
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-console-scripts
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-randomly
TEST_CONFLICTING_PACKAGES.python += library/python/typeguard

# https://github.com/bitprophet/pytest-relaxed/issues/31
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-relaxed

# https://github.com/pytest-dev/pytest-rerunfailures/issues/242
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-rerunfailures

# https://github.com/pytest-dev/pluggy/issues/457
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-shell-utilities
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-xprocess

# https://github.com/jaraco/pytest-enabler/issues/10#issuecomment-1809078866
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/execnet
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/filelock
