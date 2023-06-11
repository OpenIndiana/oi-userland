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
#   $WS_TOOLS/python-integrate-project filelock
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		filelock
HUMAN_VERSION =			3.12.1
COMPONENT_SUMMARY =		filelock - A platform independent file lock.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/py-filelock
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/31/73/5b47f2a0b8543c105f26f74e2a680ea74799379cf53802f0f979e9be9b7a/filelock-3.12.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:82b1f7da46f0ae42abf1bc78e548667f484ac59d2bcec38c713cee7e2eb51e83
COMPONENT_LICENSE =		Unlicense
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/diff-cover
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
