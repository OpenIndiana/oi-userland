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
#   $WS_TOOLS/python-integrate-project tox
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tox
HUMAN_VERSION =			4.6.3
COMPONENT_SUMMARY =		tox - tox is a generic virtualenv management and test command line tool
COMPONENT_PROJECT_URL =		http://tox.readthedocs.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b2/7b/6cb14ae53aa80e57e9ac07431624a83d8f5b09af1284b5a3850fb09b8d4e/tox-4.6.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9e2c5091a117d03b583c57c4c40aecd068099c17d40520e7b165e85c19334534
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox-current-env (test bootstrap)
# - Userland testing framework (see setup.py.mk)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cachetools
PYTHON_REQUIRED_PACKAGES += library/python/chardet
PYTHON_REQUIRED_PACKAGES += library/python/colorama
PYTHON_REQUIRED_PACKAGES += library/python/filelock
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/pyproject-api
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/covdefaults
TEST_REQUIRED_PACKAGES.python += library/python/detect-test-pollution
TEST_REQUIRED_PACKAGES.python += library/python/devpi-process
TEST_REQUIRED_PACKAGES.python += library/python/diff-cover
TEST_REQUIRED_PACKAGES.python += library/python/distlib
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/hatch-vcs
TEST_REQUIRED_PACKAGES.python += library/python/hatchling
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/re-assert
TEST_REQUIRED_PACKAGES.python += library/python/time-machine
TEST_REQUIRED_PACKAGES.python += library/python/wheel
