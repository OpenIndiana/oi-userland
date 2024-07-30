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
#   $WS_TOOLS/python-integrate-project apeye
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		apeye
HUMAN_VERSION =			1.4.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Handy tools for working with URLs and APIs.
COMPONENT_PROJECT_URL =		https://github.com/domdfcoding/apeye
COMPONENT_ARCHIVE_URL =		\
	https://github.com/domdfcoding/apeye/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f8affe31802f0a31b28b42742d2b92baaf38fd6c124b6ee8e071e2f5da5e2932
COMPONENT_LICENSE =		LGPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# apeye --> coincidence ==> whey ==> pyproject-parser ==> shippinglabel ==> apeye
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/domdfcoding/apeye/issues/91
PYTEST_ADDOPTS += --deselect tests/test_rate_limiter.py::test_rate_limit

# Contains timestamp and random port number
COMPONENT_TEST_TRANSFORMS += "-e 's/ \{1,\}\[.*\] ENGINE.*//'"

# pytest-datadir is needed by pytest-regressions and pytest-regressions is
# needed by coincidence so both pytest-regressions and pytest-datadir will be
# always installed.
#
# We need to list them explicitly here to make sure they are enabled.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir

# see 04-test-yaml.patch
TEST_REQUIRED_PACKAGES.python += library/python/pyyaml
TEST_REQUIRED_PACKAGES.python += library/python/ruamel-yaml

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/apeye-core
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cachecontrol
TEST_REQUIRED_PACKAGES.python += library/python/cherrypy
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
