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
#   $WS_TOOLS/python-integrate-project shippinglabel
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		shippinglabel
HUMAN_VERSION =			2.1.0
COMPONENT_SUMMARY =		Utilities for handling packages.
COMPONENT_PROJECT_URL =		https://github.com/domdfcoding/shippinglabel
COMPONENT_ARCHIVE_URL =		\
	https://github.com/domdfcoding/shippinglabel/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:51ea365ca7fc8ff691d80dac446abc1cd595c997a6b9bc0a4aab4e8d89d07e51
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# shippinglabel --> coincidence ==> whey ==> pyproject-parser ==> shippinglabel
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# pytest-datadir is needed by pytest-regressions and pytest-regressions is
# needed by coincidence so both pytest-regressions and pytest-datadir will be
# always installed.
#
# We need to list them explicitly here to make sure they are enabled.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/dist-meta
PYTHON_REQUIRED_PACKAGES += library/python/dom-toml
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/apeye
TEST_REQUIRED_PACKAGES.python += library/python/betamax
TEST_REQUIRED_PACKAGES.python += library/python/cachecontrol
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/consolekit
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/requests
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
