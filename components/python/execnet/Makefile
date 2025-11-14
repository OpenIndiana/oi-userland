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
#   $WS_TOOLS/python-integrate-project execnet
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		execnet
HUMAN_VERSION =			2.1.2
COMPONENT_SUMMARY =		execnet: rapid multi-Python deployment
COMPONENT_PROJECT_URL =		https://execnet.readthedocs.io/en/latest/
COMPONENT_ARCHIVE_HASH =	\
	sha256:63d83bfdd9a23e35b9c6a3261412324f964c2ec8dcd8d3c6916ee9373e0befcd
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# execnet --> pytest-timeout --> pytest-cov ==> coverage --> pytest-xdist ==> execnet
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# https://github.com/pytest-dev/execnet/issues/279
PYTEST_ADDOPTS += --deselect testing/test_basics.py::test_popen_io[gevent-sys.executable]

# We need this optional test dependency to get consistent test results
TEST_REQUIRED_PACKAGES.python += library/python/gevent

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
