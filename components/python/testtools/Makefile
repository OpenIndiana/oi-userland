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
#   $WS_TOOLS/python-integrate-project testtools
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testtools
HUMAN_VERSION =			2.8.3
COMPONENT_SUMMARY =		Extensions to the Python standard library unit testing framework
COMPONENT_PROJECT_URL =		https://github.com/testing-cabal/testtools
COMPONENT_ARCHIVE_HASH =	\
	sha256:3b54b543a7583a35f65538b1d36a327fc34943a26bb839bcbe4b2c5e085aa939
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# testtools --> fixtures --> testtools
# testtools --> testscenarios ==> testtools
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# Python 3.9 is not supported by testtools >= 2.8.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Normalize port
COMPONENT_TEST_TRANSFORMS += "-e 's/\(laddr=('\''127.0.0.1'\'', \)[0-9]\{1,\})/\1\$$(PORT))/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/fixtures
TEST_REQUIRED_PACKAGES.python += library/python/testresources
TEST_REQUIRED_PACKAGES.python += library/python/testscenarios
TEST_REQUIRED_PACKAGES.python += library/python/twisted
