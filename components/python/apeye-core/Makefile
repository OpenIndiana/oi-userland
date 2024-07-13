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
#   $WS_TOOLS/python-integrate-project apeye-core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		apeye-core
HUMAN_VERSION =			1.1.5
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Core (offline) functionality for the apeye library.
COMPONENT_PROJECT_URL =		https://github.com/domdfcoding/apeye-core
COMPONENT_ARCHIVE_URL =		\
	https://github.com/domdfcoding/apeye-core/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:40a7633ccc60eb521be71e14cfe03ad5da342514cd9539ada29041530383a943
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# apeye-core --> coincidence ==> whey ==> pyproject-parser ==> shippinglabel ==> apeye ==> apeye-core
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# pytest-datadir is needed by pytest-regressions and pytest-regressions is
# needed by coincidence so both pytest-regressions and pytest-datadir will be
# always installed.
#
# We need to list them explicitly here to make sure they are enabled.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-regressions
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/domdf-python-tools
PYTHON_REQUIRED_PACKAGES += library/python/hatch-requirements-txt
PYTHON_REQUIRED_PACKAGES += library/python/idna
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coincidence
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/importlib-metadata
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
